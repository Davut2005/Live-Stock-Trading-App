#pragma once

#include "Transaction.h"
#include <string>
#include <vector>

class TransactionLog {

private:
  std::vector<Transaction> history;

public:
  void add(const Transaction &t);
  void saveToFile(const std::string &path) const;
  void loadFromFile(const std::string &path);

  const std::vector<Transaction> &getHistory() const { return history; }
};
