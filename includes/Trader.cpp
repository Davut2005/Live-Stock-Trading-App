#include "Trader.h"
#include "../exceptions/StockErrors.h"
#include "../exceptions/StockException.h"
#include "./Logger.h"
#include "./Transaction.h"
#include <iostream>

Trader::Trader(const std::string &traderName, double b)
    : m_name(traderName), balance(b) {}

void Trader::buyStock(std::unique_ptr<Stock> s, int quantity) {

  std::string ticker = s->getName();
  double price = s->getPrice();

  double cost = s->getPrice() * quantity;
  if (balance < cost) {
    throw InsufficientBalanceException();
  }
  balance -= cost;
  s->addQuantity(quantity);
  portfolio.addStock(std::move(s));

  transactionLog.add(Transaction(Transaction::Type::BUY, quantity, price));

  Logger::instance().info("BUY transaction recorded for " + ticker + " x" +
                          std::to_string(quantity));
}

void Trader::sellStock(const std::string &name, int quantity, double price) {
  Stock *s = portfolio.findStock(name);
  if (!s || s->getQuantity() < quantity)
    return;
  s->removeQuantity(quantity);
  balance += quantity * price;
  if (s->getQuantity() == 0)
    portfolio.removeStock(name);

  transactionLog.add(Transaction(Transaction::Type::SELL, quantity, price));

  Logger::instance().info("SELL transaction recorded for " +
                          std::to_string(quantity));
}

void Trader::display() const {
  std::cout << "Trader: " << m_name << " | Balance: " << balance << '\n';
  portfolio.showAll();
}

double Trader::getBalance() const {
    return balance;
}