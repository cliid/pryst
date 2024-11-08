#include "type_metadata.hpp"
#include "../utils/logger.hpp"
#include "../utils/debug.hpp"
#include <llvm/IR/DerivedTypes.h>
#include <stdexcept>

namespace pryst {

// Helper function to check if a type is a subclass of another type
bool isSubclassOf(const ClassTypeInfoPtr& derived, const ClassTypeInfoPtr& base) {
    if (!derived || !base) return false;

    auto current = derived;
    while (current) {
        // Check if types match in the inheritance chain
        if (current->getName() == base->getName()) {
            return true;
        }
        current = current->getParent();
    }
    return false;
}

// Helper function to get member index considering inheritance
size_t getMemberIndexInHierarchy(const ClassTypeInfoPtr& classInfo, const std::string& memberName) {
    if (!classInfo) {
        throw std::runtime_error("Invalid class type info");
    }

    auto llvmClassInfo = std::dynamic_pointer_cast<LLVMClassTypeInfo>(classInfo);
    if (!llvmClassInfo) {
        throw std::runtime_error("Expected LLVM class type info");
    }

    try {
        return llvmClassInfo->getMemberIndex(memberName);
    } catch (const std::runtime_error&) {
        if (auto baseClass = classInfo->getParent()) {
            return getMemberIndexInHierarchy(baseClass, memberName);
        }
        throw;
    }
}

// Helper function to check if a value is an instance of a class
bool isInstanceOf(const TypeInfoPtr& type, const ClassTypeInfoPtr& classType) {
    if (!type || !classType) return false;

    if (type->getKind() == TypeInfo::Kind::Class) {
        auto derivedClass = std::dynamic_pointer_cast<ClassTypeInfo>(type);
        if (!derivedClass) {
            return false;
        }
        return isSubclassOf(derivedClass, classType);
    }
    return false;
}

// LLVMFunctionTypeInfo implementation
llvm::FunctionType* LLVMFunctionTypeInfo::getFunctionType(llvm::LLVMContext& context) const {
    return llvmType ? llvmType : createFunctionType(context);
}

llvm::FunctionType* LLVMFunctionTypeInfo::createFunctionType(llvm::LLVMContext& context) const {
    std::vector<llvm::Type*> paramLLVMTypes;
    for (const auto& paramType : getParamTypes()) {
        paramLLVMTypes.push_back(getLLVMTypeFromTypeInfo(paramType, context));
    }
    return llvm::FunctionType::get(
        getLLVMTypeFromTypeInfo(getReturnType(), context),
        paramLLVMTypes,
        false
    );
}

// LLVMClassTypeInfo implementation
void LLVMClassTypeInfo::addMember(const std::string& name, size_t index, TypeInfoPtr type) {
    memberIndices[name] = index;
    memberTypes[name] = type;
}

TypeInfoPtr LLVMClassTypeInfo::getMemberType(const std::string& name) const {
    auto it = memberTypes.find(name);
    return it != memberTypes.end() ? it->second : nullptr;
}

size_t LLVMClassTypeInfo::getMemberIndex(const std::string& memberName) const {
    auto it = memberIndices.find(memberName);
    if (it != memberIndices.end()) {
        return it->second;
    }
    auto parent = parentClass;
    if (auto llvmParent = std::dynamic_pointer_cast<LLVMClassTypeInfo>(parent)) {
        return llvmParent->getMemberIndex(memberName);
    }
    throw std::runtime_error("Member not found: " + memberName);
}

TypeInfoPtr LLVMClassTypeInfo::getMemberTypeInfo(const std::string& memberName) const {
    // First check in this class
    auto fieldType = getMemberType(memberName);
    if (fieldType) {
        return fieldType;
    }
    // Then check parent class
    auto parent = parentClass;
    if (parent) {
        return parent->getMemberTypeInfo(memberName);
    }
    throw std::runtime_error("Member type not found: " + memberName);
}

std::string LLVMClassTypeInfo::getClassName() const {
    return getName();
}

// TypeMetadata implementation
TypeMetadata::TypeMetadata(llvm::LLVMContext& ctx, llvm::Module& mod)
    : context(ctx), module(mod) {
    PRYST_DEBUG("Initializing TypeMetadata");
}

void TypeMetadata::addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    if (!value || !typeInfo) {
        PRYST_ERROR("Attempted to add null type info");
        return;
    }
    PRYST_DEBUG("Adding type info for value: " + typeInfo->getName());
    typeInfoMap[value] = typeInfo;
}

TypeInfoPtr TypeMetadata::getTypeInfo(llvm::Value* value) const {
    if (!value) {
        PRYST_ERROR("Attempted to get type info for null value");
        return nullptr;
    }
    auto it = typeInfoMap.find(value);
    if (it != typeInfoMap.end()) {
        return it->second;
    }
    PRYST_DEBUG("No type info found for value");
    return nullptr;
}

void TypeMetadata::addFunctionTypeInfo(llvm::Function* function, LLVMFunctionTypeInfoPtr typeInfo) {
    if (!function || !typeInfo) {
        PRYST_ERROR("Attempted to add null function type info");
        return;
    }
    PRYST_DEBUG("Adding function type info for: " + std::string(function->getName()));
    functionTypes[function] = typeInfo;
}

LLVMFunctionTypeInfoPtr TypeMetadata::getFunctionTypeInfo(llvm::Function* function) const {
    if (!function) {
        PRYST_ERROR("Attempted to get type info for null function");
        return nullptr;
    }
    auto it = functionTypes.find(function);
    if (it != functionTypes.end()) {
        return it->second;
    }
    PRYST_DEBUG("No function type info found");
    return nullptr;
}

void TypeMetadata::addClassTypeInfo(llvm::StructType* structType, LLVMClassTypeInfoPtr typeInfo) {
    if (!structType || !typeInfo) {
        PRYST_ERROR("Attempted to add null class type info");
        return;
    }
    PRYST_DEBUG("Adding class type info for: " + std::string(structType->getName()));
    classTypes[structType] = typeInfo;
}

LLVMClassTypeInfoPtr TypeMetadata::getClassTypeInfo(llvm::StructType* structType) const {
    if (!structType) {
        PRYST_ERROR("Attempted to get type info for null struct type");
        return nullptr;
    }
    auto it = classTypes.find(structType);
    if (it != classTypes.end()) {
        return it->second;
    }
    PRYST_DEBUG("No class type info found");
    return nullptr;
}

} // namespace pryst
