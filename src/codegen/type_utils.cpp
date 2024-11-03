#include "llvm_codegen.hpp"
#include "type_metadata.hpp"
#include <llvm/IR/DerivedTypes.h>

llvm::Type* LLVMCodegen::getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo) {
    if (!typeInfo) {
        throw std::runtime_error("Invalid type info");
    }

    switch (typeInfo->getKind()) {
        case pryst::TypeKind::Int:
            return llvm::Type::getInt32Ty(*context);
        case pryst::TypeKind::Float:
            return llvm::Type::getDoubleTy(*context);
        case pryst::TypeKind::Bool:
            return llvm::Type::getInt1Ty(*context);
        case pryst::TypeKind::String:
            return llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(*context));
        case pryst::TypeKind::Class:
            if (auto classInfo = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(typeInfo)) {
                return classInfo->getLLVMType();
            }
            throw std::runtime_error("Invalid class type info");
        case pryst::TypeKind::Function:
            if (auto funcInfo = std::dynamic_pointer_cast<pryst::FunctionTypeInfo>(typeInfo)) {
                return funcInfo->getFunctionType();
            }
            throw std::runtime_error("Invalid function type info");
        case pryst::TypeKind::Void:
            return llvm::Type::getVoidTy(*context);
        case pryst::TypeKind::Pointer:
            return llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(*context));
        default:
            throw std::runtime_error("Unknown type kind");
    }
}
