#pragma once
#include <vector>
#include <utility>
#include "HistoricalData.h"

class MarketSimulator {
public:
    struct SimulationResult {
        double expectedPrice;
        double worstCase;
        double bestCase;
        std::vector<double> projectedPath;
    };

    MarketSimulator(double initialPrice, double volatility, double drift);
    
    // Run a single path simulation
    std::vector<double> simulatePath(int steps, double dt);
    
    // Run Monte Carlo simulation
    SimulationResult runMonteCarlo(int numSimulations, int steps);

private:
    double initialPrice;
    double volatility;
    double drift;
};
