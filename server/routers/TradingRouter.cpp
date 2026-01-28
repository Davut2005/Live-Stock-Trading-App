#include "TradingRouter.h"
#include "StockFactory.h"
#include <iostream>

void TradingRouter::registerRoutes(crow::SimpleApp& app, std::shared_ptr<Trader> trader, std::shared_ptr<MarketDataManager> market) {

    // POST /api/trading/buy
    // Body: { "symbol": "AAPL", "quantity": 10 }
    CROW_ROUTE(app, "/api/trading/buy").methods(crow::HTTPMethod::Post)
    ([trader, market](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400, "Invalid JSON");
        
        std::string symbol = x["symbol"].s();
        int quantity = x["quantity"].i();
        
        if (quantity <= 0) return crow::response(400, "Quantity must be positive");
        
        try {
            double price = market->getLatestPrice(symbol);
            
            // In a real app we'd determine type logic better, here we default to Tech for simple buy
            // unless known otherwise. 
            // Better logic: ask MarketData for metadata about the stock.
            
            auto stock = StockFactory::create("tech", symbol, price, 0.0);
            trader->buyStock(std::move(stock), quantity);
            
            crow::json::wvalue resp;
            resp["status"] = "filled";
            resp["symbol"] = symbol;
            resp["quantity"] = quantity;
            resp["price"] = price;
            resp["total_cost"] = price * quantity;
            resp["remaining_balance"] = trader->getBalance();
            
            return crow::response(201, resp);
            
        } catch (const std::exception& e) {
            crow::json::wvalue err;
            err["error"] = e.what();
            return crow::response(400, err);
        }
    });

    // POST /api/trading/sell
    CROW_ROUTE(app, "/api/trading/sell").methods(crow::HTTPMethod::Post)
    ([trader, market](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400, "Invalid JSON");
        
        std::string symbol = x["symbol"].s();
        int quantity = x["quantity"].i();
        
        try {
            // Need current price to sell
            double price = market->getLatestPrice(symbol);
            
            trader->sellStock(symbol, quantity, price);
            
            crow::json::wvalue resp;
            resp["status"] = "sold";
            resp["symbol"] = symbol;
            resp["quantity"] = quantity;
            resp["price"] = price;
            resp["total_proceeds"] = price * quantity;
            resp["new_balance"] = trader->getBalance();
            
            return crow::response(200, resp);
            
        } catch (const std::exception& e) {
             crow::json::wvalue err;
            err["error"] = e.what();
            return crow::response(400, err);
        }
    });
    
    // GET /api/trading/orders
    // Simulating an order book or active orders view
    CROW_ROUTE(app, "/api/trading/orders")
    ([](){
        // Since we don't have a persistent OrderBook exposed globally in this simple refactor yet,
        // we will return a simulated list of 'open' orders.
        
        crow::json::wvalue o1;
        o1["id"] = "ord_123";
        o1["symbol"] = "GOOG";
        o1["side"] = "buy";
        o1["type"] = "limit";
        o1["price"] = 2750.0;
        o1["qty"] = 5;
        o1["status"] = "open";
        
        crow::json::wvalue o2;
        o2["id"] = "ord_124";
        o2["symbol"] = "TSLA";
        o2["side"] = "sell";
        o2["type"] = "market";
        o2["qty"] = 10;
        o2["status"] = "pending";

        std::vector<crow::json::wvalue> orders;
        orders.push_back(o1);
        orders.push_back(o2);
        
        crow::json::wvalue resp;
        resp["orders"] = std::move(orders);
        
        return crow::response(resp);
    });
}
