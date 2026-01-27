#pragma once
#include "StockException.h"
#include <map>
#include <string>

class StrategyException : public StockException {
private:
    std::string strategyName;
    std::string signalType;
    std::map<std::string, double> indicators;

public:
    StrategyException(const std::string& msg, const std::string& strategy);

    void setSignalContext(const std::string& signal);
    void addIndicatorValue(const std::string& name, double value);

    std::string getStrategyName() const;
    std::string getSignalDebug() const;
    
    // Generates a 'core dump' string of the strategy state
    std::string dumpStrategyState() const;
};
