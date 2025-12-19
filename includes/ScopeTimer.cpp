#include "ScopeTimer.h"
#include "Logger.h"
#include <chrono>
#include <string>

ScopeTimer::ScopeTimer(std::string label)
    : label(std::move(label)), start(std::chrono::steady_clock::now()) {}

ScopeTimer::~ScopeTimer() {
  auto end = std::chrono::steady_clock::now();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();

  Logger::instance().info(label + " executed in " + std::to_string(ms) + "ms");
}
