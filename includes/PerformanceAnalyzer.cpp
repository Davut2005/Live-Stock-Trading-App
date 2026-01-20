#include "PerformanceAnalyzer.h"

double PerformanceAnalyzer::calculateTotalValue(const Portfolio& portfolio) {
    double total = 0.0;
    for (const auto& stock : portfolio.getStocks()) {
        if (stock) { // Good practice to check if the pointer is not null
            total += stock->getPrice() * stock->getQuantity();
        }
    }
    return total;
}

double PerformanceAnalyzer::calculateROI(const Portfolio& portfolio, double initialInvestment) {
    double currentValue = calculateTotalValue(portfolio);
    return ((currentValue - initialInvestment) / initialInvestment) * 100.0;
}
