#include "MarketDataException.h"
#include <iomanip>
#include <ctime>

MarketDataException::MarketDataException(const std::string& msg, const std::string& source, const std::string& sym, int code)
    : StockException(msg), dataSource(source), symbol(sym), timestamp(std::time(nullptr)), errorCode(code), isCritical(false) {
}

void MarketDataException::setInvalidSnapshot(const std::string& snapshot) {
    invalidDataSnapshot = snapshot;
}

void MarketDataException::setCritical(bool critical) {
    isCritical = critical;
}

std::string MarketDataException::getDataSource() const {
    return dataSource;
}

std::string MarketDataException::getSymbol() const {
    return symbol;
}

long long MarketDataException::getTimestamp() const {
    return timestamp;
}

int MarketDataException::getErrorCode() const {
    return errorCode;
}

bool MarketDataException::isCriticalError() const {
    return isCritical;
}

std::string MarketDataException::getFormattedReport() const {
    std::stringstream ss;
    ss << "=== Market Data Exception Report ===\n";
    ss << "Time: " << timestamp << "\n";
    ss << "Message: " << message << "\n";
    ss << "Source: " << dataSource << "\n";
    ss << "Symbol: " << symbol << "\n";
    ss << "Error Code: " << errorCode << "\n";
    ss << "Severity: " << (isCritical ? "CRITICAL" : "WARNING") << "\n";
    
    if (!invalidDataSnapshot.empty()) {
        ss << "Snapshot: " << invalidDataSnapshot << "\n";
    }
    ss << "==================================";
    return ss.str();
}

std::string MarketDataException::getLogEntry() const {
    std::stringstream ss;
    ss << "[ERROR][MARKET_DATA][" << timestamp << "] " 
       << message << " | Source=" << dataSource 
       << " | Sym=" << symbol 
       << " | Code=" << errorCode;
    return ss.str();
}
