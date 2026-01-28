#include "../includes/HealthStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createHealthStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<HealthStock>("PFE", 45.0));
    stocks.push_back(std::make_unique<HealthStock>("JNJ", 160.0));
    stocks.push_back(std::make_unique<HealthStock>("MRNA", 140.0));
    stocks.push_back(std::make_unique<HealthStock>("GILD", 70.0));
    stocks.push_back(std::make_unique<HealthStock>("UNH", 480.0));
    stocks.push_back(std::make_unique<HealthStock>("ABBV", 150.0));
    stocks.push_back(std::make_unique<HealthStock>("MRK", 110.0));
    stocks.push_back(std::make_unique<HealthStock>("LLY", 450.0));
    stocks.push_back(std::make_unique<HealthStock>("TMO", 520.0));
    stocks.push_back(std::make_unique<HealthStock>("ABT", 110.0));
    stocks.push_back(std::make_unique<HealthStock>("NVS", 95.0));
    stocks.push_back(std::make_unique<HealthStock>("AZN", 70.0));
    stocks.push_back(std::make_unique<HealthStock>("DHR", 250.0));
    stocks.push_back(std::make_unique<HealthStock>("BMY", 60.0));
    stocks.push_back(std::make_unique<HealthStock>("AMGN", 230.0));
    stocks.push_back(std::make_unique<HealthStock>("MDT", 85.0));
    stocks.push_back(std::make_unique<HealthStock>("CVS", 75.0));
    stocks.push_back(std::make_unique<HealthStock>("ISRG", 310.0));
    stocks.push_back(std::make_unique<HealthStock>("SYK", 280.0));
    stocks.push_back(std::make_unique<HealthStock>("REGN", 750.0));
    stocks.push_back(std::make_unique<HealthStock>("VRTX", 350.0));
    return stocks;
}
