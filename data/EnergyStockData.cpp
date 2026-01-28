#include "../includes/EnergyStock.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Stock>> createEnergyStocks() {
    std::vector<std::unique_ptr<Stock>> stocks;
    stocks.push_back(std::make_unique<EnergyStock>("XOM", 110.0));
    stocks.push_back(std::make_unique<EnergyStock>("CVX", 160.0));
    stocks.push_back(std::make_unique<EnergyStock>("BP", 28.0));
    stocks.push_back(std::make_unique<EnergyStock>("TOT", 60.0));
    stocks.push_back(std::make_unique<EnergyStock>("SHEL", 60.0));
    stocks.push_back(std::make_unique<EnergyStock>("COP", 115.0));
    stocks.push_back(std::make_unique<EnergyStock>("EQNR", 32.0));
    stocks.push_back(std::make_unique<EnergyStock>("SLB", 55.0));
    stocks.push_back(std::make_unique<EnergyStock>("EOG", 125.0));
    stocks.push_back(std::make_unique<EnergyStock>("PXD", 230.0));
    stocks.push_back(std::make_unique<EnergyStock>("MPC", 135.0));
    stocks.push_back(std::make_unique<EnergyStock>("VLO", 130.0));
    stocks.push_back(std::make_unique<EnergyStock>("WMB", 35.0));
    stocks.push_back(std::make_unique<EnergyStock>("OXY", 60.0));
    stocks.push_back(std::make_unique<EnergyStock>("KMI", 17.0));
    stocks.push_back(std::make_unique<EnergyStock>("HES", 150.0));
    stocks.push_back(std::make_unique<EnergyStock>("PSX", 110.0));
    stocks.push_back(std::make_unique<EnergyStock>("HAL", 40.0));
    stocks.push_back(std::make_unique<EnergyStock>("BKR", 35.0));
    stocks.push_back(std::make_unique<EnergyStock>("DVN", 50.0));
    stocks.push_back(std::make_unique<EnergyStock>("CTRA", 28.0));
    return stocks;
}
