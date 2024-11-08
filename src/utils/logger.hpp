#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <map>

namespace pryst {

enum class LogLevel {
    TRACE,  // Most detailed level
    DEBUG,  // Development debugging
    INFO,   // General information
    WARN,   // Warnings
    ERROR   // Errors
};

struct LogConfig {
    bool enabled;
    std::ostream* stream;
    bool useColor;
    std::string prefix;
};

class Logger {
public:
    static Logger& getInstance();

    // Logging methods
    void trace(const std::string& msg, const std::string& file = "", int line = 0);
    void debug(const std::string& msg, const std::string& file = "", int line = 0);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);

    // Configuration methods
    void setLogLevel(LogLevel level);
    void setDebugEnabled(bool enabled);
    void setLogFile(const std::string& filename);
    void setColorEnabled(bool enabled);
    bool isDebugEnabled() const;
    LogLevel getLogLevel() const;

    // String formatting support
    template<typename... Args>
    std::string format(const std::string& fmt, Args... args) {
        return formatImpl(fmt, std::forward<Args>(args)...);
    }

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& msg, const std::string& file = "", int line = 0);
    std::string formatImpl(const std::string& fmt) { return fmt; }
    std::string getLogLevelString(LogLevel level) const;
    std::string getColorCode(LogLevel level) const;
    std::string getSourceLocation(const std::string& file, int line) const;

    template<typename T, typename... Args>
    std::string formatImpl(const std::string& fmt, T value, Args... args) {
        std::string result;
        size_t pos = 0;
        size_t lastPos = 0;

        while ((pos = fmt.find("{}", lastPos)) != std::string::npos) {
            result += fmt.substr(lastPos, pos - lastPos);
            std::stringstream ss;
            ss << value;
            result += ss.str();
            lastPos = pos + 2;
            return result + formatImpl(fmt.substr(lastPos), args...);
        }

        return fmt;
    }

    LogLevel currentLevel;
    std::map<LogLevel, LogConfig> logConfigs;
    std::unique_ptr<std::ofstream> logFile;
    bool useColor;
};

// Debug macros with source location
#define PRYST_TRACE(msg) Logger::getInstance().trace(msg, __FILE__, __LINE__)
#define PRYST_DEBUG(msg) Logger::getInstance().debug(msg, __FILE__, __LINE__)
#define PRYST_INFO(msg)  Logger::getInstance().info(msg)
#define PRYST_WARN(msg)  Logger::getInstance().warn(msg)
#define PRYST_ERROR(msg) Logger::getInstance().error(msg)

} // namespace pryst
