#pragma once
#include "StockException.h"

class InvalidPriceException : public StockException {
public:
  InvalidPriceException() : StockException("Invalid stock price") {}
};

class InvalidQuantityException : public StockException {
public:
  InvalidQuantityException() : StockException("Invalid stock quantity") {}
};

class InsufficientBalanceException : public StockException {
public:
  InsufficientBalanceException() : StockException("Insufficient balance") {}
};

class StockNotFoundException : public StockException {
public:
  StockNotFoundException(const std::string &name)
      : StockException("Stock not found: " + name) {}
};
