#include "Server.h"
#include <iostream>

// Include Routers (Forward declarations or headers)
#include "routers/MarketRouter.h"
#include "routers/TradingRouter.h"
#include "routers/PortfolioRouter.h"
#include "routers/AnalysisRouter.h"
#include "routers/AdminRouter.h"

// Included for data initialization
#include "StockFactory.h"

Server::Server(int port) : port_(port) {
    std::cout << "[Server] Initializing subsystems...\n";
    initializeData();
}

void Server::initializeData() {
    // Create shared instances of core components
    portfolio_ = std::make_shared<Portfolio>();
    trader_ = std::make_shared<Trader>("API User", 100000.0);
    // Explicitly link the portfolio to the trader
    // Note: In a real app we might pass this via constructor, 
    // but here we ensure consistency if Trader doesn't share internal ptr.
    // Given the previous refactor, we rely on Trader owning the portfolio logic mostly.
    
    market_ = std::make_shared<MarketDataManager>();
    
    // Seed some initial data
    market_->updatePrice("AAPL", 150.0);
    market_->updatePrice("GOOG", 2800.0);
    market_->updatePrice("TSLA", 700.0);
    market_->updatePrice("BTC", 30000.0);
    
    // Setup simulator to run in background (conceptually)
    simulator_ = std::make_unique<MarketSimulator>(100.0, 0.2, 0.05);

    std::cout << "[Server] Data initialized.\n";
}

void Server::setupMiddleware() {
    // Example: Logging middleware could be added here
    // app_.route_dynamic(middleware) ...
    // For now, we trust Crow's internal logging or add explicit interceptors
}

void Server::setupRoutes() {
    std::cout << "[Server] Setting up routes...\n";

    // Initialize Routers
    // Market Router: Handles price quotes, history, and market status
    MarketRouter::registerRoutes(app_, market_);

    // Trading Router: Handles orders, executing trades
    TradingRouter::registerRoutes(app_, trader_, market_);

    // Portfolio Router: Handles position viewing, performance metrics
    PortfolioRouter::registerRoutes(app_, trader_);

    // Analysis Router: Technical analysis endpoints
    AnalysisRouter::registerRoutes(app_, market_);
    
    // Admin Router: System control
    AdminRouter::registerRoutes(app_);
    
    // Base route
    CROW_ROUTE(app_, "/")
    ([](){
        return crow::response(200, "Live Stock Trading API is Running. Use /api/...");
    });
}

void Server::run() {
    setupMiddleware();
    setupRoutes();

    std::cout << "[Server] Starting on port " << port_ << "...\n";
    app_.port(port_).multithreaded().run();
}
