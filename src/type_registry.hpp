#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"

namespace pryst {

class TypeRegistry {
public:
    TypeRegistry();
    ~TypeRegistry() = default;

    // Register a new class type with its members
    void registerClass(const std::string& className,
                      const std::vector<std::pair<std::string, llvm::Type*>>& members);

    // Get the LLVM type for a class
    llvm::StructType* getClassType(const std::string& className);

    // Get the index of a member within a class
    int getMemberIndex(const std::string& className, const std::string& memberName);

    // Check if a class exists
    bool hasClass(const std::string& className) const;

    // Get member type by index
    llvm::Type* getMemberType(const std::string& className, int index);

private:
    // Map of class names to their LLVM struct types
    std::unordered_map<std::string, llvm::StructType*> classTypes;

    // Map of class names to their member information
    std::unordered_map<std::string, std::vector<std::pair<std::string, llvm::Type*>>> classMemberInfo;
};

} // namespace pryst
