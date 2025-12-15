#pragma once
#include <string>
#include <iostream>
#include <memory>

class Stock {
protected:
    std::string name;
    double price;
    int quantity;
   
    static int totalStocks;

public:
    Stock();
    explicit Stock(const std::string& n, double p = 0.0, int q = 0);
    Stock(const Stock& other);
    Stock& operator=(const Stock& other);
    Stock(Stock&& other) noexcept;
    Stock& operator=(Stock&& other) noexcept;
    virtual ~Stock();
    static int getTotalStocks() { return totalStocks; }

const std::string& getName() const;
double getPrice() const;
int getQuantity() const;


virtual void updatePrice(double percentChange);
double totalValue() const;
void addQuantity(int q);
void removeQuantity(int q);


virtual void display() const;
virtual std::string getType() const = 0;

virtual std::unique_ptr<Stock> clone() const = 0;  

friend std::ostream& operator<<(std::ostream& os, const Stock& s);
};

int Stock::totalStocks = 0;

Stock::Stock(const std::string& n, double p, int q) : name(n), price(p), quantity(q) {
    totalStocks++; 
}