#include "TechnicalAnalysis.h"
#include <numeric>
#include <cmath>
#include <algorithm>

std::vector<double> TechnicalAnalysis::calculateSMA(const std::vector<double>& prices, int period) {
    std::vector<double> sma;
    if (prices.size() < static_cast<size_t>(period)) return sma;

    for (size_t i = 0; i <= prices.size() - period; ++i) {
        double sum = std::accumulate(prices.begin() + i, prices.begin() + i + period, 0.0);
        sma.push_back(sum / period);
    }
    return sma;
}

std::vector<double> TechnicalAnalysis::calculateEMA(const std::vector<double>& prices, int period) {
    std::vector<double> ema;
    if (prices.size() < static_cast<size_t>(period)) return ema;

    double multiplier = 2.0 / (period + 1);
    
    // Start with SMA
    double sum = std::accumulate(prices.begin(), prices.begin() + period, 0.0);
    double currentEma = sum / period;
    ema.push_back(currentEma);

    for (size_t i = period; i < prices.size(); ++i) {
        currentEma = (prices[i] - currentEma) * multiplier + currentEma;
        ema.push_back(currentEma);
    }
    return ema;
}

std::vector<double> TechnicalAnalysis::calculateRSI(const std::vector<double>& prices, int period) {
    if (prices.size() <= static_cast<size_t>(period)) return {};

    std::vector<double> rsi;
    double avgGain = 0.0;
    double avgLoss = 0.0;

    for (int i = 1; i <= period; ++i) {
        double change = prices[i] - prices[i-1];
        if (change > 0) avgGain += change;
        else avgLoss -= change;
    }

    avgGain /= period;
    avgLoss /= period;

    double rs = (avgLoss == 0) ? 100.0 : avgGain / avgLoss;
    rsi.push_back(100.0 - (100.0 / (1.0 + rs)));

    for (size_t i = period + 1; i < prices.size(); ++i) {
        double change = prices[i] - prices[i-1];
        double gain = (change > 0) ? change : 0.0;
        double loss = (change < 0) ? -change : 0.0;

        avgGain = (avgGain * (period - 1) + gain) / period;
        avgLoss = (avgLoss * (period - 1) + loss) / period;

        rs = (avgLoss == 0) ? 100.0 : avgGain / avgLoss;
        rsi.push_back(100.0 - (100.0 / (1.0 + rs)));
    }

    return rsi;
}

// Simplified MACD (returns Moving Average Convergence Divergence line only)
std::vector<double> TechnicalAnalysis::calculateMACD(const std::vector<double>& prices, int fastMsg, int slowMsg, int signal) {
    // Placeholder for fully detailed MACD implementation complexity
    (void)signal; 
    auto fastEMA = calculateEMA(prices, fastMsg);
    auto slowEMA = calculateEMA(prices, slowMsg);
    
    std::vector<double> macdLine;
    size_t offset = slowMsg - fastMsg; // Align arrays 
    
    // We need both valid
    if (slowEMA.empty() || fastEMA.empty()) return {};

    for (size_t i = 0; i < slowEMA.size(); ++i) {
         // This alignment logic is simplified; real implementation needs precise timestamp matching
         if (i + offset < fastEMA.size()) {
             macdLine.push_back(fastEMA[i + offset] - slowEMA[i]);
         }
    }
    return macdLine;
}

std::vector<double> TechnicalAnalysis::calculateBollingerBands(const std::vector<double>& prices, int period, double numStdDev, bool upper) {
    if (prices.size() < static_cast<size_t>(period)) return {};

    std::vector<double> bands;
    auto sma = calculateSMA(prices, period);

    for (size_t i = 0; i < sma.size(); ++i) {
        // Calculate StdDev for window
        size_t startIdx = i; // indices align because SMA shrinks result
        
        double sumSqDiff = 0.0;
        double mean = sma[i];
        
        for(int j=0; j<period; ++j) {
            double diff = prices[startIdx + j] - mean;
            sumSqDiff += diff * diff;
        }
        
        double stdDev = std::sqrt(sumSqDiff / period);
        if (upper) 
            bands.push_back(mean + (stdDev * numStdDev));
        else
            bands.push_back(mean - (stdDev * numStdDev));
    }
    return bands;
}
