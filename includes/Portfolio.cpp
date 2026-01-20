#include "Portfolio.h"
#include "../exceptions/StockErrors.h"
#include "BuyOrder.h"
#include "Order.h"
#include "SellOrder.h"
#include "TechStock.h"
#include "Accumulator.h"

#include <algorithm>
#include <iostream>

Portfolio::Portfolio(const Portfolio &other) {
  for (const auto &s : other.stocks) {
    stocks.push_back(s->clone()); // virtual constructor
  }
}

void Portfolio::showTechStocks() const {
  for (const auto &s : stocks) {
    if (auto tech = dynamic_cast<TechStock *>(s.get())) {
      std::cout << "Tech stock found: ";
      tech->display();
    }
  }
}

Portfolio &Portfolio::operator=(Portfolio other) {
  std::swap(stocks, other.stocks);
  return *this;
}

void Portfolio::addStock(std::unique_ptr<Stock> stock) {
  stocks.push_back(std::move(stock));
}

Stock *Portfolio::findStock(const std::string &name) {
  for (auto &s : stocks)
    if (s->getName() == name)
      return s.get();
  return nullptr;
}

void Portfolio::removeStock(const std::string &name) {
  stocks.erase(std::remove_if(stocks.begin(), stocks.end(),
                              [&](const std::unique_ptr<Stock> &s) {
                                return s->getName() == name;
                              }),
               stocks.end());
}

double Portfolio::totalValue() const {
    Accumulator<double> valueAccumulator;   // instantiation #1 (double)

    for (const auto& s : stocks)
        valueAccumulator.add(s->totalValue());

    return valueAccumulator.sum();
}

void Portfolio::showAll() const {
    Accumulator<int> quantityAccumulator;   // instantiation #2 (int)

    for (const auto& s : stocks) {
        s->display();
        quantityAccumulator.add(s->getQuantity());
    }

    std::cout << "Total quantity of all stocks: "
              << quantityAccumulator.sum() << '\n';
}



void Portfolio::buyStock(const std::string &name, int qty) {
  auto stock = findStock(name);
  if (!stock)
    throw StockNotFoundException(name);

  stock->addQuantity(qty);
}

void Portfolio::sellStock(const std::string &name, int qty) {
  auto stock = findStock(name);
  if (!stock)
    throw StockNotFoundException(name);

  stock->removeQuantity(qty);
}

void Portfolio::showAllToStream(std::ostream& os) const 
{
    for (const auto& stock : stocks)  
    {
        os << stock->getName() 
           << " | Price: " << stock->getPrice() 
           << " | Qty: " << stock->getQuantity()
           << "\n";
    }
}
