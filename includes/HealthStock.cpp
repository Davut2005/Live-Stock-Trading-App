#include "HealthStock.h"
#include <iostream>

// Constructor
HealthStock::HealthStock(const std::string& n, double p, int q)
    : Stock(n, p, q) {}

// Copy constructor
HealthStock::HealthStock(const HealthStock& other)
    : Stock(other) {}

// Destructor
HealthStock::~HealthStock() = default;

// getType implementation
std::string HealthStock::getType() const {
    return "Health";
}

// clone implementation
std::unique_ptr<Stock> HealthStock::clone() const {
    return std::make_unique<HealthStock>(*this);
}

// display implementation
void HealthStock::display() const {
    std::cout << getType() << " Stock: " << name
              << " | Price: " << price
              << " | Quantity: " << quantity
              << " | Value: " << totalValue() << '\n';
}
