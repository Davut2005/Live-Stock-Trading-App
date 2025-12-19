#include "SellOrder.h"

void SellOrder::execute(Portfolio& portfolio) const {
    portfolio.sellStock(stockName, quantity);
}
