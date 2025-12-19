#pragma once
#include "Order.h"
#include "Portfolio.h"

class BuyOrder : public Order {
public:
    BuyOrder(const std::string& name, int qty)
        : Order(name, qty) {}

    OrderType getType() const override {
        return OrderType::BUY;
    }

    void execute(Portfolio& portfolio) const override;
};
