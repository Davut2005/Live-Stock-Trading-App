#include "TradingEngine.h"

TradingEngine::TradingEngine(MarketDataManager& md, RiskManager& rm)
    : marketData(md), riskManager(rm) {}

bool TradingEngine::executeOrder(
    Trader& trader,
    Portfolio& portfolio,
    const std::shared_ptr<Order>& order
) {
    double price = marketData.getLatestPrice(order->getStockSymbol());

    if (!riskManager.validateOrder(trader, *order, price)) {
        Logger::getInstance().log("Order rejected by RiskManager");
        return false;
    }

    order->execute(trader, portfolio, price);
    orderBook.addOrder(order);

    Logger::getInstance().log("Order executed successfully");
    return true;
}
