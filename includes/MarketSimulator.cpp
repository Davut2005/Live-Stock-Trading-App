#include "MarketSimulator.h"
#include <random>
#include <cmath>
#include <algorithm>
#include <iostream>

MarketSimulator::MarketSimulator(double p, double v, double d) 
    : initialPrice(p), volatility(v), drift(d) {}

std::vector<double> MarketSimulator::simulatePath(int steps, double dt) {
    std::vector<double> path;
    path.reserve(steps + 1);
    path.push_back(initialPrice);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    double currentPrice = initialPrice;

    for (int i = 0; i < steps; ++i) {
        double shock = d(gen);
        // Geometric Brownian Motion: dS = S * (mu * dt + sigma * dW)
        double change = currentPrice * (drift * dt + volatility * std::sqrt(dt) * shock);
        currentPrice += change;
        if (currentPrice < 0) currentPrice = 0.01; // Avoid negative prices
        path.push_back(currentPrice);
    }
    return path;
}

MarketSimulator::SimulationResult MarketSimulator::runMonteCarlo(int numSimulations, int steps) {
    std::vector<double> finalPrices;
    std::vector<double> accumulatedPath(steps + 1, 0.0);
    double dt = 1.0 / 252.0; // Daily steps assumes 252 trading days

    for (int i = 0; i < numSimulations; ++i) {
        std::vector<double> path = simulatePath(steps, dt);
        finalPrices.push_back(path.back());
        
        for(size_t j=0; j<path.size(); ++j) {
            accumulatedPath[j] += path[j];
        }
    }

    // Average path
    for(auto& val : accumulatedPath) {
        val /= numSimulations;
    }

    std::sort(finalPrices.begin(), finalPrices.end());
    
    MarketSimulator::SimulationResult res;
    res.expectedPrice = accumulatedPath.back();
    res.projectedPath = accumulatedPath;
    
    // 5th percentile and 95th percentile
    int idx5 = static_cast<int>(numSimulations * 0.05);
    int idx95 = static_cast<int>(numSimulations * 0.95);
    
    res.worstCase = finalPrices[idx5];
    res.bestCase = finalPrices[idx95];

    return res;
}
