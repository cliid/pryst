#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cinttypes>
#include <cstdarg>

// Buffer size for formatted strings
constexpr size_t BUFFER_SIZE = 1024;

extern "C" {

// Format an integer with padding and alignment
char* pryst_format_int(int64_t value, int32_t width, char fill, bool leftAlign) {
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) return nullptr;

    // Create format string based on specifications
    char format[32];
    if (leftAlign) {
        snprintf(format, sizeof(format), "%%-%dld", width);
    } else if (fill == '0') {
        snprintf(format, sizeof(format), "%%0%dld", width);
    } else {
        snprintf(format, sizeof(format), "%%%dld", width);
    }

    snprintf(buffer, BUFFER_SIZE, format, value);
    return buffer;
}

// Format a boolean value
char* pryst_format_bool(bool value) {
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) return nullptr;

    snprintf(buffer, BUFFER_SIZE, "%s", value ? "true" : "false");
    return buffer;
}

// Format a float with precision, padding, and alignment
char* pryst_format_float(double value, int32_t precision, int32_t width, char fill, bool leftAlign) {
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) return nullptr;

    // Create format string based on specifications
    char format[32];
    char align = leftAlign ? '-' : '\0';
    char pad = (fill == '0' && !leftAlign) ? '0' : ' ';

    if (precision >= 0) {
        if (width > 0) {
            snprintf(format, sizeof(format), "%%%c%c%d.%df", align, pad, width, precision);
        } else {
            snprintf(format, sizeof(format), "%%.%df", precision);
        }
    } else {
        if (width > 0) {
            snprintf(format, sizeof(format), "%%%c%c%df", align, pad, width);
        } else {
            snprintf(format, sizeof(format), "%%f");
        }
    }

    snprintf(buffer, BUFFER_SIZE, format, value);
    return buffer;
}

// Format a string with padding and alignment
char* pryst_format_string(const char* str, int32_t width, char fill, bool leftAlign) {
    char* buffer = (char*)malloc(BUFFER_SIZE);
    if (!buffer) return nullptr;

    size_t len = strlen(str);
    size_t padLen = (width > len) ? (width - len) : 0;

    if (leftAlign) {
        strcpy(buffer, str);
        memset(buffer + len, fill, padLen);
        buffer[len + padLen] = '\0';
    } else {
        memset(buffer, fill, padLen);
        strcpy(buffer + padLen, str);
    }

    return buffer;
}

// Interpolate multiple values into a format string
char* pryst_interpolate_string(const char* format, int32_t count, ...) {
    char* result = (char*)malloc(BUFFER_SIZE);
    if (!result) return nullptr;
    result[0] = '\0';

    va_list args;
    va_start(args, count);

    size_t resultLen = 0;
    const char* curr = format;
    const char* lastCopied = format;

    while (*curr && resultLen < BUFFER_SIZE - 1) {
        if (*curr == '{' || (*curr == '$' && *(curr + 1) == '{')) {
            // Copy text before the interpolation
            size_t prefixLen = curr - lastCopied;
            if (prefixLen > 0 && resultLen + prefixLen < BUFFER_SIZE - 1) {
                strncat(result + resultLen, lastCopied, prefixLen);
                resultLen += prefixLen;
            }

            // Skip the opening brace(s)
            bool isExpr = *curr == '$';
            curr += isExpr ? 2 : 1;

            // Find the closing brace
            const char* end = strchr(curr, '}');
            if (!end) break;

            // Get the next formatted value
            if (count > 0) {
                char* value = va_arg(args, char*);
                if (value) {
                    size_t valueLen = strlen(value);
                    if (resultLen + valueLen < BUFFER_SIZE - 1) {
                        strcat(result + resultLen, value);
                        resultLen += valueLen;
                    }
                    free(value);
                }
                count--;
            }

            curr = end + 1;
            lastCopied = curr;
        } else {
            curr++;
        }
    }

    // Copy any remaining text
    if (*lastCopied && resultLen < BUFFER_SIZE - 1) {
        strcat(result + resultLen, lastCopied);
    }

    va_end(args);
    return result;
}

} // extern "C"
