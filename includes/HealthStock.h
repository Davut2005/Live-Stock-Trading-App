#pragma once
#include "Stock.h"
#include <memory>

class HealthStock : public Stock {
public:
    // Constructor
    explicit HealthStock(const std::string& n, double p = 0.0, int q = 0);

    // Copy constructor
    HealthStock(const HealthStock& other);

    // Destructor
    ~HealthStock() override;

    // Implement pure virtual functions from Stock
    std::string getType() const override;

    std::unique_ptr<Stock> clone() const override;

    void display() const override;
};
