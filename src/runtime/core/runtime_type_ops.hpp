#ifndef PRYST_RUNTIME_TYPE_OPS_HPP
#define PRYST_RUNTIME_TYPE_OPS_HPP

#include "../type_system/advanced/types.hpp"
#include <memory>

namespace pryst {
namespace runtime {

// Runtime type operator implementations
class TypeOperations {
public:
    static bool isNullable(void* obj);
    static bool isArray(void* obj);
    static const char* getBaseTypeName(void* obj);
    static std::string getFullTypeName(void* obj);  // Includes nullable/array status
};

extern "C" {
    bool pryst_runtime_instanceof(void* obj, const char* typeName);
    const char* pryst_runtime_typeof(void* obj);
    bool pryst_runtime_is_nullable(void* obj);
}

} // namespace runtime
} // namespace pryst

#endif // PRYST_RUNTIME_TYPE_OPS_HPP
