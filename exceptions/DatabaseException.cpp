#include "DatabaseException.h"
#include <regex>

DatabaseException::DatabaseException(const std::string& msg, const std::string& dbInfo, int code)
    : StockException(msg), dbConnectionStr(dbInfo), dbErrorCode(code), connectionAlive(true) {
}

void DatabaseException::setQueryContext(const std::string& query) {
    failedQuery = query;
}

void DatabaseException::setConnectionState(bool alive) {
    connectionAlive = alive;
}

std::string DatabaseException::getSanitizedConnectionString() const {
    // Basic regex to hide password in connection string if present
    std::regex pwdRegex("(password=)([^;]+)");
    return std::regex_replace(dbConnectionStr, pwdRegex, "$1*****");
}

std::string DatabaseException::getSafeQueryLog() const {
    if (failedQuery.empty()) return "No Query Context";
    // Truncate if too long to prevent log flooding
    if (failedQuery.length() > 256) {
        return failedQuery.substr(0, 253) + "...";
    }
    return failedQuery;
}

int DatabaseException::getDbErrorCode() const {
    return dbErrorCode;
}

bool DatabaseException::isConnectionLost() const {
    return !connectionAlive;
}
