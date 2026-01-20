#pragma once
#include "Order.h"
#include "Portfolio.h"

class SellOrder : public Order {
public:
  SellOrder(const std::string &name, int qty) : Order(name, qty) {}

  OrderType getType() const override { return OrderType::SELL; }

  void execute(class Trader &trader, class Portfolio &portfolio, double price) const override;
};
