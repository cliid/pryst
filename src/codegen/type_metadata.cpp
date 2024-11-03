#include "type_metadata.hpp"
#include <llvm/IR/DerivedTypes.h>
#include <stdexcept>

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
            auto llvmBaseClass = std::dynamic_pointer_cast<LLVMClassTypeInfo>(baseClass);
            if (!llvmBaseClass) {
                throw std::runtime_error("Expected LLVM class type info for base class");
            }
            return getMemberIndexInHierarchy(llvmBaseClass, memberName);
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
