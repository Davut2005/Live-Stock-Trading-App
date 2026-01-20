#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <vector>
#include <memory>
#include "Order.h"

class OrderBook {
private:
    std::vector<std::shared_ptr<Order>> buyOrders;
    std::vector<std::shared_ptr<Order>> sellOrders;

public:
    void addOrder(const std::shared_ptr<Order>& order);
    void removeOrder(const std::shared_ptr<Order>& order);

    const std::vector<std::shared_ptr<Order>>& getBuyOrders() const;
    const std::vector<std::shared_ptr<Order>>& getSellOrders() const;
};

#endif
