#include "../includes/EnergyStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createEnergyStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<EnergyStock>("XOM", 110.0));
    stocks.push_back(std::make_unique<EnergyStock>("CVX", 160.0));
    stocks.push_back(std::make_unique<EnergyStock>("BP", 28.0));
    stocks.push_back(std::make_unique<EnergyStock>("TOT", 60.0));
    return stocks;
}
