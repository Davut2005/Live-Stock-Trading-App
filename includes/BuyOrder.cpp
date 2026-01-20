#include "BuyOrder.h"
#include "Trader.h"

void BuyOrder::execute(Trader& trader, Portfolio& portfolio, double price) const {
    portfolio.buyStock(stockName, quantity);
    trader.debit(quantity * price);
}
