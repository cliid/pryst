#include "debug.hpp"

namespace pryst {

static bool debugEnabled = false;

bool isDebugEnabled() {
    return debugEnabled;
}

void setDebugEnabled(bool enabled) {
    debugEnabled = enabled;
}

} // namespace pryst
