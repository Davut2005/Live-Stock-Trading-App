// HealthStock.h
#pragma once
#include "Stock.h"

class HealthStock : public Stock {
public:
    using Stock::Stock;
    std::string getType() const override { return "Health"; }
};
