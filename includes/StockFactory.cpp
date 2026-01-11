#include "StockFactory.h"
#include "TechStock.h"
#include "CryptoStock.h"
#include "EnergyStock.h"
#include "HealthStock.h"
#include "../exceptions/StockException.h"

std::unique_ptr<Stock> StockFactory::create(
    const std::string& type,
    const std::string& name,
    double price,
    int quantity
) {
    if (type == "tech")
        return std::make_unique<TechStock>(name, price, quantity);

    if (type == "crypto")
        return std::make_unique<CryptoStock>(name, price, quantity);

    if (type == "energy")
        return std::make_unique<EnergyStock>(name, price, quantity);

    if (type == "health")
        return std::make_unique<HealthStock>(name, price, quantity);

    throw StockException("Invalid type of stock");
}
