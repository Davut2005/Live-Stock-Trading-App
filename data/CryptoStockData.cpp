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
    stocks.push_back(std::make_unique<CryptoStock>("XRP", 0.5));
    stocks.push_back(std::make_unique<CryptoStock>("DOGE", 0.07));
    stocks.push_back(std::make_unique<CryptoStock>("TRX", 0.08));
    stocks.push_back(std::make_unique<CryptoStock>("DOT", 5.0));
    stocks.push_back(std::make_unique<CryptoStock>("LTC", 90.0));
    stocks.push_back(std::make_unique<CryptoStock>("MATIC", 0.7));
    stocks.push_back(std::make_unique<CryptoStock>("AVAX", 12.0));
    stocks.push_back(std::make_unique<CryptoStock>("SHIB", 0.000008));
    stocks.push_back(std::make_unique<CryptoStock>("LINK", 6.5));
    stocks.push_back(std::make_unique<CryptoStock>("UNI", 5.5));
    stocks.push_back(std::make_unique<CryptoStock>("XLM", 0.1));
    stocks.push_back(std::make_unique<CryptoStock>("ATOM", 9.0));
    stocks.push_back(std::make_unique<CryptoStock>("XMR", 150.0));
    stocks.push_back(std::make_unique<CryptoStock>("ETC", 18.0));
    stocks.push_back(std::make_unique<CryptoStock>("BCH", 200.0));
    stocks.push_back(std::make_unique<CryptoStock>("FIL", 4.0));
    return stocks;
}
