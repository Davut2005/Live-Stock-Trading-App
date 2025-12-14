#pragma once
#include <exception>
#include <string>

class StockException : public std::exception {
protected:
    std::string message;

public:
    explicit StockException(std::string msg)
        : message(std::move(msg)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
