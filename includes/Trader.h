#pragma once
#include "Portfolio.h"


class Trader {
std::string m_name;
double balance;
Portfolio portfolio;


public:
Trader(const std::string& name, double b);
void buyStock(std::unique_ptr<Stock> s, int quantity);
void sellStock(const std::string& name, int quantity, double price);
void display() const;
};