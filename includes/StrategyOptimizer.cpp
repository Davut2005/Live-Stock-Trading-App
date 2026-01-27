#include "StrategyOptimizer.h"
#include "TechnicalAnalysis.h"
#include <algorithm>
#include <iostream>

StrategyOptimizer::StrategyOptimizer(int popSize, int generations, double mRate)
    : populationSize(popSize), maxGenerations(generations), mutationRate(mRate) {
    std::random_device rd;
    rng = std::mt19937(rd());
}

StrategyParams StrategyOptimizer::optimize(const std::vector<double>& prices) {
    if(prices.empty()) return {};

    initializePopulation();
    
    for (int gen = 0; gen < maxGenerations; ++gen) {
        evaluateFitness(population, prices);
        
        // Sort by fitness descending
        std::sort(population.begin(), population.end(), [](const StrategyParams& a, const StrategyParams& b) {
            return a.fitness > b.fitness;
        });

        // Elitism: Keep top 10%
        std::vector<StrategyParams> newPop;
        int eliteCount = populationSize / 10;
        for(int i=0; i<eliteCount; ++i) newPop.push_back(population[i]);

        // Generate rest
        std::uniform_int_distribution<int> idxDist(0, populationSize/2); // Select from top 50%
        
        while(newPop.size() < static_cast<size_t>(populationSize)) {
            const auto& p1 = population[idxDist(rng)];
            const auto& p2 = population[idxDist(rng)];
            
            auto child = crossover(p1, p2);
            mutate(child);
            newPop.push_back(child);
        }
        population = newPop;
        
        // std::cout << "Generation " << gen << " Best Fitness: " << population[0].fitness << "%\n";
    }
    
    return population[0];
}

void StrategyOptimizer::initializePopulation() {
    population.clear();
    std::uniform_int_distribution<int> rsiDist(5, 30);
    std::uniform_int_distribution<int> macdFastDist(5, 20);
    std::uniform_int_distribution<int> macdSlowDist(21, 50);
    std::uniform_real_distribution<double> slDist(0.01, 0.10);
    
    for(int i=0; i<populationSize; ++i) {
        StrategyParams p;
        p.rsiPeriod = rsiDist(rng);
        p.macdFast = macdFastDist(rng);
        p.macdSlow = macdSlowDist(rng);
        p.macdSignal = 9;
        p.stopLoss = slDist(rng);
        p.takeProfit = p.stopLoss * 2.0;
        p.fitness = 0.0;
        population.push_back(p);
    }
}

void StrategyOptimizer::evaluateFitness(std::vector<StrategyParams>& pop, const std::vector<double>& prices) {
    for(auto& p : pop) {
        p.fitness = runBacktest(p, prices);
    }
}

double StrategyOptimizer::runBacktest(const StrategyParams& params, const std::vector<double>& prices) {
    // Simple Strategy:
    // Buy if RSI < 30
    // Sell if RSI > 70 OR StopLoss OR TakeProfit
    
    auto rsi = TechnicalAnalysis::calculateRSI(prices, params.rsiPeriod);
    if(rsi.empty()) return -100.0;

    double balance = 10000.0;
    double position = 0.0;
    double entryPrice = 0.0;
    
    size_t offset = prices.size() - rsi.size(); // RSI starts later
    
    for(size_t i=0; i<rsi.size(); ++i) {
        size_t priceIdx = i + offset;
        double currentPrice = prices[priceIdx];
        double currentRsi = rsi[i];
        
        if (position == 0.0) {
            // Buy Signal
            if (currentRsi < 30) {
                position = balance / currentPrice;
                balance = 0.0;
                entryPrice = currentPrice;
            }
        } else {
            // Sell Signal
            double pnl = (currentPrice - entryPrice) / entryPrice;
            
            if (currentRsi > 70 || pnl < -params.stopLoss || pnl > params.takeProfit) {
                balance = position * currentPrice;
                position = 0.0;
            }
        }
    }
    
    if (position > 0.0) balance = position * prices.back();
    
    return ((balance - 10000.0) / 10000.0) * 100.0; // ROI %
}

StrategyParams StrategyOptimizer::crossover(const StrategyParams& p1, const StrategyParams& p2) {
    StrategyParams child = p1;
    std::uniform_int_distribution<int> coin(0, 1);
    
    if(coin(rng)) child.rsiPeriod = p2.rsiPeriod;
    if(coin(rng)) child.macdFast = p2.macdFast;
    if(coin(rng)) child.stopLoss = p2.stopLoss;
    
    return child;
}

void StrategyOptimizer::mutate(StrategyParams& p) {
    std::uniform_real_distribution<double> chance(0.0, 1.0);
    if(chance(rng) < mutationRate) {
        std::uniform_int_distribution<int> rsiDist(5, 30);
        p.rsiPeriod = rsiDist(rng);
    }
    if(chance(rng) < mutationRate) {
        std::uniform_real_distribution<double> slDist(0.01, 0.10);
        p.stopLoss = slDist(rng);
        p.takeProfit = p.stopLoss * 2.0;
    }
}
