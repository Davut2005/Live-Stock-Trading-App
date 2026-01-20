#include "MarketDataManager.h"
#include <numeric>
#include <stdexcept>

MarketDataManager::MarketDataManager() {}

void MarketDataManager::updatePrice(const std::string& symbol, double price) {
    std::lock_guard<std::mutex> lock(dataMutex);
    latestPrices[symbol] = price;
    priceHistory[symbol].push_back(price);
}

double MarketDataManager::getLatestPrice(const std::string& symbol) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    auto it = latestPrices.find(symbol);
    if (it == latestPrices.end())
        throw std::runtime_error("Price not available for symbol");
    return it->second;
}

std::vector<double> MarketDataManager::getPriceHistory(const std::string& symbol) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    auto it = priceHistory.find(symbol);
    if (it == priceHistory.end())
        return {};
    return it->second;
}

double MarketDataManager::getMovingAverage(const std::string& symbol, size_t period) const {
    auto history = getPriceHistory(symbol);
    if (history.size() < period)
        throw std::runtime_error("Not enough data for moving average");

    double sum = std::accumulate(history.end() - period, history.end(), 0.0);
    return sum / period;
}

bool MarketDataManager::hasSymbol(const std::string& symbol) const {
    std::lock_guard<std::mutex> lock(dataMutex);
    return latestPrices.count(symbol) > 0;
}
