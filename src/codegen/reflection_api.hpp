#pragma once

#include <llvm/IR/Value.h>
#include <string>
#include <memory>
#include "type_metadata.hpp"

namespace pryst {

class LLVMCodegen;

// Forward declarations
class TypeInfo;
using TypeInfoPtr = std::shared_ptr<TypeInfo>;

// Reflection API interface
class ReflectionAPI {
public:
    virtual ~ReflectionAPI() = default;

    // Core reflection methods
    virtual llvm::Value* generateGetType(llvm::Value* value) = 0;
    virtual llvm::Value* generateIsInstance(llvm::Value* value, const std::string& typeName) = 0;

    // Type information management
    virtual TypeInfoPtr getTypeInfo(llvm::Value* value) = 0;
    virtual void attachTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) = 0;
};

} // namespace pryst
