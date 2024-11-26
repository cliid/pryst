#pragma once

// LLVM headers (order matters)
#include <llvm/Support/Casting.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

// Standard library headers
#include <memory>

// Project headers
#include "type_system/core/types.hpp"

namespace pryst {
namespace core {

// Use consistent LLVM type aliases
using LLVMContextRef = ::llvm::LLVMContext;
using LLVMTypeRef = ::llvm::Type;
using LLVMArrayTypeRef = ::llvm::ArrayType;
using LLVMPointerTypeRef = ::llvm::PointerType;
using LLVMStructTypeRef = ::llvm::StructType;

class LLVMTypeConverter {
public:
    explicit LLVMTypeConverter(LLVMContextRef& context) : context_(context) {}

    LLVMTypeRef* convert(const std::shared_ptr<Type>& type) {
        switch (type->getKind()) {
            case Type::Kind::Int:
                return LLVMTypeRef::getInt32Ty(context_);
            case Type::Kind::Float:
                return LLVMTypeRef::getDoubleTy(context_);
            case Type::Kind::Bool:
                return LLVMTypeRef::getInt1Ty(context_);
            case Type::Kind::String:
                return LLVMTypeRef::getInt8PtrTy(context_);
            case Type::Kind::Void:
                return LLVMTypeRef::getVoidTy(context_);
            case Type::Kind::Array:
                return convertArrayType(std::static_pointer_cast<ArrayType>(type));
            case Type::Kind::Map:
                return convertMapType(std::static_pointer_cast<MapType>(type));
            case Type::Kind::Class:
                return convertClassType(std::static_pointer_cast<ClassType>(type));
            case Type::Kind::Nullable:
                return convertNullableType(std::static_pointer_cast<NullableType>(type));
            default:
                throw std::runtime_error("Unsupported type for LLVM conversion");
        }
    }

private:
    LLVMTypeRef* convertArrayType(const std::shared_ptr<ArrayType>& type) {
        auto elementType = convert(type->getElementType());
        auto arrayType = LLVMArrayTypeRef::get(elementType, 0);
        return LLVMPointerTypeRef::getUnqual(arrayType);
    }

    LLVMTypeRef* convertMapType(const std::shared_ptr<MapType>& type) {
        // Maps are implemented as pointers to opaque structures
        auto i8Ty = LLVMTypeRef::getInt8Ty(context_);
        return LLVMPointerTypeRef::getUnqual(i8Ty);
    }

    LLVMTypeRef* convertClassType(const std::shared_ptr<ClassType>& type) {
        std::vector<LLVMTypeRef*> memberTypes;
        for (const auto& memberName : type->getAvailableMembers()) {
            auto memberType = type->getField(memberName);
            memberTypes.push_back(convert(memberType));
        }
        return LLVMStructTypeRef::create(context_, memberTypes, type->getName());
    }

    LLVMTypeRef* convertNullableType(const std::shared_ptr<NullableType>& type) {
        return LLVMPointerTypeRef::getUnqual(convert(type->getInnerType()));
    }

    LLVMContextRef& context_;
};

} // namespace core
} // namespace pryst
