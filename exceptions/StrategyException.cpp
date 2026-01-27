#include "StrategyException.h"
#include <sstream>

StrategyException::StrategyException(const std::string& msg, const std::string& strategy)
    : StockException(msg), strategyName(strategy), signalType("NONE") {
}

void StrategyException::setSignalContext(const std::string& signal) {
    signalType = signal;
}

void StrategyException::addIndicatorValue(const std::string& name, double value) {
    indicators[name] = value;
}

std::string StrategyException::getStrategyName() const {
    return strategyName;
}

std::string StrategyException::getSignalDebug() const {
    return "Failed processing signal: " + signalType;
}

std::string StrategyException::dumpStrategyState() const {
    std::stringstream ss;
    ss << "State Dump for Strategy: " << strategyName << "\n";
    ss << "Current Signal: " << signalType << "\n";
    ss << "Indicator Values:\n";
    for (const auto& pair : indicators) {
        ss << "  [ " << pair.first << " ] = " << pair.second << "\n";
    }
    ss << "End Dump";
    return ss.str();
}
