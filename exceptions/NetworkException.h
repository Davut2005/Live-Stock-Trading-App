#pragma once
#include "StockException.h"
#include <string>
#include <vector>

class NetworkException : public StockException {
public:
    enum class SocketError {
        CONNECTION_REFUSED = 101,
        HOST_UNREACHABLE = 103,
        TIMED_OUT = 110,
        CONNECTION_RESET = 111,
        UNKNOWN = 999
    };

private:
    std::string endpoint;
    int port;
    SocketError socketError;
    int retryCount;
    double latencyms;

public:
    NetworkException(const std::string& msg, const std::string& host, int p, SocketError err);

    void setRetryCount(int count);
    void setLatency(double ms);

    std::string getEndpoint() const;
    int getPort() const;
    SocketError getSocketError() const;
    
    std::string getDiagnostics() const;
    std::string getRecoveryAction() const;
};
