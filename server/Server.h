#pragma once

#include "../libs/crow.h"
#include "Trader.h"
#include "Portfolio.h"
#include "MarketDataManager.h"
#include "MarketSimulator.h"
#include <memory>
#include <string>

class Server {
public:
    Server(int port = 18080);
    void run();

private:
    int port_;
    crow::SimpleApp app_;

    // Core Business Logic Components
    std::shared_ptr<Trader> trader_;
    std::shared_ptr<Portfolio> portfolio_;
    std::shared_ptr<MarketDataManager> market_;
    std::unique_ptr<MarketSimulator> simulator_;

    // Initialization methods
    void setupRoutes();
    void initializeData();
    
    // Internal Middleware setup (simulated)
    void setupMiddleware();
};
