#pragma once
#include "StockException.h"
#include <string>

class DatabaseException : public StockException {
private:
    std::string dbConnectionStr;
    std::string failedQuery;
    int dbErrorCode;
    bool connectionAlive;

public:
    DatabaseException(const std::string& msg, const std::string& dbInfo, int code);

    void setQueryContext(const std::string& query);
    void setConnectionState(bool alive);

    std::string getSanitizedConnectionString() const;
    std::string getSafeQueryLog() const;
    int getDbErrorCode() const;

    bool isConnectionLost() const;
};
