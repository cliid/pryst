#pragma once

#include "type_registry.hpp"
#include "type_metadata.hpp"
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>

namespace pryst {

// Forward declarations
class TypeInfo;
using TypeInfoPtr = std::shared_ptr<TypeInfo>;

// Global type conversion function - declared here, defined in type_utils.cpp
llvm::Type* getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo, llvm::LLVMContext& context);

} // namespace pryst
