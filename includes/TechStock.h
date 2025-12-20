#pragma once
#include "Stock.h"

class TechStock : public Stock {
public:
  using Stock::Stock;
  std::string getType() const override { return "Tech"; }
  std::unique_ptr<Stock> clone() const override {
    return std::make_unique<TechStock>(*this); 
  }
};