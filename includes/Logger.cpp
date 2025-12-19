#include "Logger.h"
#include <iomanip>
#include <iostream>

Logger::Logger() {
  file.open("logs.txt", std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Logger failed to open log file." << std::endl;
  }
}

Logger::~Logger() {
  if (file.is_open()) {
    file.close();
  }
}

Logger &Logger::instance() {
  static Logger instance;
  return instance;
}

std::string Logger::timestamp() {
  auto now = std::chrono::system_clock::now();
  auto t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "]";
  return ss.str();
}

void Logger::logRaw(const std::string &msg) {
  std::lock_guard<std::mutex> lock(mtx);

  if (file.is_open()) {
    file << msg << std::endl;
  }
  std::cout << msg << std::endl;
}

void Logger::info(const std::string &msg) {
  logRaw(timestamp() + " [INFO] " + msg);
}

void Logger::error(const std::string &msg) {
  logRaw(timestamp() + " [ERROR] " + msg);
}

void Logger::trade(const std::string &msg) {
  logRaw(timestamp() + " [TRADE] " + msg);
}
