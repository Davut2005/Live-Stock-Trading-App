#pragma once
#include <chrono>
#include <string>

class ScopeTimer {
private:
  std::string label;
  std::chrono::steady_clock::time_point start;

public:
  explicit ScopeTimer(std::string label);
  ~ScopeTimer();
};
