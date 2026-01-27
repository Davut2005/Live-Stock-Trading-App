#pragma once
#include <vector>
#include <functional>
#include <random>

struct StrategyParams {
    int rsiPeriod;
    int macdFast;
    int macdSlow;
    int macdSignal;
    double stopLoss;
    double takeProfit;
    
    double fitness; // ROI
};

class StrategyOptimizer {
public:
    StrategyOptimizer(int popSize, int generations, double mutationRate);
    
    // Run genetic algorithm
    StrategyParams optimize(const std::vector<double>& prices);

private:
    int populationSize;
    int maxGenerations;
    double mutationRate;

    std::vector<StrategyParams> population;
    std::mt19937 rng;

    void initializePopulation();
    void evaluateFitness(std::vector<StrategyParams>& pop, const std::vector<double>& prices);
    double runBacktest(const StrategyParams& params, const std::vector<double>& prices);
    
    StrategyParams crossover(const StrategyParams& p1, const StrategyParams& p2);
    void mutate(StrategyParams& p);
};
