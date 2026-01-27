#pragma once
#include "StockException.h"
#include <string>
#include <vector>

class SystemCriticalException : public StockException {
public:
    enum class Component {
        MEMORY_MANAGER,
        THREAD_POOL,
        FILE_SYSTEM,
        KERNEL_INTERFACE
    };

private:
    Component sourceComponent;
    std::vector<std::string> stackTrace;
    long long systemCode;

public:
    SystemCriticalException(const std::string& msg, Component comp, long long sysCode);

    void captureStackTrace();
    std::string getComponentString() const;
    std::string getStackTraceDump() const;
    
    // Suggests if immediate termination is required
    bool requiresImmediateShutdown() const;
};
