#include "SellOrder.h"
#include "Trader.h"

void SellOrder::execute(Trader& trader, Portfolio& portfolio, double price) const {
    portfolio.sellStock(stockName, quantity);
    trader.credit(quantity * price);
}
