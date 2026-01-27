#include "OrderExecutionException.h"
#include <sstream>

OrderExecutionException::OrderExecutionException(const std::string& msg, const std::string& oid, FailureReason r)
    : StockException(msg), orderId(oid), reason(r), attemptedPrice(0.0), attemptedQuantity(0) {
}

void OrderExecutionException::setAttemptedDetails(double price, int quantity) {
    attemptedPrice = price;
    attemptedQuantity = quantity;
}

void OrderExecutionException::addStateDetail(const std::string& key, const std::string& value) {
    orderState[key] = value;
}

std::string OrderExecutionException::getOrderId() const {
    return orderId;
}

std::string OrderExecutionException::getReasonString() const {
    switch (reason) {
        case FailureReason::INSUFFICIENT_FUNDS: return "Insufficient Funds";
        case FailureReason::MARKET_CLOSED: return "Market Closed";
        case FailureReason::PRICE_OUT_OF_BOUNDS: return "Price Out of Bounds";
        case FailureReason::NETWORK_TIMEOUT: return "Network Timeout";
        case FailureReason::EXCHANGE_REJECTED: return "Exchange Rejected";
        default: return "Unknown";
    }
}

std::string OrderExecutionException::getDebugDump() const {
    std::stringstream ss;
    ss << "Order Exception Dump [ID: " << orderId << "]\n";
    ss << "Reason: " << getReasonString() << "\n";
    ss << "Attempted: " << attemptedQuantity << " @ " << attemptedPrice << "\n";
    ss << "State Details:\n";
    for (const auto& pair : orderState) {
        ss << "  " << pair.first << ": " << pair.second << "\n";
    }
    return ss.str();
}

bool OrderExecutionException::shouldRetry() const {
    return reason == FailureReason::NETWORK_TIMEOUT || reason == FailureReason::EXCHANGE_REJECTED;
}
