#ifndef TRADING_ENGINE_H
#define TRADING_ENGINE_H

#include "MarketDataManager.h"
#include "OrderBook.h"
#include "RiskManager.h"
#include "Logger.h"
#include "Portfolio.h"

class TradingEngine {
private:
    MarketDataManager& marketData;
    RiskManager& riskManager;
    OrderBook orderBook;

public:
    TradingEngine(MarketDataManager& md, RiskManager& rm);

    bool executeOrder(Trader& trader, Portfolio& portfolio, const std::shared_ptr<Order>& order);
};

#endif
