#pragma once

#include <memory>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include "../semantic/type_info.hpp"
#include "../semantic/basic_type_info.hpp"

namespace pryst {

llvm::Type* getLLVMTypeFromTypeInfo(const TypeInfoPtr& typeInfo, llvm::LLVMContext& context);
llvm::Type* getBasicLLVMType(BasicTypeInfo::BasicKind kind, llvm::LLVMContext& context);
bool isConvertibleTypes(const TypeInfo* from, const TypeInfo* to);

} // namespace pryst
