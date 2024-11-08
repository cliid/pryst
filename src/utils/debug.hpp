#pragma once

#include <iostream>
#include <string>

#ifdef NDEBUG
#define PRYST_DEBUG(x)
#else
#define PRYST_DEBUG(x) std::cerr << "[DEBUG] " << x << std::endl
#endif

#define PRYST_ERROR(x) std::cerr << "[ERROR] " << x << std::endl
#define PRYST_WARN(x) std::cerr << "[WARN] " << x << std::endl

namespace pryst {
namespace debug {

inline void logError(const std::string& message) {
    PRYST_ERROR(message);
}

inline void logWarning(const std::string& message) {
    PRYST_WARN(message);
}

inline void logDebug(const std::string& message) {
    PRYST_DEBUG(message);
}

} // namespace debug
} // namespace pryst
