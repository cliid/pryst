#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <string>
#include <vector>
#include <functional>
#include "web.hpp"

namespace pryst {
namespace runtime {

class RuntimeRegistry;  // Forward declaration

namespace web {

// Function declaration only
void registerWebTypes(RuntimeRegistry& registry);

} // namespace web
} // namespace runtime
} // namespace pryst
