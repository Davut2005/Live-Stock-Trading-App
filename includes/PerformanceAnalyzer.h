#ifndef PERFORMANCE_ANALYZER_H
#define PERFORMANCE_ANALYZER_H

#include "Portfolio.h"

class PerformanceAnalyzer {
public:
    static double calculateTotalValue(const Portfolio& portfolio);
    static double calculateROI(const Portfolio& portfolio, double initialInvestment);
};

#endif
