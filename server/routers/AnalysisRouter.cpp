#include "AnalysisRouter.h"
#include "TechnicalAnalysis.h" // Assuming this exists in includes
#include <iostream>

void AnalysisRouter::registerRoutes(crow::SimpleApp& app, std::shared_ptr<MarketDataManager> market) {

    // GET /api/analysis/sma?symbol=AAPL&period=20
    CROW_ROUTE(app, "/api/analysis/sma")
    ([market](const crow::request& req){
        auto symbol = req.url_params.get("symbol");
        auto periodStr = req.url_params.get("period");
        
        if (!symbol || !periodStr) return crow::response(400, "Missing symbol or period");
        
        int period = std::stoi(periodStr);
        // Warning: getPriceHistory returns vector by value, expensive for large data
        std::vector<double> history = market->getPriceHistory(symbol);
        
        if (history.empty()) return crow::response(404, "No data for symbol");
        
        std::vector<double> sma = TechnicalAnalysis::calculateSMA(history, period);
        
        crow::json::wvalue resp;
        resp["symbol"] = symbol;
        resp["indicator"] = "SMA";
        resp["period"] = period;
        
        if (!sma.empty()) {
            resp["current_value"] = sma.back();
            
            // Return last 10 points
            std::vector<crow::json::wvalue> points;
            size_t start = sma.size() > 10 ? sma.size() - 10 : 0;
            for (size_t i = start; i < sma.size(); ++i) {
                points.push_back(sma[i]);
            }
            resp["recent_values"] = std::move(points);
        } else {
             resp["current_value"] = nullptr;
        }

        return crow::response(resp);
    });

    // GET /api/analysis/rsi?symbol=AAPL&period=14
    CROW_ROUTE(app, "/api/analysis/rsi")
    ([market](const crow::request& req){
         auto symbol = req.url_params.get("symbol");
        auto periodStr = req.url_params.get("period");
        
        if (!symbol || !periodStr) return crow::response(400, "Missing symbol or period");
         int period = std::stoi(periodStr);
         
         std::vector<double> history = market->getPriceHistory(symbol);
         if (history.empty()) return crow::response(404, "No data");
         
         std::vector<double> rsi = TechnicalAnalysis::calculateRSI(history, period);
          crow::json::wvalue resp;
        resp["symbol"] = symbol;
        resp["indicator"] = "RSI";
        resp["period"] = period;
        
        if (!rsi.empty()) {
            double lastRsi = rsi.back();
            resp["current_value"] = lastRsi;
            
            std::string signal = "NEUTRAL";
            if (lastRsi > 70) signal = "OVERBOUGHT";
            else if (lastRsi < 30) signal = "OVERSOLD";
            
            resp["signal"] = signal;
        }
        
        return crow::response(resp);
    });
}
