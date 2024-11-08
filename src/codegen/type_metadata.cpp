#include "type_metadata.hpp"
#include "../utils/debug.hpp"

namespace pryst {

void TypeMetadata::attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    if (value && typeInfo) {
        typeMap[value] = typeInfo;
    }
}

TypeInfoPtr TypeMetadata::getTypeInfo(llvm::Value* value) const {
    if (!value) return nullptr;
    auto it = typeMap.find(value);
    return it != typeMap.end() ? it->second : nullptr;
}

void TypeMetadata::clearTypeInfo(llvm::Value* value) {
    if (value) {
        typeMap.erase(value);
    }
}

} // namespace pryst
