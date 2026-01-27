#pragma once
#include <vector>
#include <string>

class TechnicalAnalysis {
public:
    static std::vector<double> calculateSMA(const std::vector<double>& prices, int period);
    static std::vector<double> calculateEMA(const std::vector<double>& prices, int period);
    static std::vector<double> calculateRSI(const std::vector<double>& prices, int period = 14);
    static std::vector<double> calculateMACD(const std::vector<double>& prices, int fastMsg = 12, int slowMsg = 26, int signal = 9);
    static std::vector<double> calculateBollingerBands(const std::vector<double>& prices, int period, double numStdDev, bool upper);
};
