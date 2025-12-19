#include "TransactionLog.h"
#include <fstream>
#include <iostream>

void TransactionLog::add(const Transaction &t) { history.push_back(t); }

void TransactionLog::saveToFile(const std::string &path) const {

  std::ofstream file(path, std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Failed to open log file: " << path << "\n";
    return;
  }

  for (const auto &t : history) {
    file << t.toString() << "\n";
  }
}

void TransactionLog::loadFromFile(const std::string &path) {

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "No previous transaction file found.\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << "\n";
  }
}
