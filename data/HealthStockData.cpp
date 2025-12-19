#include "../includes/HealthStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createHealthStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<HealthStock>("PFE", 45.0));
    stocks.push_back(std::make_unique<HealthStock>("JNJ", 160.0));
    stocks.push_back(std::make_unique<HealthStock>("MRNA", 140.0));
    stocks.push_back(std::make_unique<HealthStock>("GILD", 70.0));
    return stocks;
}
