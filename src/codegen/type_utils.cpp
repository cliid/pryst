#include "type_utils.hpp"
#include <llvm/IR/DerivedTypes.h>

namespace pryst {

llvm::Type* getLLVMTypeFromTypeInfo(const TypeInfoPtr& typeInfo, llvm::LLVMContext& context) {
    if (!typeInfo) return nullptr;

    switch (typeInfo->getKind()) {
        case TypeKind::Int:
        case TypeKind::Float:
        case TypeKind::Bool:
        case TypeKind::String:
        case TypeKind::Void: {
            auto basicInfo = std::dynamic_pointer_cast<BasicTypeInfo>(typeInfo);
            if (!basicInfo) return nullptr;
            return getBasicLLVMType(basicInfo->getBasicKind(), context);
        }
        case TypeKind::Array: {
            auto arrayInfo = std::dynamic_pointer_cast<ArrayTypeInfo>(typeInfo);
            if (!arrayInfo) return nullptr;
            auto elementType = getLLVMTypeFromTypeInfo(arrayInfo->getElementType(), context);
            if (!elementType) return nullptr;
            return llvm::PointerType::get(context, 0);
        }
        case TypeKind::Function: {
            auto funcInfo = std::dynamic_pointer_cast<FunctionTypeInfo>(typeInfo);
            if (!funcInfo) return nullptr;

            std::vector<llvm::Type*> paramTypes;
            for (const auto& paramType : funcInfo->getParamTypes()) {
                if (auto llvmType = getLLVMTypeFromTypeInfo(paramType, context)) {
                    paramTypes.push_back(llvmType);
                } else {
                    return nullptr;
                }
            }

            auto returnType = getLLVMTypeFromTypeInfo(funcInfo->getReturnType(), context);
            if (!returnType) return nullptr;

            return llvm::FunctionType::get(returnType, paramTypes, false);
        }
        default:
            return nullptr;
    }
}

llvm::Type* getBasicLLVMType(BasicTypeInfo::BasicKind kind, llvm::LLVMContext& context) {
    switch (kind) {
        case BasicTypeInfo::BasicKind::Void:
            return llvm::Type::getVoidTy(context);
        case BasicTypeInfo::BasicKind::Bool:
            return llvm::Type::getInt1Ty(context);
        case BasicTypeInfo::BasicKind::Int:
            return llvm::Type::getInt32Ty(context);
        case BasicTypeInfo::BasicKind::Float:
            return llvm::Type::getDoubleTy(context);
        case BasicTypeInfo::BasicKind::String:
            return llvm::PointerType::get(context, 0);
        default:
            return nullptr;
    }
}

bool isConvertibleTypes(const TypeInfo* from, const TypeInfo* to) {
    if (!from || !to) return false;
    if (from->getKind() == to->getKind()) return true;

    // Handle numeric type conversions
    if (from->getKind() == TypeKind::Int && to->getKind() == TypeKind::Float) {
        return true;
    }

    // Handle conversions to string
    if (to->getKind() == TypeKind::String &&
        (from->getKind() == TypeKind::Int ||
         from->getKind() == TypeKind::Float ||
         from->getKind() == TypeKind::Bool)) {
        return true;
    }

    return false;
}

} // namespace pryst
