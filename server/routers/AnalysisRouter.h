#pragma once
#include "../../libs/crow.h"
#include "MarketDataManager.h"
#include <memory>

class AnalysisRouter {
public:
    static void registerRoutes(crow::SimpleApp& app, std::shared_ptr<MarketDataManager> market);
};
