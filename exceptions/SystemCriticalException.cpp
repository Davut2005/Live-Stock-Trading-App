#include "SystemCriticalException.h"
#include <sstream>

SystemCriticalException::SystemCriticalException(const std::string& msg, Component comp, long long sysCode)
    : StockException(msg), sourceComponent(comp), systemCode(sysCode) {
    // Automatically attempt to capture stack trace on creation
    captureStackTrace();
}

void SystemCriticalException::captureStackTrace() {
    // Simulate stack trace capture since we don't have a reliable cross-platform way 
    // without heavy dependencies like boost::stacktrace or backward-cpp in this environment.
    stackTrace.clear();
    stackTrace.push_back("SystemCriticalException::captureStackTrace() at 0x7FF001");
    stackTrace.push_back("SystemCriticalException::SystemCriticalException() at 0x7FF024");
    stackTrace.push_back("CoreSystem::raiseCriticalError() at 0x7FF099");
    stackTrace.push_back("main_loop() at 0x7FF102");
    stackTrace.push_back("_start() at 0x7FF200");
}

std::string SystemCriticalException::getComponentString() const {
    switch (sourceComponent) {
        case Component::MEMORY_MANAGER: return "Memory Manager";
        case Component::THREAD_POOL: return "Thread Pool";
        case Component::FILE_SYSTEM: return "File System";
        case Component::KERNEL_INTERFACE: return "Kernel Interface";
        default: return "Unknown Core Component";
    }
}

std::string SystemCriticalException::getStackTraceDump() const {
    std::stringstream ss;
    ss << "CRITICAL FAILURE IN [" << getComponentString() << "]\n";
    ss << "System Code: " << systemCode << "\n";
    ss << "Stack Trace:\n";
    for (size_t i = 0; i < stackTrace.size(); ++i) {
        ss << "  [" << i << "] " << stackTrace[i] << "\n";
    }
    return ss.str();
}

bool SystemCriticalException::requiresImmediateShutdown() const {
    // Most system critical errors preserve data integrity only if stopped immediately
    return true;
}
