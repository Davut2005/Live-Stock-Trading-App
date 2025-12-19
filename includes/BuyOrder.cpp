#include "BuyOrder.h"

void BuyOrder::execute(Portfolio& portfolio) const {
    portfolio.buyStock(stockName, quantity);
}
