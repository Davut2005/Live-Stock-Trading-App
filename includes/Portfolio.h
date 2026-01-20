#pragma once
#include "./Order.h"
#include "Stock.h"
#include <iomanip>
#include <memory>
#include <vector>
#include <ostream>

class Portfolio {
  std::vector<std::unique_ptr<Stock>> stocks;

public:
  Portfolio() = default;
  Portfolio(const Portfolio &other);
  Portfolio &operator=(Portfolio other);

  void showTechStocks() const;
  void addStock(std::unique_ptr<Stock> stock);
  Stock *findStock(const std::string &name);
  void removeStock(const std::string &name);
  double totalValue() const;
  void showAll() const;
  void showAllToStream(std::ostream& os) const;

  void buyStock(const std::string &name, int qty);
  void sellStock(const std::string &name, int qty);
  const std::vector<std::unique_ptr<Stock>>& getStocks() const;
};