#include "type_registry.hpp"
#include "../utils/logger.hpp"
#include "llvm/IR/DerivedTypes.h"
#include <sstream>

namespace pryst {

namespace {
    // Helper function to create type signature string
    std::string createTypeSignature(const std::string& baseName,
                                  const std::vector<std::string>& params = {}) {
        std::stringstream ss;
        ss << baseName;
        if (!params.empty()) {
            ss << "<";
            for (size_t i = 0; i < params.size(); ++i) {
                if (i > 0) ss << ",";
                ss << params[i];
            }
            ss << ">";
        }
        return ss.str();
    }
}

llvm::Type* TypeRegistry::getFunctionPointerType(llvm::Type* returnType,
                                               const std::vector<llvm::Type*>& paramTypes,
                                               bool isVarArg) {
    auto funcType = getFunctionType(returnType, paramTypes, isVarArg);
    return createOpaquePointer();
}

llvm::Type* TypeRegistry::getLoadType(llvm::Type* type) {
    if (!type) {
        PRYST_ERROR("Attempted to get load type for null type");
        return nullptr;
    }

    // For opaque pointers, we need to track the actual type separately
    if (type->isPointerTy()) {
        // Look up the element type name from our mapping
        for (const auto& [ptrName, elemName] : elementTypes) {
            if (typeCache[ptrName] == type) {
                return getType(elemName);
            }
        }
        // If we can't find the element type, return a default type
        PRYST_WARNING("Could not find element type for pointer, using default");
        return getIntType();
    }

    return type;
}

llvm::Type* TypeRegistry::getStoreType(llvm::Type* type) {
    if (!type) {
        PRYST_ERROR("Attempted to get store type for null type");
        return nullptr;
    }

    // For opaque pointers, we need to track the actual type separately
    if (type->isPointerTy()) {
        // Look up the element type name from our mapping
        for (const auto& [ptrName, elemName] : elementTypes) {
            if (typeCache[ptrName] == type) {
                return getType(elemName);
            }
        }
        // If we can't find the element type, return a default type
        PRYST_WARNING("Could not find element type for pointer, using default");
        return getIntType();
    }

    return type;
}

llvm::Type* TypeRegistry::getArrayElementType(llvm::Type* arrayType) {
    if (!arrayType) {
        PRYST_ERROR("Attempted to get element type for null array type");
        return nullptr;
    }

    if (auto arrTy = llvm::dyn_cast<llvm::ArrayType>(arrayType)) {
        return arrTy->getElementType();
    }

    PRYST_ERROR("Type is not an array type");
    return nullptr;
}

llvm::Type* TypeRegistry::getStructElementType(llvm::Type* structType, unsigned index) {
    if (!structType) {
        PRYST_ERROR("Attempted to get element type for null struct type");
        return nullptr;
    }

    if (auto structTy = llvm::dyn_cast<llvm::StructType>(structType)) {
        if (index < structTy->getNumElements()) {
            return structTy->getElementType(index);
        }
        PRYST_ERROR("Struct element index out of bounds");
        return nullptr;
    }

    PRYST_ERROR("Type is not a struct type");
    return nullptr;
}

bool TypeRegistry::isPointerToFunction(llvm::Type* type) {
    if (!type || !type->isPointerTy()) return false;

    // In LLVM 20.0.0, we can't directly check the pointee type
    // Instead, we check our type registry
    for (const auto& [name, elemType] : elementTypes) {
        if (typeCache[name] == type) {
            return name.find("fn<") == 0;
        }
    }
    return false;
}

std::string TypeRegistry::getTypeName(llvm::Type* type) {
    if (!type) return "null";

    // Search in our type cache
    for (const auto& [name, cachedType] : typeCache) {
        if (cachedType == type) return name;
    }

    // If not found in cache, generate a name based on type properties
    if (type->isVoidTy()) return "void";
    if (type->isIntegerTy(1)) return "bool";
    if (type->isIntegerTy(32)) return "int";
    if (type->isFloatTy()) return "float";
    if (type->isPointerTy()) return "ptr";
    if (type->isArrayTy()) return "array";
    if (type->isStructTy()) {
        auto structType = llvm::cast<llvm::StructType>(type);
        return structType->hasName() ? structType->getName().str() : "struct";
    }

    return "unknown";
}

void TypeRegistry::dumpTypeInfo() {
    PRYST_DEBUG("=== Type Registry Contents ===");
    for (const auto& [name, type] : typeCache) {
        PRYST_DEBUG("Type: " + name);
        if (type->isPointerTy()) {
            auto it = elementTypes.find(name);
            if (it != elementTypes.end()) {
                PRYST_DEBUG("  Element type: " + it->second);
            }
        }
    }
    PRYST_DEBUG("===========================");
}

} // namespace pryst
