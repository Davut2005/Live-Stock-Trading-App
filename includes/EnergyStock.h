#pragma once
#include "Stock.h"


class EnergyStock : public Stock {
public:
using Stock::Stock;
std::string getType() const override { return "Energy"; }
};