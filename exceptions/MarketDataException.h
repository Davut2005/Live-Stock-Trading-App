#pragma once
#include "StockException.h"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

class MarketDataException : public StockException {
private:
    std::string dataSource;
    std::string symbol;
    long long timestamp;
    int errorCode;
    std::string invalidDataSnapshot;
    bool isCritical;

public:
    MarketDataException(const std::string& msg, const std::string& source, const std::string& sym, int code);

    // Setters for additional context
    void setInvalidSnapshot(const std::string& snapshot);
    void setCritical(bool critical);

    // Getters
    std::string getDataSource() const;
    std::string getSymbol() const;
    long long getTimestamp() const;
    int getErrorCode() const;
    bool isCriticalError() const;

    // Detailed reporting
    std::string getFormattedReport() const;
    std::string getLogEntry() const;
};
