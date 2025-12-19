#include "../includes/CryptoStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createCryptoStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<CryptoStock>("BTC", 30000.0));
    stocks.push_back(std::make_unique<CryptoStock>("ETH", 1900.0));
    stocks.push_back(std::make_unique<CryptoStock>("BNB", 350.0));
    stocks.push_back(std::make_unique<CryptoStock>("SOL", 25.0));
    stocks.push_back(std::make_unique<CryptoStock>("ADA", 1.2));
    return stocks;
}
