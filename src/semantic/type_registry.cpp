#include "type_info.hpp"
#include "utils/debug.hpp"
#include <stdexcept>
#include <sstream>

bool TypeRegistry::debugEnabled = false;

TypeRegistry::TypeRegistry() {
    // Register basic types
    registerBasicType("void");
    registerBasicType("bool");
    registerBasicType("int");
    registerBasicType("float");
    registerBasicType("str");
}

void TypeRegistry::registerBasicType(const std::string& name) {
    if (types.find(name) != types.end()) {
        PRYST_DEBUG("Type already registered: " + name);
        return;
    }

    auto typeInfo = std::make_shared<BasicTypeInfo>(name);
    types[name] = typeInfo;
    PRYST_DEBUG("Registered basic type: " + name);
}

void TypeRegistry::registerClassType(const std::string& name, const std::vector<std::string>& baseClasses) {
    if (types.find(name) != types.end()) {
        PRYST_DEBUG("Type already registered: " + name);
        return;
    }

    auto typeInfo = std::make_shared<ClassTypeInfo>(name, baseClasses);
    types[name] = typeInfo;
    PRYST_DEBUG("Registered class type: " + name + " with " + std::to_string(baseClasses.size()) + " base classes");
}

void TypeRegistry::registerFunctionType(const std::string& returnType, const std::vector<std::string>& paramTypes) {
    std::string typeString = createFunctionTypeString(returnType, paramTypes);
    if (types.find(typeString) != types.end()) {
        PRYST_DEBUG("Function type already registered: " + typeString);
        return;
    }

    auto typeInfo = std::make_shared<FunctionTypeInfo>(returnType, paramTypes);
    types[typeString] = typeInfo;
    PRYST_DEBUG("Registered function type: " + typeString);
}

void TypeRegistry::registerPointerType(const std::string& baseType) {
    std::string pointerType = baseType + "*";
    if (types.find(pointerType) != types.end()) {
        PRYST_DEBUG("Pointer type already registered: " + pointerType);
        return;
    }

    auto typeInfo = std::make_shared<PointerTypeInfo>(baseType);
    types[pointerType] = typeInfo;
    PRYST_DEBUG("Registered pointer type: " + pointerType);
}

std::shared_ptr<TypeInfo> TypeRegistry::getType(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) {
        throw std::runtime_error("Type not found: " + name);
    }
    return it->second;
}

bool TypeRegistry::isBasicType(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) return false;
    return dynamic_cast<BasicTypeInfo*>(it->second.get()) != nullptr;
}

bool TypeRegistry::isClassType(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) return false;
    return dynamic_cast<ClassTypeInfo*>(it->second.get()) != nullptr;
}

bool TypeRegistry::isFunctionType(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) return false;
    return dynamic_cast<FunctionTypeInfo*>(it->second.get()) != nullptr;
}

bool TypeRegistry::isPointerType(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) return false;
    return dynamic_cast<PointerTypeInfo*>(it->second.get()) != nullptr;
}

std::string TypeRegistry::createFunctionTypeString(const std::string& returnType, const std::vector<std::string>& paramTypes) const {
    std::stringstream ss;
    ss << "fn<" << returnType << ">(";
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << paramTypes[i];
    }
    ss << ")";
    return ss.str();
}

bool TypeRegistry::areTypesCompatible(const std::string& expected, const std::string& actual) const {
    if (expected == actual) return true;

    // Handle numeric type promotion (int to float)
    if (expected == "float" && actual == "int") return true;

    // Handle class inheritance
    if (isClassType(expected) && isClassType(actual)) {
        auto actualType = std::dynamic_pointer_cast<ClassTypeInfo>(getType(actual));
        return actualType->isSubclassOf(expected);
    }

    // Handle function type compatibility
    if (isFunctionType(expected) && isFunctionType(actual)) {
        auto expectedType = std::dynamic_pointer_cast<FunctionTypeInfo>(getType(expected));
        auto actualType = std::dynamic_pointer_cast<FunctionTypeInfo>(getType(actual));
        return expectedType->isCompatibleWith(*actualType);
    }

    return false;
}

std::string TypeRegistry::getBaseType(const std::string& pointerType) const {
    if (!isPointerType(pointerType)) {
        throw std::runtime_error("Not a pointer type: " + pointerType);
    }
    return pointerType.substr(0, pointerType.length() - 1);
}

void TypeRegistry::setDebugEnabled(bool enabled) {
    debugEnabled = enabled;
    PRYST_DEBUG("Debug mode " + std::string(enabled ? "enabled" : "disabled") + " for TypeRegistry");
}
