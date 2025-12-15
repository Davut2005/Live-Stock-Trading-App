#include "Stock.h"
#include "../exceptions/StockException.h"
#include "../exceptions/StockErrors.h"

Stock::Stock() : name("Unknown"), price(0.0), quantity(0) {}

int Stock::totalStocks = 0;

Stock::Stock(const std::string& n, double p, int q)
: name(n), price(p), quantity(q) {
    totalStocks++; 
}


Stock::Stock(const Stock& other)
: name(other.name), price(other.price), quantity(other.quantity) {}


Stock& Stock::operator=(const Stock& other) {
if (this != &other) {
name = other.name;
price = other.price;
quantity = other.quantity;
}
return *this;
}


Stock::Stock(Stock&& other) noexcept
: name(std::move(other.name)), price(other.price), quantity(other.quantity) {}


Stock& Stock::operator=(Stock&& other) noexcept {
if (this != &other) {
name = std::move(other.name);
price = other.price;
quantity = other.quantity;
}
return *this;
}


Stock::~Stock() = default;


const std::string& Stock::getName() const { return name; }
double Stock::getPrice() const { return price; }
int Stock::getQuantity() const { return quantity; }


void Stock::updatePrice(double percentChange) {
    if (percentChange < -100.0) { // cannot reduce price below 0
        throw InvalidPriceException();
    }
    price *= (1 + percentChange / 100);
}


double Stock::totalValue() const {
return price * quantity;
}


void Stock::addQuantity(int q) {
    if (q <= 0) throw InvalidQuantityException();
    quantity += q;
}


void Stock::removeQuantity(int q) {
if (q <= 0 || q > quantity) throw InvalidQuantityException();
    quantity -= q;
}


void Stock::display() const {
std::cout << getType() << " Stock: " << name
<< " | Price: " << price
<< " | Quantity: " << quantity
<< " | Value: " << totalValue() << '\n';
}


std::ostream& operator<<(std::ostream& os, const Stock& s) {
os << s.getType() << "(" << s.name << ", " << s.price << ", " << s.quantity << ")";
return os;
}