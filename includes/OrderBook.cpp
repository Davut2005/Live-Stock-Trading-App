#include "OrderBook.h"
#include <algorithm>

void OrderBook::addOrder(const std::shared_ptr<Order>& order) {
    if (order->getType() == OrderType::BUY)
        buyOrders.push_back(order);
    else
        sellOrders.push_back(order);
}

void OrderBook::removeOrder(const std::shared_ptr<Order>& order) {
    auto& container = (order->getType() == OrderType::BUY) ? buyOrders : sellOrders;

    container.erase(
        std::remove(container.begin(), container.end(), order),
        container.end()
    );
}

const std::vector<std::shared_ptr<Order>>& OrderBook::getBuyOrders() const {
    return buyOrders;
}

const std::vector<std::shared_ptr<Order>>& OrderBook::getSellOrders() const {
    return sellOrders;
}
