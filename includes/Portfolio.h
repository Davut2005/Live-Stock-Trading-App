#pragma once
#include <vector>
#include <memory>
#include <iomanip>
#include "Stock.h"


class Portfolio {
std::vector<std::unique_ptr<Stock>> stocks;


public:
Portfolio() = default;
Portfolio(const Portfolio& other);
Portfolio& operator=(Portfolio other);

void showTechStocks() const;
void addStock(std::unique_ptr<Stock> stock);
Stock* findStock(const std::string& name);
void removeStock(const std::string& name);
double totalValue() const;
void showAll() const;
};