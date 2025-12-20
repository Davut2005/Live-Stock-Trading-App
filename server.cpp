#include "server.h"
#include "./include/crow.h"  
#include "./includes/TechStock.h"  
#include <memory>

Portfolio portfolio;
Trader trader("Alice", 50000.0);

void runServer() {
    crow::SimpleApp app;

    
    CROW_ROUTE(app, "/stocks")
    ([](){
        std::ostringstream ss;
        ss << "Portfolio:\n";
        portfolio.showAllToStream(ss);         
        return crow::response{ ss.str() };
    });

    
    CROW_ROUTE(app, "/buy").methods(crow::HTTPMethod::Post)
    ([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        std::string name = body["name"].s();
        double price = body["price"].d();
        int quantity = body["quantity"].i();

        try {
            auto stock = std::make_unique<TechStock>(name, price); 
            trader.buyStock(std::move(stock), quantity);
        } catch (const std::exception& e) {
            return crow::response(400, e.what());
        }

        return crow::response(200, "Stock bought successfully");
    });

    app.port(18080).multithreaded().run();
}

int main()
{
    runServer();
    return 0;
}
