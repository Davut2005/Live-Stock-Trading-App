#pragma once
#include <string>

enum class OrderType { BUY, SELL };

class Order {
protected:
    std::string stockName;
    int quantity;

public:
    Order(const std::string& name, int qty)
        : stockName(name), quantity(qty) {}

    virtual ~Order() = default;

    const std::string& getStockName() const { return stockName; }
    int getQuantity() const { return quantity; }

    virtual OrderType getType() const = 0;

    virtual void execute(class Portfolio& portfolio) const = 0;
};
