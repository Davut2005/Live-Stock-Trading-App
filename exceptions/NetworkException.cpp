#include "NetworkException.h"
#include <sstream>

NetworkException::NetworkException(const std::string& msg, const std::string& host, int p, SocketError err)
    : StockException(msg), endpoint(host), port(p), socketError(err), retryCount(0), latencyms(0.0) {
}

void NetworkException::setRetryCount(int count) {
    retryCount = count;
}

void NetworkException::setLatency(double ms) {
    latencyms = ms;
}

std::string NetworkException::getEndpoint() const {
    return endpoint;
}

int NetworkException::getPort() const {
    return port;
}

NetworkException::SocketError NetworkException::getSocketError() const {
    return socketError;
}

std::string NetworkException::getDiagnostics() const {
    std::stringstream ss;
    ss << "Network Failure: " << message << "\n"
       << "Target: " << endpoint << ":" << port << "\n"
       << "Error Code: " << static_cast<int>(socketError) << "\n"
       << "Observed Latency: " << latencyms << "ms\n"
       << "Retries Attempted: " << retryCount;
    return ss.str();
}

std::string NetworkException::getRecoveryAction() const {
    switch (socketError) {
        case SocketError::CONNECTION_REFUSED:
            return "Wait 5s and check if service is running.";
        case SocketError::HOST_UNREACHABLE:
            return "Check local network interface connection.";
        case SocketError::TIMED_OUT:
            return "Increase timeout threshold or use exponential backoff.";
        case SocketError::CONNECTION_RESET:
            return "Immediate retry possible.";
        default:
            return "Manual intervention required.";
    }
}
