#pragma once
#include "StockException.h"
#include <string>
#include <map>

class OrderExecutionException : public StockException {
public:
    enum class FailureReason {
        INSUFFICIENT_FUNDS,
        MARKET_CLOSED,
        PRICE_OUT_OF_BOUNDS,
        NETWORK_TIMEOUT,
        EXCHANGE_REJECTED,
        UNKNOWN
    };

private:
    std::string orderId;
    FailureReason reason;
    double attemptedPrice;
    int attemptedQuantity;
    std::map<std::string, std::string> orderState;

public:
    OrderExecutionException(const std::string& msg, const std::string& oid, FailureReason r);

    void setAttemptedDetails(double price, int quantity);
    void addStateDetail(const std::string& key, const std::string& value);

    std::string getOrderId() const;
    std::string getReasonString() const;
    
    std::string getDebugDump() const;
    bool shouldRetry() const;
};
