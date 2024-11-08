#include "logger.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace pryst {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : debugEnabled(false) {}

void Logger::debug(const std::string& msg) {
    if (debugEnabled) {
        log(LogLevel::DEBUG, msg);
    }
}

void Logger::error(const std::string& msg) {
    log(LogLevel::ERROR, msg);
}

void Logger::info(const std::string& msg) {
    log(LogLevel::INFO, msg);
}

void Logger::setDebugEnabled(bool enabled) {
    debugEnabled = enabled;
}

bool Logger::isDebugEnabled() const {
    return debugEnabled;
}

void Logger::log(LogLevel level, const std::string& msg) {
    // Get current time
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    // Determine log level prefix and output stream
    std::string prefix;
    std::ostream* out = &std::cout;

    switch (level) {
        case LogLevel::ERROR:
            prefix = "\033[1;31mERROR\033[0m";  // Red, bold
            out = &std::cerr;
            break;
        case LogLevel::INFO:
            prefix = "\033[1;32mINFO\033[0m";   // Green, bold
            break;
        case LogLevel::DEBUG:
            if (!debugEnabled) return;
            prefix = "\033[1;34mDEBUG\033[0m";  // Blue, bold
            break;
    }

    // Format and output the log message
    *out << "[" << timestamp.str() << "] " << prefix << ": " << msg << std::endl;
}

} // namespace pryst
