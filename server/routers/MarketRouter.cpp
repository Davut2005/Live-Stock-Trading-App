#include "MarketRouter.h"
#include <vector>

void MarketRouter::registerRoutes(crow::SimpleApp& app, std::shared_ptr<MarketDataManager> market) {

    // GET /api/market/price/<symbol>
    CROW_ROUTE(app, "/api/market/price/<string>")
    ([market](const std::string& symbol){
        try {
            double price = market->getLatestPrice(symbol);
            crow::json::wvalue x;
            x["symbol"] = symbol;
            x["price"] = price;
            x["currency"] = "USD";
            x["timestamp"] = "now"; // In real app, use actual timestamp
            return crow::response(x);
        } catch (...) {
            return crow::response(404, "Symbol not found");
        }
    });

    // GET /api/market/history/<symbol>
    CROW_ROUTE(app, "/api/market/history/<string>")
    ([market](const std::string& symbol){
        // Simulate checking if symbol exists first
        if (!market->hasSymbol(symbol)) {
             return crow::response(404, "Symbol not found");
        }

        std::vector<double> history = market->getPriceHistory(symbol);
        crow::json::wvalue x;
        x["symbol"] = symbol;
        
        // Convert vector to json array
        // Crow's json writer doesn't support direct vector assignment easily in all versions,
        // so we manually construct.
        std::vector<crow::json::wvalue> pricesJson;
        for(double p : history) {
            pricesJson.push_back(p);
        }
        x["history"] = std::move(pricesJson);
        x["count"] = history.size();

        return crow::response(x);
    });

    // GET /api/market/status
    CROW_ROUTE(app, "/api/market/status")
    ([](){
        crow::json::wvalue x;
        x["status"] = "OPEN";
        x["exchange"] = "NYSE";
        x["timezone"] = "EST";
        return crow::response(x);
    });
    
    // GET /api/market/quote/<symbol> -> Detailed Quote
    CROW_ROUTE(app, "/api/market/quote/<string>")
    ([market](const std::string& symbol){
         if (!market->hasSymbol(symbol)) return crow::response(404);
         
         double price = market->getLatestPrice(symbol);
         double prevClose = price * 0.99; // Mock previous close
         double change = price - prevClose;
         double pctChange = (change / prevClose) * 100.0;
         
         crow::json::wvalue x;
         x["symbol"] = symbol;
         x["price"] = price;
         x["prev_close"] = prevClose;
         x["change"] = change;
         x["pct_change"] = pctChange;
         x["high"] = price * 1.01;
         x["low"] = price * 0.98;
         x["volume"] = 1500000; // Mock volume
         
         return crow::response(x);
    });
}
