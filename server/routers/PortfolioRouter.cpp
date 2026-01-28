#include "PortfolioRouter.h"

void PortfolioRouter::registerRoutes(crow::SimpleApp& app, std::shared_ptr<Trader> trader) {

    // GET /api/portfolio
    CROW_ROUTE(app, "/api/portfolio")
    ([trader](){
        auto& p = trader->getPortfolio();
        crow::json::wvalue resp;
        
        double totalValue = p.totalValue();
        double cash = trader->getBalance();
        
        resp["cash"] = cash;
        resp["invested_value"] = totalValue;
        resp["net_worth"] = cash + totalValue;
        
        std::vector<crow::json::wvalue> holdings;
        for(const auto& stock : p.getStocks()) {
            crow::json::wvalue item;
            item["symbol"] = stock->getName(); // Fixed getter usage
            item["quantity"] = stock->getQuantity();
            item["current_price"] = stock->getPrice();
            item["value"] = stock->totalValue();
            item["type"] = stock->getType(); // Using polymorphic call
            holdings.push_back(item);
        }
        
        resp["holdings"] = std::move(holdings);
        return crow::response(resp);
    });

    // GET /api/portfolio/<symbol>
    CROW_ROUTE(app, "/api/portfolio/<string>")
    ([trader](const std::string& symbol){
        auto& p = trader->getPortfolio();
        Stock* s = p.findStock(symbol);
        
        if (!s) {
            return crow::response(404, "Stock not found in portfolio");
        }
        
        crow::json::wvalue item;
        item["symbol"] = s->getName();
        item["quantity"] = s->getQuantity();
        item["avg_cost"] = 0.0; // Todo: implement avg cost tracking
        item["market_value"] = s->totalValue();
        
        return crow::response(item);
    });
}
