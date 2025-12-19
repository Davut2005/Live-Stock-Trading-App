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
    return stocks;
}
