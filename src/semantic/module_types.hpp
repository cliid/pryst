#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace pryst {

// Forward declarations
class Type;
class FunctionType;
class ClassType;

// Represents a function parameter
struct ParameterSignature {
    std::string name;
    std::shared_ptr<Type> type;
};

// Represents a function signature
struct FunctionSignature {
    std::string name;
    std::shared_ptr<Type> returnType;
    std::vector<ParameterSignature> parameters;
    bool isPublic;
};

// Represents a class member
struct MemberSignature {
    std::string name;
    std::shared_ptr<Type> type;
    bool isPublic;
};

// Represents a class method
struct MethodSignature : public FunctionSignature {
    bool isStatic;
    bool isVirtual;
};

// Represents a class signature
struct ClassSignature {
    std::string name;
    std::string parentClass;
    std::unordered_map<std::string, MemberSignature> members;
    std::unordered_map<std::string, MethodSignature> methods;
    bool isPublic;
};

} // namespace pryst
