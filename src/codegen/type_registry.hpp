#pragma once

#include "../semantic/type_info.hpp"
#include "type_metadata.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

namespace pryst {

// LLVM-specific type registry extensions
class LLVMTypeRegistry {
public:
    static LLVMTypeRegistry& getInstance() {
        static LLVMTypeRegistry instance;
        return instance;
    }

    // Convert TypeInfo to LLVM Type
    llvm::Type* getLLVMType(TypeInfoPtr type, llvm::LLVMContext& context) {
        if (!type) return nullptr;

        switch (type->getKind()) {
            case TypeInfo::Kind::Basic:
                if (type == TypeRegistry::getInstance().getIntType())
                    return llvm::Type::getInt32Ty(context);
                if (type == TypeRegistry::getInstance().getFloatType())
                    return llvm::Type::getDoubleTy(context);
                if (type == TypeRegistry::getInstance().getBoolType())
                    return llvm::Type::getInt1Ty(context);
                if (type == TypeRegistry::getInstance().getStrType())
                    return llvm::Type::getInt8PtrTy(context);
                break;
            case TypeInfo::Kind::Function: {
                auto funcType = std::dynamic_pointer_cast<FunctionTypeInfo>(type);
                if (!funcType) return nullptr;

                std::vector<llvm::Type*> paramTypes;
                for (const auto& paramType : funcType->getParamTypes()) {
                    if (auto llvmType = getLLVMType(paramType, context))
                        paramTypes.push_back(llvmType);
                }

                auto returnType = getLLVMType(funcType->getReturnType(), context);
                if (!returnType) return nullptr;

                return llvm::FunctionType::get(returnType, paramTypes, false);
            }
            case TypeInfo::Kind::Pointer:
                return llvm::PointerType::get(context);
            default:
                break;
        }
        return nullptr;
    }

private:
    LLVMTypeRegistry() = default;
    ~LLVMTypeRegistry() = default;
    LLVMTypeRegistry(const LLVMTypeRegistry&) = delete;
    LLVMTypeRegistry& operator=(const LLVMTypeRegistry&) = delete;
};

} // namespace pryst
