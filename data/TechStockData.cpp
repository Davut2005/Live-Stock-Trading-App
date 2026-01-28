#include "../includes/TechStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createTechStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<TechStock>("AAPL", 180.5));
    stocks.push_back(std::make_unique<TechStock>("GOOG", 135.75));
    stocks.push_back(std::make_unique<TechStock>("MSFT", 250.0));
    stocks.push_back(std::make_unique<TechStock>("AMZN", 140.0));
    stocks.push_back(std::make_unique<TechStock>("TSLA", 220.0));
    stocks.push_back(std::make_unique<TechStock>("NVDA", 460.0));
    stocks.push_back(std::make_unique<TechStock>("AMD", 110.0));
    stocks.push_back(std::make_unique<TechStock>("INTC", 35.5));
    stocks.push_back(std::make_unique<TechStock>("CSCO", 55.0));
    stocks.push_back(std::make_unique<TechStock>("ORCL", 115.0));
    stocks.push_back(std::make_unique<TechStock>("IBM", 145.0));
    stocks.push_back(std::make_unique<TechStock>("CRM", 210.0));
    stocks.push_back(std::make_unique<TechStock>("ADBE", 520.0));
    stocks.push_back(std::make_unique<TechStock>("QCOM", 120.0));
    stocks.push_back(std::make_unique<TechStock>("TXN", 170.0));
    stocks.push_back(std::make_unique<TechStock>("AVGO", 850.0));
    stocks.push_back(std::make_unique<TechStock>("SAP", 130.0));
    stocks.push_back(std::make_unique<TechStock>("SHOP", 60.0));
    stocks.push_back(std::make_unique<TechStock>("SQ", 55.0));
    stocks.push_back(std::make_unique<TechStock>("UBER", 45.0));
    stocks.push_back(std::make_unique<TechStock>("ABNB", 125.0));
    return stocks;
}
