#include "RiskManager.h"

RiskManager::RiskManager(double maxPosition, double maxTrade)
    : maxSingleTradeValue(maxTrade) {
    (void)maxPosition; // Suppress unused parameter warning
}

bool RiskManager::validateOrder(const Trader& trader, const Order& order, double price) const {
    double tradeValue = order.getQuantity() * price;

    if (tradeValue > maxSingleTradeValue)
        return false;

    if (trader.getBalance() < tradeValue)
        return false;

    return true;
}
