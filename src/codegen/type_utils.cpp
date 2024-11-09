#include "type_utils.hpp"
#include "type_metadata.hpp"
#include <llvm/IR/DerivedTypes.h>

namespace pryst {

namespace {
// Internal helper function
llvm::Type* getLLVMTypeFromTypeInfoImpl(TypeInfoPtr typeInfo, llvm::LLVMContext& context) {
    if (!typeInfo) {
        throw std::runtime_error("Invalid type info");
    }

    switch (typeInfo->getKind()) {
        case TypeInfo::Kind::Basic: {
            const std::string& name = typeInfo->getName();
            if (name == "int") return llvm::Type::getInt32Ty(context);
            if (name == "float") return llvm::Type::getDoubleTy(context);
            if (name == "bool") return llvm::Type::getInt1Ty(context);
            if (name == "str") return llvm::Type::getInt8Ty(context);  // All pointers are opaque i8
            throw std::runtime_error("Unknown basic type: " + name);
        }
        case TypeInfo::Kind::Class:
            if (auto classInfo = std::dynamic_pointer_cast<LLVMClassTypeInfo>(typeInfo)) {
                return classInfo->getStructType();
            }
            throw std::runtime_error("Invalid class type info");
        case TypeInfo::Kind::Function:
            if (auto funcInfo = std::dynamic_pointer_cast<LLVMFunctionTypeInfo>(typeInfo)) {
                return funcInfo->getFunctionType(context);
            }
            throw std::runtime_error("Invalid function type info");
        case TypeInfo::Kind::Array:
            // TODO: Implement array type handling
            throw std::runtime_error("Array types not yet implemented");
        case TypeInfo::Kind::Pointer:
            return llvm::Type::getInt8Ty(context);  // All pointers are opaque i8
        default:
            throw std::runtime_error("Unknown type kind");
    }
}
} // anonymous namespace

llvm::Type* LLVMCodegen::getLLVMTypeFromTypeInfo(TypeInfoPtr typeInfo) const {
    if (!typeInfo) {
        throw std::runtime_error("Invalid type info");
    }
    return getLLVMTypeFromTypeInfoImpl(typeInfo, module->getContext());
}

} // namespace pryst
