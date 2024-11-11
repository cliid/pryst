#include "type_registry.hpp"
#include <stdexcept>

namespace pryst {

TypeRegistry::TypeRegistry() {}

void TypeRegistry::registerClass(const std::string& className,
                               const std::vector<std::pair<std::string, llvm::Type*>>& members) {
    if (hasClass(className)) {
        throw std::runtime_error("Class " + className + " already registered");
    }

    // Create vector of member types for LLVM struct type
    std::vector<llvm::Type*> memberTypes;
    for (const auto& member : members) {
        memberTypes.push_back(member.second);
    }

    // Create LLVM struct type for the class
    auto* structType = llvm::StructType::create(memberTypes, className);
    classTypes[className] = structType;
    classMemberInfo[className] = members;
}

llvm::StructType* TypeRegistry::getClassType(const std::string& className) {
    if (!hasClass(className)) {
        throw std::runtime_error("Class " + className + " not found in registry");
    }
    return classTypes[className];
}

int TypeRegistry::getMemberIndex(const std::string& className, const std::string& memberName) {
    if (!hasClass(className)) {
        throw std::runtime_error("Class " + className + " not found in registry");
    }

    const auto& members = classMemberInfo[className];
    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i].first == memberName) {
            return static_cast<int>(i);
        }
    }

    throw std::runtime_error("Member " + memberName + " not found in class " + className);
}

bool TypeRegistry::hasClass(const std::string& className) const {
    return classTypes.find(className) != classTypes.end();
}

llvm::Type* TypeRegistry::getMemberType(const std::string& className, int index) {
    if (!hasClass(className)) {
        throw std::runtime_error("Class " + className + " not found in registry");
    }

    const auto& members = classMemberInfo[className];
    if (index < 0 || static_cast<size_t>(index) >= members.size()) {
        throw std::runtime_error("Invalid member index " + std::to_string(index) +
                               " for class " + className);
    }

    return members[index].second;
}

} // namespace pryst
