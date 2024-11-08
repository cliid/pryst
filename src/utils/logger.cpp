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

Logger::Logger() : currentLevel(LogLevel::INFO), useColor(true) {
    // Initialize default configurations for each log level
    logConfigs[LogLevel::TRACE] = {false, &std::cout, true, "\033[1;35mTRACE\033[0m"}; // Magenta
    logConfigs[LogLevel::DEBUG] = {false, &std::cout, true, "\033[1;34mDEBUG\033[0m"}; // Blue
    logConfigs[LogLevel::INFO]  = {true,  &std::cout, true, "\033[1;32mINFO\033[0m"};  // Green
    logConfigs[LogLevel::WARN]  = {true,  &std::cerr, true, "\033[1;33mWARN\033[0m"};  // Yellow
    logConfigs[LogLevel::ERROR] = {true,  &std::cerr, true, "\033[1;31mERROR\033[0m"}; // Red
}

Logger::~Logger() {
    if (logFile) {
        logFile->close();
    }
}

void Logger::trace(const std::string& msg, const std::string& file, int line) {
    log(LogLevel::TRACE, msg, file, line);
}

void Logger::debug(const std::string& msg, const std::string& file, int line) {
    log(LogLevel::DEBUG, msg, file, line);
}

void Logger::info(const std::string& msg) {
    log(LogLevel::INFO, msg);
}

void Logger::warn(const std::string& msg) {
    log(LogLevel::WARN, msg);
}

void Logger::error(const std::string& msg) {
    log(LogLevel::ERROR, msg);
}

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
    // Enable all levels above or equal to the current level
    for (auto& config : logConfigs) {
        config.second.enabled = config.first >= currentLevel;
    }
}

void Logger::setDebugEnabled(bool enabled) {
    logConfigs[LogLevel::DEBUG].enabled = enabled;
    if (enabled && currentLevel > LogLevel::DEBUG) {
        currentLevel = LogLevel::DEBUG;
    }
}

void Logger::setLogFile(const std::string& filename) {
    logFile = std::make_unique<std::ofstream>(filename, std::ios::app);
    if (!logFile->is_open()) {
        error("Failed to open log file: " + filename);
        logFile.reset();
    }
}

void Logger::setColorEnabled(bool enabled) {
    useColor = enabled;
}

bool Logger::isDebugEnabled() const {
    return logConfigs.at(LogLevel::DEBUG).enabled;
}

LogLevel Logger::getLogLevel() const {
    return currentLevel;
}

std::string Logger::getColorCode(LogLevel level) const {
    if (!useColor) return "";
    return logConfigs.at(level).prefix;
}

std::string Logger::getSourceLocation(const std::string& file, int line) const {
    if (file.empty()) return "";
    std::stringstream ss;
    ss << " (" << file << ":" << line << ")";
    return ss.str();
}

void Logger::log(LogLevel level, const std::string& msg, const std::string& file, int line) {
    auto& config = logConfigs.at(level);
    if (!config.enabled || level < currentLevel) return;

    // Get current time
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    // Format the log message
    std::stringstream formatted;
    formatted << "[" << timestamp.str() << "] "
              << (useColor ? config.prefix : getLogLevelString(level))
              << ": " << msg
              << getSourceLocation(file, line);

    // Output to console
    *config.stream << formatted.str() << std::endl;

    // Output to file if enabled
    if (logFile && logFile->is_open()) {
        *logFile << formatted.str() << std::endl;
    }
}

std::string Logger::getLogLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

} // namespace pryst
