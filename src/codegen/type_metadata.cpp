#include "type_metadata.hpp"
#include <llvm/IR/DerivedTypes.h>
#include <stdexcept>

namespace pryst {

// Helper function to check if a type is a subclass of another type
bool isSubclassOf(const ClassTypeInfoPtr& derived, const ClassTypeInfoPtr& base) {
    if (!derived || !base) return false;

    auto current = derived;
    while (current) {
        if (current->getStructType() == base->getStructType()) {
            return true;
        }
        current = current->getBaseClass();
    }
    return false;
}

// Helper function to get member index considering inheritance
size_t getMemberIndexInHierarchy(const ClassTypeInfoPtr& classInfo, const std::string& memberName) {
    if (!classInfo) {
        throw std::runtime_error("Invalid class type info");
    }

    try {
        return classInfo->getMemberIndex(memberName);
    } catch (const std::runtime_error&) {
        if (auto baseClass = classInfo->getBaseClass()) {
            return getMemberIndexInHierarchy(baseClass, memberName);
        }
        throw;
    }
}

// Helper function to check if a value is an instance of a class
bool isInstanceOf(const TypeInfoPtr& type, const ClassTypeInfoPtr& classType) {
    if (!type || !classType) return false;

    if (type->isClass()) {
        auto derivedClass = std::dynamic_pointer_cast<ClassTypeInfo>(type);
        return isSubclassOf(derivedClass, classType);
    }
    return false;
}

} // namespace pryst
