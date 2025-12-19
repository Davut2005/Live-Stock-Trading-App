#pragma once
#include <string>
#include <chrono>

class Transaction {

public:
    enum class Type { BUY, SELL };

private:
    Type type;
    int quantity;
    double price;
    std::chrono::system_clock::time_point timestamp;

public:
    Transaction(Type type,
        int quantity, double price);

    std::string toString() const;
    
    // getters if needed
    Type getType() const { return type; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }
};
