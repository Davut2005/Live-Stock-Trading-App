#pragma once
#include <chrono>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

class Logger {
private:
  std::ofstream file;
  std::mutex mtx;

  Logger();
  ~Logger();

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  std::string timestamp();

public:
  static Logger &instance();
  static Logger &getInstance() { return instance(); }

  void info(const std::string &msg);
  void error(const std::string &msg);
  void trade(const std::string &msg);
  void logRaw(const std::string &msg);
  void log(const std::string &msg);
};
