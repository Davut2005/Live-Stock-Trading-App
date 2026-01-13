#include "Transaction.h"
#include <iomanip>
#include <sstream>

Transaction::Transaction(Type type, int quantity,
                         double price)
    : type(type), quantity(quantity), price(price),
      timestamp(std::chrono::system_clock::now()) {}

      
std::string Transaction::toString() const {
  std::stringstream ss;

  auto t = std::chrono::system_clock::to_time_t(timestamp);

  ss << (type == Type::BUY ? "BUY" : "SELL") << " | " 
     << " | Qty: " << quantity << " | Price: " << price
     << " | Time: " << std::put_time(std::localtime(&t), "%F %T");

  return ss.str();
}
