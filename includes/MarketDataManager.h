#ifndef MARKET_DATA_MANAGER_H
#define MARKET_DATA_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include "Stock.h"

class MarketDataManager {
private:
    std::unordered_map<std::string, std::vector<double>> priceHistory;
    std::unordered_map<std::string, double> latestPrices;
    mutable std::mutex dataMutex;

public:
    MarketDataManager();

    void updatePrice(const std::string& symbol, double price);
    double getLatestPrice(const std::string& symbol) const;

    std::vector<double> getPriceHistory(const std::string& symbol) const;
    double getMovingAverage(const std::string& symbol, size_t period) const;

    bool hasSymbol(const std::string& symbol) const;
};

#endif
