#pragma once
#include "Portfolio.h"
#include "TransactionLog.h"

class Trader {
private: 
  std::string m_name;
  double balance;
  Portfolio portfolio;
  TransactionLog transactionLog; 

public:
  Trader(const std::string &name, double b);
  void buyStock(std::unique_ptr<Stock> s, int quantity);
  void sellStock(const std::string &name, int quantity, double price);
  void display() const;
  double getBalance() const;
};