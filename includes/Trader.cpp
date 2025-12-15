#include "Trader.h"
#include <iostream>


Trader::Trader(const std::string& traderName, double b) : name(traderName), balance(b) {}


void Trader::buyStock(std::unique_ptr<Stock> s, int quantity) {
double cost = s->getPrice() * quantity;
if (balance >= cost) {
balance -= cost;
s->addQuantity(quantity);
portfolio.addStock(std::move(s));
}
}


void Trader::sellStock(const std::string& name, int quantity, double price) {
Stock* s = portfolio.findStock(name);
if (!s || s->getQuantity() < quantity) return;
s->removeQuantity(quantity);
balance += quantity * price;
if (s->getQuantity() == 0)
portfolio.removeStock(name);
}


void Trader::display() const {
std::cout << "Trader: " << name << " | Balance: " << balance << '\n';
portfolio.showAll();
}