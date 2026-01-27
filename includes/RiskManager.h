#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include "Trader.h"
#include "Order.h"

class RiskManager {
private:

    double maxSingleTradeValue;

public:
    RiskManager(double maxPosition, double maxTrade);

    bool validateOrder(const Trader& trader, const Order& order, double price) const;
};

#endif
