#pragma once

#include <string>

struct ClassInfo {
    std::string baseClassName;
    ClassInfo() : baseClassName("") {}
    explicit ClassInfo(const std::string& base) : baseClassName(base) {}
};
