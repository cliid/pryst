#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

namespace pryst {

enum class LogLevel {
    DEBUG,
    INFO,
    ERROR
};

class Logger {
public:
    static Logger& getInstance();
    void debug(const std::string& msg);
    void error(const std::string& msg);
    void info(const std::string& msg);
    void setDebugEnabled(bool enabled);
    bool isDebugEnabled() const;

    // String formatting support
    template<typename... Args>
    std::string format(const std::string& fmt, Args... args) {
        return formatImpl(fmt, std::forward<Args>(args)...);
    }

private:
    Logger();
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& msg);
    std::string formatImpl(const std::string& fmt) { return fmt; }

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

    bool debugEnabled;
    std::string getLogLevelString(LogLevel level) const;
};

} // namespace pryst
