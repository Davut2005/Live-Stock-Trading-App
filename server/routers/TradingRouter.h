#pragma once
#include "../../libs/crow.h"
#include "Trader.h"
#include "MarketDataManager.h"
#include <memory>

class TradingRouter {
public:
    static void registerRoutes(crow::SimpleApp& app, std::shared_ptr<Trader> trader, std::shared_ptr<MarketDataManager> market);
};
