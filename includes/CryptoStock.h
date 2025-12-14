#pragma once
#include "Stock.h"


class CryptoStock : public Stock {
public:
using Stock::Stock;
void updatePrice(double percentChange) override {
Stock::updatePrice(percentChange * 1.5);
}
std::string getType() const override { return "Crypto"; }
};