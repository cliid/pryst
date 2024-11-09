#pragma once

#include <unordered_map>
#include <memory>
#include <llvm/IR/Value.h>
#include "../semantic/type_info.hpp"
#include "../semantic/basic_type_info.hpp"

namespace pryst {

using TypeInfoPtr = std::shared_ptr<TypeInfo>;

class TypeMetadata {
public:
    TypeMetadata() = default;
    ~TypeMetadata() = default;

    void attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo);
    TypeInfoPtr getTypeInfo(llvm::Value* value) const;
    void clearTypeInfo(llvm::Value* value);

private:
    std::unordered_map<llvm::Value*, TypeInfoPtr> typeMap;
};

} // namespace pryst
