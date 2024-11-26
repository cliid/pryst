#include "type_registry.hpp"
#include "runtime/runtime_registry.hpp"
#include "error.hpp"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Value.h"
#include <iostream>

namespace pryst {

TypeRegistry::TypeRegistry(llvm::LLVMContext& context)
    : context_(context)
    , runtimeRegistry_(*static_cast<runtime::RuntimeRegistry*>(nullptr)) {  // Temporary null reference
    std::cout << "TypeRegistry basic constructor called" << std::endl;

    // Create LLVM types for primitives
    auto* i32Type = llvm::Type::getInt32Ty(context_);
    auto* i8PtrType = llvm::PointerType::get(llvm::Type::getInt8Ty(context_), 0);
    auto* floatType = llvm::Type::getFloatTy(context_);
    auto* boolType = llvm::Type::getInt1Ty(context_);

    // Register primitive types as classes with their LLVM types
    std::vector<std::pair<std::string, llvm::Type*>> strMembers;
    strMembers.push_back({"data", i8PtrType});  // String data pointer
    strMembers.push_back({"length", i32Type});  // String length
    auto* strStructType = llvm::StructType::create(context_, {i8PtrType, i32Type}, "str");
    classTypes["str"] = strStructType;
    classMemberInfo["str"] = strMembers;
    cacheType("str", STRING_TYPE);

    // Register int as a class
    std::vector<std::pair<std::string, llvm::Type*>> intMembers;
    intMembers.push_back({"value", i32Type});
    auto* intStructType = llvm::StructType::create(context_, {i32Type}, "int");
    classTypes["int"] = intStructType;
    classMemberInfo["int"] = intMembers;
    cacheType("int", INT_TYPE);

    // Register float as a class
    std::vector<std::pair<std::string, llvm::Type*>> floatMembers;
    floatMembers.push_back({"value", floatType});
    auto* floatStructType = llvm::StructType::create(context_, {floatType}, "float");
    classTypes["float"] = floatStructType;
    classMemberInfo["float"] = floatMembers;
    cacheType("float", FLOAT_TYPE);

    // Register bool as a class
    std::vector<std::pair<std::string, llvm::Type*>> boolMembers;
    boolMembers.push_back({"value", boolType});
    auto* boolStructType = llvm::StructType::create(context_, {boolType}, "bool");
    classTypes["bool"] = boolStructType;
    classMemberInfo["bool"] = boolMembers;
    cacheType("bool", BOOL_TYPE);

    // Register nullable versions of primitive types
    auto* nullableIntStructType = llvm::StructType::create(context_, {llvm::PointerType::get(i32Type, 0)}, "int?");
    classTypes["int?"] = nullableIntStructType;
    std::vector<std::pair<std::string, llvm::Type*>> nullableIntMembers;
    nullableIntMembers.push_back({"value", llvm::PointerType::get(i32Type, 0)});
    classMemberInfo["int?"] = nullableIntMembers;
    auto nullableIntType = std::make_shared<NullableType>(INT_TYPE);
    cacheType("int?", nullableIntType);
    nullableTypes.insert("int");

    auto* nullableStrStructType = llvm::StructType::create(context_, {llvm::PointerType::get(strStructType, 0)}, "str?");
    classTypes["str?"] = nullableStrStructType;
    std::vector<std::pair<std::string, llvm::Type*>> nullableStrMembers;
    nullableStrMembers.push_back({"value", llvm::PointerType::get(strStructType, 0)});
    classMemberInfo["str?"] = nullableStrMembers;
    auto nullableStrType = std::make_shared<NullableType>(STRING_TYPE);
    cacheType("str?", nullableStrType);
    nullableTypes.insert("str");

    // Register methods after types are registered
    registerPrimitiveMethods();
}

TypeRegistry::TypeRegistry(llvm::LLVMContext& context, runtime::RuntimeRegistry& runtimeRegistry)
    : context_(context)
    , runtimeRegistry_(runtimeRegistry) {
    std::cout << "TypeRegistry full constructor called" << std::endl;

    // Create LLVM types for primitives
    auto* i32Type = llvm::Type::getInt32Ty(context_);
    auto* i8PtrType = llvm::PointerType::get(llvm::Type::getInt8Ty(context_), 0);
    auto* floatType = llvm::Type::getFloatTy(context_);
    auto* boolType = llvm::Type::getInt1Ty(context_);

    // Register primitive types as classes with their LLVM types
    std::vector<std::pair<std::string, llvm::Type*>> strMembers;
    strMembers.push_back({"data", i8PtrType});  // String data pointer
    strMembers.push_back({"length", i32Type});  // String length
    auto* strStructType = llvm::StructType::create(context_, {i8PtrType, i32Type}, "str");
    classTypes["str"] = strStructType;
    classMemberInfo["str"] = strMembers;
    cacheType("str", STRING_TYPE);

    // Register int as a class
    std::vector<std::pair<std::string, llvm::Type*>> intMembers;
    intMembers.push_back({"value", i32Type});
    auto* intStructType = llvm::StructType::create(context_, {i32Type}, "int");
    classTypes["int"] = intStructType;
    classMemberInfo["int"] = intMembers;
    cacheType("int", INT_TYPE);

    // Register float as a class
    std::vector<std::pair<std::string, llvm::Type*>> floatMembers;
    floatMembers.push_back({"value", floatType});
    auto* floatStructType = llvm::StructType::create(context_, {floatType}, "float");
    classTypes["float"] = floatStructType;
    classMemberInfo["float"] = floatMembers;
    cacheType("float", FLOAT_TYPE);

    // Register bool as a class
    std::vector<std::pair<std::string, llvm::Type*>> boolMembers;
    boolMembers.push_back({"value", boolType});
    auto* boolStructType = llvm::StructType::create(context_, {boolType}, "bool");
    classTypes["bool"] = boolStructType;
    classMemberInfo["bool"] = boolMembers;
    cacheType("bool", BOOL_TYPE);

    // Register nullable versions of primitive types
    auto* nullableIntStructType = llvm::StructType::create(context_, {llvm::PointerType::get(i32Type, 0)}, "int?");
    classTypes["int?"] = nullableIntStructType;
    std::vector<std::pair<std::string, llvm::Type*>> nullableIntMembers;
    nullableIntMembers.push_back({"value", llvm::PointerType::get(i32Type, 0)});
    classMemberInfo["int?"] = nullableIntMembers;
    auto nullableIntType = std::make_shared<NullableType>(INT_TYPE);
    cacheType("int?", nullableIntType);
    nullableTypes.insert("int");

    auto* nullableStrStructType = llvm::StructType::create(context_, {llvm::PointerType::get(strStructType, 0)}, "str?");
    classTypes["str?"] = nullableStrStructType;
    std::vector<std::pair<std::string, llvm::Type*>> nullableStrMembers;
    nullableStrMembers.push_back({"value", llvm::PointerType::get(strStructType, 0)});
    classMemberInfo["str?"] = nullableStrMembers;
    auto nullableStrType = std::make_shared<NullableType>(STRING_TYPE);
    cacheType("str?", nullableStrType);
    nullableTypes.insert("str");

    // Register methods after types are registered
    registerPrimitiveMethods();
}

void TypeRegistry::registerPrimitiveMethods() {
    std::cout << "Debug [registerPrimitiveMethods]: Registering primitive methods" << std::endl;

    // Create common return types
    auto* stringType = llvm::PointerType::get(llvm::IntegerType::get(context_, 8), 0);
    auto* intType = llvm::IntegerType::get(context_, 32);

    // toString() method for int
    std::vector<llvm::Type*> noParams;
    auto* toStringFuncType = llvm::FunctionType::get(stringType, noParams, false);
    primitiveMethods["int"]["toString"] = toStringFuncType;

    // toString() method for float
    primitiveMethods["float"]["toString"] = toStringFuncType;

    // toString() method for bool
    primitiveMethods["bool"]["toString"] = toStringFuncType;

    // length() method for string
    auto* lengthFuncType = llvm::FunctionType::get(intType, noParams, false);
    primitiveMethods["str"]["length"] = lengthFuncType;
    primitiveMethods["str"]["toString"] = toStringFuncType;  // string also has toString()

    std::cout << "Debug [registerPrimitiveMethods]: Registered primitive methods for int, float, bool, and str" << std::endl;
}

const std::unordered_map<std::string, llvm::FunctionType*>& TypeRegistry::getPrimitiveMethods(const std::string& typeName) const {
    auto it = primitiveMethods.find(typeName);
    if (it == primitiveMethods.end()) {
        static std::unordered_map<std::string, llvm::FunctionType*> empty;
        return empty;
    }
    return it->second;
}

void TypeRegistry::registerNullableType(const std::string& typeName) {
    std::cout << "Debug [registerNullableType]: Registering nullable type: " << typeName << std::endl;

    // Extract base type name if typeName ends with '?'
    std::string baseTypeName;
    std::string nullableTypeName;

    if (typeName.back() == '?') {
        baseTypeName = typeName.substr(0, typeName.length() - 1);
        nullableTypeName = typeName;
    } else {
        baseTypeName = typeName;
        nullableTypeName = typeName + "?";
    }

    std::cout << "Debug [registerNullableType]: Base type name: " << baseTypeName << std::endl;
    std::cout << "Debug [registerNullableType]: Nullable type name: " << nullableTypeName << std::endl;

    // Check if base type exists in class types for qualified names
    if (baseTypeName.find("::") != std::string::npos) {
        if (!hasClass(baseTypeName)) {
            std::cerr << "Error: Cannot create nullable type for unregistered class: " << baseTypeName << std::endl;
            throw Error("TypeError", "Unregistered class type: " + baseTypeName);
        }
        // Create a class type for the base type if it doesn't exist in cache
        if (!getCachedType(baseTypeName)) {
            auto classType = std::make_shared<ClassType>(baseTypeName);
            cacheType(baseTypeName, classType);
        }
    }

    // Get the base type
    auto baseType = getCachedType(baseTypeName);
    if (!baseType) {
        std::cerr << "Error: Cannot create nullable type for unknown base type: " << baseTypeName << std::endl;
        throw Error("TypeError", "Unknown base type: " + baseTypeName);
    }

    // Create the nullable type wrapper
    auto nullableType = std::make_shared<NullableType>(baseType);

    // Cache the nullable type
    cacheType(nullableTypeName, nullableType);

    // Add to set of nullable types
    nullableTypes.insert(baseTypeName);

    std::cout << "Debug [registerNullableType]: Successfully registered nullable type: " << nullableTypeName << std::endl;
}

std::shared_ptr<Type> TypeRegistry::getCachedType(const std::string& typeName) const {
    std::cout << "\nDebug [getCachedType]: ===========================================" << std::endl;
    std::cout << "Debug [getCachedType]: Looking up type: " << typeName << std::endl;
    std::cout << "Debug [getCachedType]: Current type cache contents:" << std::endl;
    for (const auto& [name, type] : typeCache) {
        std::cout << "  - " << name << " -> " << type->toString() << std::endl;
    }
    std::cout << "Debug [getCachedType]: Current registered namespaces:" << std::endl;
    for (const auto& ns : registeredNamespaces) {
        std::cout << "  - " << ns << std::endl;
    }

    // Try exact match first
    auto it = typeCache.find(typeName);
    if (it != typeCache.end()) {
        std::cout << "Debug [getCachedType]: Found exact match for " << typeName << std::endl;
        return it->second;
    }
    std::cout << "Debug [getCachedType]: No exact match found for " << typeName << std::endl;

    // If the type name contains namespace separators (::), try variations
    size_t lastSeparator = typeName.rfind("::");
    if (lastSeparator != std::string::npos) {
        // Try short name only if we're in the correct namespace context
        std::string shortName = typeName.substr(lastSeparator + 2);
        std::string namespacePart = typeName.substr(0, lastSeparator);

        std::cout << "Debug [getCachedType]: Trying namespace variations:" << std::endl;
        std::cout << "  - Short name: " << shortName << std::endl;
        std::cout << "  - Namespace part: " << namespacePart << std::endl;

        // Only use short name if the namespace is registered
        if (registeredNamespaces.find(namespacePart) != registeredNamespaces.end()) {
            std::cout << "Debug [getCachedType]: Namespace " << namespacePart << " is registered, trying short name" << std::endl;
            it = typeCache.find(shortName);
            if (it != typeCache.end()) {
                std::cout << "Debug [getCachedType]: Found short name match: " << shortName << std::endl;
                return it->second;
            }
            std::cout << "Debug [getCachedType]: Short name " << shortName << " not found in cache" << std::endl;
        } else {
            std::cout << "Debug [getCachedType]: Namespace " << namespacePart << " is not registered" << std::endl;
        }

        // Try all registered namespace variations
        std::string currentNs = "";
        std::string remainingName = typeName;
        while ((lastSeparator = remainingName.find("::")) != std::string::npos) {
            currentNs += (currentNs.empty() ? "" : "::") + remainingName.substr(0, lastSeparator);
            remainingName = remainingName.substr(lastSeparator + 2);

            std::vector<std::string> tryNames = {
                currentNs + "::" + remainingName,
                remainingName
            };

            for (const auto& tryName : tryNames) {
                std::cout << "Debug [getCachedType]: Trying variation: " << tryName << std::endl;
                it = typeCache.find(tryName);
                if (it != typeCache.end()) {
                    std::cout << "Debug [getCachedType]: Found variation match: " << tryName << std::endl;
                    return it->second;
                }
                std::cout << "Debug [getCachedType]: Variation " << tryName << " not found in cache" << std::endl;
            }
        }
    }

    std::cout << "Debug [getCachedType]: No type found for " << typeName << std::endl;
    std::cout << "Debug [getCachedType]: ===========================================" << std::endl;
    return nullptr;
}

void TypeRegistry::cacheType(const std::string& typeName, std::shared_ptr<Type> type) {
    std::cout << "\nDebug [cacheType]: ===========================================" << std::endl;
    std::cout << "Debug [cacheType]: Attempting to cache type: " << typeName << " -> " << type->toString() << std::endl;

    // First register the namespace if this is a qualified name
    size_t lastSeparator = typeName.rfind("::");
    if (lastSeparator != std::string::npos) {
        std::string ns = typeName.substr(0, lastSeparator);
        std::cout << "Debug [cacheType]: Registering namespace before caching: " << ns << std::endl;
        registerNamespace(ns);
    }

    // Print current cache state before adding
    std::cout << "Debug [cacheType]: Current cache contents before adding:" << std::endl;
    for (const auto& [name, t] : typeCache) {
        std::cout << "  - " << name << " -> " << t->toString() << std::endl;
    }

    // Check if type already exists in cache
    auto it = typeCache.find(typeName);
    if (it != typeCache.end()) {
        std::cout << "Debug [cacheType]: Type " << typeName << " already cached with value " << it->second->toString() << std::endl;
        // Verify if cached type matches new type
        if (it->second->toString() != type->toString()) {
            std::cout << "Debug [cacheType]: WARNING: Cached type differs from new type!" << std::endl;
            std::cout << "  Cached: " << it->second->toString() << std::endl;
            std::cout << "  New: " << type->toString() << std::endl;
        }
        return;
    }

    // Cache with fully qualified name
    typeCache[typeName] = type;
    std::cout << "Debug [cacheType]: Cached with fully qualified name: " << typeName << std::endl;

    // If type has namespace, also cache with short name if namespace is registered
    if (lastSeparator != std::string::npos) {
        std::string shortName = typeName.substr(lastSeparator + 2);
        std::string namespacePart = typeName.substr(0, lastSeparator);

        if (registeredNamespaces.find(namespacePart) != registeredNamespaces.end()) {
            // Only cache short name if it doesn't conflict
            if (typeCache.find(shortName) == typeCache.end()) {
                typeCache[shortName] = type;
                std::cout << "Debug [cacheType]: Also cached with short name: " << shortName << std::endl;
            } else {
                std::cout << "Debug [cacheType]: Short name " << shortName << " already exists, skipping to avoid conflicts" << std::endl;
            }
        } else {
            std::cout << "Debug [cacheType]: Namespace " << namespacePart << " not registered, skipping short name caching" << std::endl;
        }
    }

    // Print final cache state
    std::cout << "Debug [cacheType]: Final cache contents:" << std::endl;
    for (const auto& [name, t] : typeCache) {
        std::cout << "  - " << name << " -> " << t->toString() << std::endl;
    }
    std::cout << "Debug [cacheType]: ===========================================" << std::endl;
}

void TypeRegistry::registerClass(const std::string& className,
                               const std::vector<std::pair<std::string, llvm::Type*>>& members) {
    std::cout << "Debug [registerClass]: Attempting to register class: " << className << std::endl;

    // Special case: Register std::exception first if needed
    if (className == "Error") {
        if (!hasClass("std::exception")) {
            std::cout << "Debug [registerClass]: Registering std::exception as base class" << std::endl;
            auto* exceptionStructType = llvm::StructType::create(context_, std::vector<llvm::Type*>(), "std::exception");
            classTypes["std::exception"] = exceptionStructType;
            classMemberInfo["std::exception"] = std::vector<std::pair<std::string, llvm::Type*>>();
            convertedMemberTypes["std::exception"] = std::unordered_map<std::string, std::shared_ptr<Type>>();
            auto exceptionType = std::make_shared<ClassType>("std::exception");
            cacheType("std::exception", exceptionType);
        }
    }

    // Skip further processing for std::exception
    if (className == "std::exception") {
        return;
    }

    // Extract short name if className contains namespace
    std::string shortName = className;
    size_t lastSeparator = className.rfind("::");
    if (lastSeparator != std::string::npos) {
        shortName = className.substr(lastSeparator + 2);
    }

    try {
        // Validate member types
        for (const auto& member : members) {
            if (!member.second) {
                throw Error("TypeError", "Null type found for member " + member.first);
            }
        }

        // Create member type list
        std::vector<llvm::Type*> memberTypes;
        for (const auto& member : members) {
            memberTypes.push_back(member.second);
        }

        // Create and register class structure with both fully qualified and short names
        auto* structType = llvm::StructType::create(context_, memberTypes, className);
        classTypes[className] = structType;
        classMemberInfo[className] = members;

        // Convert member types
        std::unordered_map<std::string, std::shared_ptr<Type>> convertedMembers;
        for (const auto& member : members) {
            auto memberType = convertLLVMTypeToType(member.second);
            if (!memberType) {
                throw Error("TypeError", "Failed to convert type for member " + member.first);
            }
            convertedMembers[member.first] = memberType;
        }
        convertedMemberTypes[className] = convertedMembers;

        // Create class type and cache it with both names
        auto classType = std::make_shared<ClassType>(className);
        cacheType(className, classType);

        // Only register short name if it's different from the full name
        if (className != shortName) {
            classTypes[shortName] = structType;
            classMemberInfo[shortName] = members;
            convertedMemberTypes[shortName] = convertedMembers;
            cacheType(shortName, classType);
        }

        // Handle Error class inheritance
        if (shortName == "Error") {
            auto baseType = getCachedType("std::exception");
            if (!baseType) {
                throw Error("TypeError", "Base class std::exception not found in cache");
            }
            classType->setBaseType(baseType);
            registerInheritance("Error", "std::exception");
        }

        // Register nullable members
        for (const auto& member : members) {
            if (member.second->isPointerTy()) {
                std::string memberPath = className + "." + member.first;
                nullableTypes.insert(memberPath);
            }
        }

        std::cout << "Debug [registerClass]: Successfully registered class " << className << std::endl;
    } catch (const Error& e) {
        // Clean up on failure
        classTypes.erase(className);
        classMemberInfo.erase(className);
        convertedMemberTypes.erase(className);
        typeCache.erase(className);
        if (className != shortName) {
            classTypes.erase(shortName);
            classMemberInfo.erase(shortName);
            convertedMemberTypes.erase(shortName);
            typeCache.erase(shortName);
        }
        throw;
    }
}

void TypeRegistry::registerClass(const std::string& className,
                               const std::vector<std::pair<std::string, llvm::Type*>>& members,
                               const std::string& baseClass) {
    std::cout << "Debug [registerClass]: Attempting to register class " << className
              << " with base class " << baseClass << std::endl;

    // First register the class normally
    registerClass(className, members);

    // Then handle inheritance
    if (baseClass == "Error" || isSubclassOf(baseClass, "Error")) {
        auto baseType = getCachedType(baseClass);
        if (!baseType) {
            throw Error("TypeError", "Base class " + baseClass + " not found in cache");
        }

        auto derivedType = getCachedType(className);
        if (!derivedType) {
            throw Error("TypeError", "Derived class " + className + " not found in cache");
        }

        // Set inheritance relationship
        std::static_pointer_cast<ClassType>(derivedType)->setBaseType(baseType);
        registerInheritance(className, baseClass);
    } else {
        throw Error("TypeError", "Error classes must extend Error or its subclasses: " + className);
    }
}

void TypeRegistry::validateErrorMethodOverride(const std::string& className,
                                             const std::string& methodName,
                                             const std::shared_ptr<FunctionType>& method,
                                             const std::string& baseClass) {
    auto baseType = getCachedType(baseClass);
    if (auto baseClassType = std::dynamic_pointer_cast<ClassType>(baseType)) {
        auto baseMethod = baseClassType->getMethod(methodName);
        if (baseMethod) {
            auto baseFuncType = std::dynamic_pointer_cast<FunctionType>(baseMethod);
            if (!method->isCompatibleWith(baseFuncType)) {
                throw Error("TypeError", "Method override in " + className +
                          " is not compatible with base method in " + baseClass);
            }
        }
    }
}

void TypeRegistry::validateErrorChain(const std::string& errorClass,
                                    const std::string& chainedClass) {
    // Validate both classes are error types
    if (!isErrorType(errorClass)) {
        throw Error("TypeError", "Class " + errorClass + " must be an Error type to support chaining");
    }
    if (!isErrorType(chainedClass)) {
        throw Error("TypeError", "Chained class " + chainedClass + " must be an Error type");
    }

    // Check for circular dependencies in error chain
    std::set<std::string> visited;
    std::function<void(const std::string&)> checkCircular = [&](const std::string& current) {
        if (visited.find(current) != visited.end()) {
            throw Error("TypeError", "Circular dependency detected in error chain");
        }
        visited.insert(current);

        auto type = getCachedType(current);
        if (auto classType = std::dynamic_pointer_cast<ClassType>(type)) {
            if (auto causeField = classType->getField("cause")) {
                if (auto nullableType = std::dynamic_pointer_cast<NullableType>(causeField)) {
                    auto innerType = nullableType->getInnerType();
                    if (auto innerClass = std::dynamic_pointer_cast<ClassType>(innerType)) {
                        checkCircular(innerClass->getName());
                    }
                }
            }
        }
    };

    checkCircular(errorClass);
}

bool TypeRegistry::isErrorType(const std::string& className) const {
    if (className == "Error") return true;
    auto type = getCachedType(className);
    if (!type) return false;

    if (auto classType = std::dynamic_pointer_cast<ClassType>(type)) {
        return classType->getName() == "Error" ||
               (classType->getParent() && isErrorType(classType->getParent()->getName()));
    }
    return false;
}

std::shared_ptr<Type> TypeRegistry::createErrorChainType(const std::string& errorClass,
                                                     const std::string& chainedClass) {
    // Validate error chain using enhanced validation
    validateErrorChain(errorClass, chainedClass);

    auto errorType = getCachedType(errorClass);
    auto chainedType = getCachedType(chainedClass);

    if (auto errorClassType = std::dynamic_pointer_cast<ClassType>(errorType)) {
        // Create new error chain type with proper inheritance
        auto chainedErrorType = std::make_shared<ClassType>(errorClass);
        chainedErrorType->setParent(errorClassType);

        // Copy all fields from the original error class
        for (const auto& name : errorClassType->getAvailableMembers()) {
            chainedErrorType->addField(name, errorClassType->getField(name));
        }

        // Add nullable cause field with proper type
        auto nullableCause = std::make_shared<NullableType>(chainedType);
        chainedErrorType->addField("cause", nullableCause);

        // Cache the new error chain type
        cacheType(errorClass + "WithCause", chainedErrorType);
        return chainedErrorType;
    }

    throw Error("TypeError", "Failed to create error chain type for " + errorClass);
}

bool TypeRegistry::isErrorType(const std::string& className) const {
    return className == "Error" || isSubclassOf(className, "Error");
}

void TypeRegistry::registerInheritance(const std::string& derived, const std::string& base) {
    if (!hasClass(derived)) {
        throw Error("Derived class " + derived + " not found in registry");
    }
    if (!hasClass(base)) {
        throw Error("Base class " + base + " not found in registry");
    }
    inheritance[derived] = base;
}

bool TypeRegistry::isSubclassOf(const std::string& derived, const std::string& base) const {
    if (derived == base) {
        return true;
    }

    auto it = inheritance.find(derived);
    if (it == inheritance.end()) {
        return false;
    }

    return isSubclassOf(it->second, base);
}

llvm::StructType* TypeRegistry::getClassType(const std::string& className) {
    if (!hasClass(className)) {
        throw Error("Class " + className + " not found in registry");
    }
    return classTypes[className];
}

int TypeRegistry::getMemberIndex(const std::string& className, const std::string& memberName) {
    std::cout << "Getting member index for " << className << "::" << memberName << std::endl;

    if (!hasClass(className)) {
        throw Error("Class " + className + " not found in registry");
    }

    const auto& members = classMemberInfo[className];
    std::cout << "Class " << className << " has " << members.size() << " members:" << std::endl;
    for (size_t i = 0; i < members.size(); ++i) {
        std::cout << "  " << i << ": " << members[i].first << std::endl;
    }

    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i].first == memberName) {
            return static_cast<int>(i);
        }
    }

    throw Error("Member " + memberName + " not found in class " + className);
}

void TypeRegistry::registerMemberIndex(const std::string& className, const std::string& memberName, int index) {
    if (!hasClass(className)) {
        throw Error("Class " + className + " not found in registry");
    }

    auto& members = classMemberInfo[className];
    if (static_cast<size_t>(index) >= members.size()) {
        throw Error("Invalid member index " + std::to_string(index) +
                               " for class " + className);
    }

    members[index].first = memberName;
}

bool TypeRegistry::hasClass(const std::string& className) const {
    std::cout << "Debug [hasClass]: Checking for class: " << className << std::endl;

    // First try exact match
    if (classTypes.find(className) != classTypes.end()) {
        std::cout << "Debug [hasClass]: Found exact match for " << className << std::endl;
        return true;
    }

    // If the class name contains namespace separators (::), try variations
    size_t lastSeparator = className.rfind("::");
    if (lastSeparator != std::string::npos) {
        // Try short name
        std::string shortName = className.substr(lastSeparator + 2);
        if (classTypes.find(shortName) != classTypes.end()) {
            std::cout << "Debug [hasClass]: Found short name match: " << shortName << std::endl;
            return true;
        }

        // Try namespace variations
        std::string currentNs = "";
        std::string remainingName = className;
        while ((lastSeparator = remainingName.find("::")) != std::string::npos) {
            currentNs += (currentNs.empty() ? "" : "::") + remainingName.substr(0, lastSeparator);
            remainingName = remainingName.substr(lastSeparator + 2);
            std::string tryName = currentNs + "::" + remainingName;

            std::cout << "Debug [hasClass]: Trying namespace variation: " << tryName << std::endl;
            if (classTypes.find(tryName) != classTypes.end()) {
                std::cout << "Debug [hasClass]: Found namespace variation match: " << tryName << std::endl;
                return true;
            }
        }
    }

    std::cout << "Debug [hasClass]: Class not found: " << className << std::endl;
    return false;
}

llvm::Type* TypeRegistry::getMemberType(const std::string& className, int index) {
    if (!hasClass(className)) {
        throw Error("Class " + className + " not found in registry");
    }

    const auto& members = classMemberInfo[className];
    if (index < 0 || static_cast<size_t>(index) >= members.size()) {
        throw Error("Invalid member index " + std::to_string(index) +
                               " for class " + className);
    }

    return members[index].second;
}

void TypeRegistry::registerConstructor(const std::string& className, const std::vector<llvm::Type*>& paramTypes) {
    std::cout << "Registering constructor for class " << className << std::endl;
    if (!hasClass(className)) {
        throw Error("Class " + className + " not found in registry");
    }
    constructorParams[className] = paramTypes;
}

bool TypeRegistry::hasConstructor(const std::string& className) const {
    bool has = constructorParams.find(className) != constructorParams.end();
    std::cout << "Checking if class " << className << " has constructor: " << (has ? "yes" : "no") << std::endl;
    return has;
}

const std::vector<llvm::Type*>& TypeRegistry::getConstructorParams(const std::string& className) {
    if (!hasConstructor(className)) {
        throw Error("Constructor not found for class " + className);
    }
    return constructorParams[className];
}

const std::vector<std::pair<std::string, llvm::Type*>>& TypeRegistry::getClassMembers(const std::string& className) const {
    auto it = classMemberInfo.find(className);
    if (it == classMemberInfo.end()) {
        throw Error("Class " + className + " not found in registry");
    }
    std::cout << "Getting members for class " << className << ", found " << it->second.size() << " members" << std::endl;
    return it->second;
}

std::shared_ptr<Type> TypeRegistry::convertLLVMTypeToType(llvm::Type* llvmType) {
    std::cout << "Debug [convertLLVMTypeToType]: Starting type conversion" << std::endl;

    if (!llvmType) {
        std::cout << "Debug [convertLLVMTypeToType]: Received null LLVM type" << std::endl;
        throw Error("TypeError", "Received null LLVM type");
    }

    // Add initial type inspection
    std::cout << "Debug [convertLLVMTypeToType]: Initial type info:" << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is pointer: " << llvmType->isPointerTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is function: " << llvmType->isFunctionTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is struct: " << llvmType->isStructTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Raw type: ";
    llvmType->print(llvm::errs());
    std::cout << std::endl;

    std::cout << "Debug [convertLLVMTypeToType]: Converting LLVM type: ";
    llvmType->print(llvm::errs());
    std::cout << std::endl;

    // Check if it's a struct type (either direct or through pointer)
    llvm::StructType* structType = nullptr;
    bool isPointer = false;
    llvm::Type* baseType = llvmType;

    if (llvmType->isPointerTy()) {
        baseType = llvmType->getPointerElementType();
        isPointer = true;
        if (auto* st = llvm::dyn_cast<llvm::StructType>(baseType)) {
            structType = st;
        }
    } else if (llvmType->isStructTy()) {
        structType = llvm::cast<llvm::StructType>(llvmType);
    }

    // Handle class types first
    if (structType) {
        std::string className = structType->getName().str();
        if (!className.empty()) {
            std::cout << "Debug [convertLLVMTypeToType]: Found class type: " << className << std::endl;

            // Special handling for std::exception and Error
            if (className == "std::exception") {
                std::cout << "Debug [convertLLVMTypeToType]: Special handling for std::exception" << std::endl;
                auto exceptionType = std::make_shared<ClassType>("std::exception");
                if (isPointer && isTypeNullable(llvmType)) {
                    return std::make_shared<NullableType>(exceptionType);
                }
                return exceptionType;
            }

            if (className == "Error") {
                std::cout << "Debug [convertLLVMTypeToType]: Special handling for Error class" << std::endl;
                // Ensure std::exception is registered and cached
                if (!hasClass("std::exception")) {
                    std::vector<std::pair<std::string, llvm::Type*>> exceptionMembers;
                    auto* exceptionStructType = llvm::StructType::create(context_, "std::exception");
                    classTypes["std::exception"] = exceptionStructType;
                    classMemberInfo["std::exception"] = exceptionMembers;
                    auto exceptionType = std::make_shared<ClassType>("std::exception");
                    cacheType("std::exception", exceptionType);
                }

                // Get cached std::exception type and create Error type with inheritance
                auto baseType = getCachedType("std::exception");
                if (!baseType) {
                    throw Error("TypeError", "Base class std::exception not found in cache");
                }
                auto errorType = std::make_shared<ClassType>("Error");
                errorType->setBaseType(baseType);
                cacheType("Error", errorType);
                registerInheritance("Error", "std::exception");

                if (isPointer && isTypeNullable(llvmType)) {
                    return std::make_shared<NullableType>(errorType);
                }
                return errorType;
            }
            // Check if class exists before checking cache
            if (!hasClass(className)) {
                std::string errorMsg = "Class " + className + " not found in registry";
                std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
                throw Error("TypeError", errorMsg);
            }

            // Check cache
            auto cachedType = getCachedType(className);
            if (cachedType) {
                std::cout << "Debug [convertLLVMTypeToType]: Using cached type for " << className << std::endl;
                if (isPointer && isTypeNullable(llvmType)) {
                    return std::make_shared<NullableType>(cachedType);
                }
                return cachedType;
            }

            // Create new class type
            auto classType = std::make_shared<ClassType>(className);

            // Cache immediately to handle recursive types
            cacheType(className, classType);

            try {
                // First add base class members if this class inherits from another
                auto it = inheritance.find(className);
                if (it != inheritance.end()) {
                    std::cout << "Debug [convertLLVMTypeToType]: Class " << className << " inherits from " << it->second << std::endl;
                    const auto& baseMembers = getClassMembers(it->second);
                    for (const auto& member : baseMembers) {
                        std::cout << "Debug [convertLLVMTypeToType]: Adding base class member " << member.first << std::endl;
                        auto memberType = convertLLVMTypeToType(member.second);
                        if (!memberType) {
                            std::string errorMsg = "Failed to convert type for base class member " + member.first;
                            std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
                            throw Error("TypeError", errorMsg);
                        }
                        classType->addField(member.first, memberType);
                    }
                }

                // Then add this class's members
                const auto& members = getClassMembers(className);
                for (const auto& member : members) {
                    std::cout << "Debug [convertLLVMTypeToType]: Converting member " << member.first << " of class " << className << std::endl;
                    auto memberType = convertLLVMTypeToType(member.second);
                    if (!memberType) {
                        std::string errorMsg = "Failed to convert type for member " + member.first + " in class " + className;
                        std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
                        throw Error("TypeError", errorMsg);
                    }
                    classType->addField(member.first, memberType);
                }

                if (isPointer && isTypeNullable(llvmType)) {
                    auto nullableType = std::make_shared<NullableType>(classType);
                    return nullableType;
                }
                return classType;
            } catch (const Error& e) {
                std::string errorMsg(e.what());
                if (errorMsg.find("not found in registry") != std::string::npos) {
                    typeCache.erase(className);
                }
                throw;
            }
        } // end of if (!className.empty())
    } // end of if (structType)

    // Handle pointer types
    if (llvmType->isPointerTy()) {
        auto elementType = llvmType->getPointerElementType();
        std::cout << "Debug [convertLLVMTypeToType]: Processing pointer type with element: ";
        elementType->print(llvm::errs());
        std::cout << std::endl;

        // Handle string type (i8*)
        if (elementType->isIntegerTy(8)) {
            std::cout << "Debug [convertLLVMTypeToType]: Identified as STRING_TYPE" << std::endl;
            if (isTypeNullable(llvmType)) {
                std::cout << "Debug [convertLLVMTypeToType]: Creating nullable STRING_TYPE" << std::endl;
                return std::make_shared<NullableType>(STRING_TYPE);
            }
            return STRING_TYPE;
        }

        // Handle double pointer to i8 (i8**) as string
        if (elementType->isPointerTy() && elementType->getPointerElementType()->isIntegerTy(8)) {
            std::cout << "Debug [convertLLVMTypeToType]: Identified as STRING_TYPE (double pointer)" << std::endl;
            if (isTypeNullable(llvmType)) {
                std::cout << "Debug [convertLLVMTypeToType]: Creating nullable STRING_TYPE (double pointer)" << std::endl;
                return std::make_shared<NullableType>(STRING_TYPE);
            }
            return STRING_TYPE;
        }

        // Handle pointer to i32 as nullable int
        if (elementType->isIntegerTy(32)) {
            std::cout << "Debug [convertLLVMTypeToType]: Identified as INT_TYPE (pointer)" << std::endl;
            // Always treat pointer to i32 as nullable int
            std::cout << "Debug [convertLLVMTypeToType]: Creating nullable INT_TYPE" << std::endl;
            return std::make_shared<NullableType>(INT_TYPE);
        }
        // Recursively handle other pointer types
        auto baseType = convertLLVMTypeToType(elementType);
        if (baseType && isTypeNullable(llvmType)) {
            return std::make_shared<NullableType>(baseType);
        }
        return baseType;
    }

    // Handle basic types
    if (llvmType->isIntegerTy(32)) {
        std::cout << "Debug [convertLLVMTypeToType]: Identified as INT_TYPE" << std::endl;
        auto type = INT_TYPE;
        // Add primitive methods
        for (const auto& [methodName, methodType] : getPrimitiveMethods("int")) {
            std::cout << "Debug [convertLLVMTypeToType]: Adding method " << methodName << " to INT_TYPE" << std::endl;
            type->addMethod(methodName, convertLLVMTypeToType(methodType));
        }
        return type;
    }
    if (llvmType->isFloatTy() || llvmType->isDoubleTy()) {
        std::cout << "Debug [convertLLVMTypeToType]: Identified as FLOAT_TYPE" << std::endl;
        auto type = FLOAT_TYPE;
        // Add primitive methods
        for (const auto& [methodName, methodType] : getPrimitiveMethods("float")) {
            std::cout << "Debug [convertLLVMTypeToType]: Adding method " << methodName << " to FLOAT_TYPE" << std::endl;
            type->addMethod(methodName, convertLLVMTypeToType(methodType));
        }
        return type;
    }
    if (llvmType->isIntegerTy(1)) {
        std::cout << "Debug [convertLLVMTypeToType]: Identified as BOOL_TYPE" << std::endl;
        auto type = BOOL_TYPE;
        // Add primitive methods
        for (const auto& [methodName, methodType] : getPrimitiveMethods("bool")) {
            std::cout << "Debug [convertLLVMTypeToType]: Adding method " << methodName << " to BOOL_TYPE" << std::endl;
            type->addMethod(methodName, convertLLVMTypeToType(methodType));
        }
        return type;
    }

    // Handle function types
    if (llvmType->isFunctionTy()) {
        std::cout << "Debug [convertLLVMTypeToType]: Found function type" << std::endl;
        auto* funcType = llvm::cast<llvm::FunctionType>(llvmType);

        // Print detailed debug info
        std::cout << "Debug [convertLLVMTypeToType]: Function return type: ";
        funcType->getReturnType()->print(llvm::errs());
        std::cout << std::endl;

        // Convert return type with detailed error handling
        auto returnType = convertLLVMTypeToType(funcType->getReturnType());
        if (!returnType) {
            std::string errorMsg = "Failed to convert function return type: ";
            llvm::raw_string_ostream rso(errorMsg);
            funcType->getReturnType()->print(rso);
            std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
            throw Error("TypeError", errorMsg);
        }

        // Handle nullable return type for methods
        if (isTypeNullable(funcType->getReturnType())) {
            std::cout << "Debug [convertLLVMTypeToType]: Making return type nullable" << std::endl;
            returnType = std::make_shared<NullableType>(returnType);
        }

        // Convert parameter types with detailed error handling
        std::vector<std::shared_ptr<Type>> paramTypes;
        for (const auto& paramType : funcType->params()) {
            std::cout << "Debug [convertLLVMTypeToType]: Converting parameter type: ";
            paramType->print(llvm::errs());
            std::cout << std::endl;

            auto convertedType = convertLLVMTypeToType(paramType);
            if (!convertedType) {
                std::string errorMsg = "Failed to convert function parameter type: ";
                llvm::raw_string_ostream rso(errorMsg);
                paramType->print(rso);
                std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
                throw Error("TypeError", errorMsg);
            }

            // Handle nullable parameter types
            if (isTypeNullable(paramType)) {
                std::cout << "Debug [convertLLVMTypeToType]: Making parameter type nullable" << std::endl;
                convertedType = std::make_shared<NullableType>(convertedType);
            }

            paramTypes.push_back(convertedType);
        }

        auto functionType = std::make_shared<FunctionType>(returnType, paramTypes);

        // Handle nullable function type (for method pointers)
        if (isTypeNullable(llvmType)) {
            std::cout << "Debug [convertLLVMTypeToType]: Making function type nullable" << std::endl;
            return std::make_shared<NullableType>(functionType);
        }

        return functionType;
    }

    // Handle array types
    if (llvmType->isArrayTy()) {
        std::cout << "Debug [convertLLVMTypeToType]: Found array type" << std::endl;
        auto elementType = convertLLVMTypeToType(llvmType->getArrayElementType());
        if (elementType) {
            return std::make_shared<ArrayType>(elementType);
        }
    }

    // Handle map types
    if (llvmType->isStructTy()) {
        auto* structType = llvm::cast<llvm::StructType>(llvmType);
        std::string typeName = structType->getName().str();

        // Check if this is a map type
        if (typeName.find("map<") == 0 || typeName.find("struct.map<") == 0) {
            std::cout << "Debug [convertLLVMTypeToType]: Found map type: " << typeName << std::endl;

            // Map should have two elements: key and value types
            if (structType->getNumElements() == 2) {
                auto keyType = convertLLVMTypeToType(structType->getElementType(0));
                auto valueType = convertLLVMTypeToType(structType->getElementType(1));

                if (keyType && valueType) {
                    auto mapType = std::make_shared<MapType>(keyType, valueType);
                    // Cache the map type with its full generic type name
                    std::string fullTypeName = "map<" + keyType->toString() + "," + valueType->toString() + ">";
                    cacheType(fullTypeName, mapType);
                    return mapType;
                }
            }
        }
    }

    // Handle unknown types with more detailed error reporting
    std::string errorMsg = "Unable to convert LLVM type: ";
    llvm::raw_string_ostream rso(errorMsg);
    llvmType->print(rso);

    // Add detailed type information
    std::cout << "Debug [convertLLVMTypeToType]: Unknown type encountered - detailed info:" << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Type kind: " << llvmType->getTypeID() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is pointer: " << llvmType->isPointerTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is function: " << llvmType->isFunctionTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is struct: " << llvmType->isStructTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is array: " << llvmType->isArrayTy() << std::endl;
    std::cout << "Debug [convertLLVMTypeToType]: Is integer: " << llvmType->isIntegerTy() << std::endl;
    if (llvmType->isIntegerTy()) {
        std::cout << "Debug [convertLLVMTypeToType]: Integer bits: " << llvmType->getIntegerBitWidth() << std::endl;
    }
    std::cout << "Debug [convertLLVMTypeToType]: Raw type string: " << errorMsg << std::endl;

    if (llvmType->isPointerTy()) {
        std::cout << "Debug [convertLLVMTypeToType]: Pointer element type: ";
        llvmType->getPointerElementType()->print(llvm::errs());
        std::cout << std::endl;

        auto elementType = llvmType->getPointerElementType();
        std::cout << "Debug [convertLLVMTypeToType]: Element type kind: " << elementType->getTypeID() << std::endl;
        std::cout << "Debug [convertLLVMTypeToType]: Element is pointer: " << elementType->isPointerTy() << std::endl;
        std::cout << "Debug [convertLLVMTypeToType]: Element is struct: " << elementType->isStructTy() << std::endl;
        std::cout << "Debug [convertLLVMTypeToType]: Element is integer: " << elementType->isIntegerTy() << std::endl;
    }

    std::cout << "Debug [convertLLVMTypeToType]: " << errorMsg << std::endl;
    throw Error("TypeError", errorMsg);
}

std::shared_ptr<Type> TypeRegistry::registerFunctionType(const std::string& returnType,
                                                      const std::vector<std::string>& paramTypes) {
    std::cout << "Debug [registerFunctionType]: Registering function type with return type: "
              << returnType << std::endl;

    // Convert return type
    auto returnTypeObj = getCachedType(returnType);
    if (!returnTypeObj) {
        throw Error("TypeError", "Unknown return type: " + returnType);
    }

    // Convert parameter types
    std::vector<std::shared_ptr<Type>> paramTypeObjs;
    for (const auto& paramType : paramTypes) {
        std::cout << "Debug [registerFunctionType]: Converting parameter type: " << paramType << std::endl;
        auto paramTypeObj = getCachedType(paramType);
        if (!paramTypeObj) {
            throw Error("TypeError", "Unknown parameter type: " + paramType);
        }
        paramTypeObjs.push_back(paramTypeObj);
    }

    // Create function type
    auto functionType = std::make_shared<FunctionType>(returnTypeObj, paramTypeObjs);

    // Generate unique type name for caching
    std::string functionTypeName = "fn<" + returnType + ">(";
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) functionTypeName += ",";
        functionTypeName += paramTypes[i];
    }
    functionTypeName += ")";

    // Cache the function type
    cacheType(functionTypeName, functionType);
    std::cout << "Debug [registerFunctionType]: Registered function type: " << functionTypeName << std::endl;

    return functionType;
}

bool TypeRegistry::isTypeNullable(llvm::Type* type) const {
    if (!type) return false;

    // If it's a pointer type, check the element type
    if (type->isPointerTy()) {
        auto elementType = type->getPointerElementType();
        std::cout << "Debug [isTypeNullable]: Checking pointer type" << std::endl;

        // Check if it's a struct type
        if (auto* structType = llvm::dyn_cast<llvm::StructType>(elementType)) {
            std::string typeName = structType->getName().str();
            std::cout << "Debug [isTypeNullable]: Checking struct type: " << typeName << std::endl;

            // Check if the type is registered as nullable or has '?' suffix
            if (nullableTypes.find(typeName) != nullableTypes.end() ||
                (typeName.length() > 0 && typeName.back() == '?')) {
                std::cout << "Debug [isTypeNullable]: Type " << typeName << " is nullable" << std::endl;
                return true;
            }

            // Check if any members of this type are nullable
            if (hasClass(typeName)) {
                const auto& members = getClassMembers(typeName);
                for (const auto& member : members) {
                    std::string memberPath = typeName + "." + member.first;
                    if (nullableTypes.find(memberPath) != nullableTypes.end()) {
                        std::cout << "Debug [isTypeNullable]: Member " << memberPath << " is nullable" << std::endl;
                        return true;
                    }
                }
            }
        }

        // Check if it's a basic type that's nullable (like int? or str?)
        if (elementType->isIntegerTy(32) || elementType->isIntegerTy(8) ||
            elementType->isFloatTy() || elementType->isDoubleTy()) {
            std::cout << "Debug [isTypeNullable]: Basic type is nullable" << std::endl;
            return true;
        }
    }

    // Check if the type itself is nullable
    if (auto* structType = llvm::dyn_cast<llvm::StructType>(type)) {
        std::string typeName = structType->getName().str();
        return nullableTypes.find(typeName) != nullableTypes.end() ||
               (typeName.length() > 0 && typeName.back() == '?');
    }

    return false;
}

std::shared_ptr<Type> TypeRegistry::getMemberPrystType(const std::string& className, const std::string& memberName) {
    if (!hasClass(className)) {
        throw Error("Class " + className + " not found");
    }

    const auto& convertedMembers = convertedMemberTypes[className];
    auto it = convertedMembers.find(memberName);
    if (it == convertedMembers.end()) {
        throw Error("Member " + memberName + " not found in class " + className);
    }

    return it->second;
}

llvm::Type* TypeRegistry::convertTypeToLLVMType(std::shared_ptr<Type> type) {
    std::cout << "Debug [convertTypeToLLVMType]: Converting type: " << type->toString() << std::endl;

    if (!type) {
        throw Error("TypeError", "Received null type");
    }

    // Handle primitive types
    if (type == INT_TYPE) {
        return llvm::Type::getInt32Ty(context_);
    }
    if (type == FLOAT_TYPE) {
        return llvm::Type::getFloatTy(context_);
    }
    if (type == BOOL_TYPE) {
        return llvm::Type::getInt1Ty(context_);
    }
    if (type == STRING_TYPE) {
        // String type is always a pointer to i8
        auto stringType = llvm::PointerType::get(llvm::Type::getInt8Ty(context_), 0);
        std::cout << "Debug [convertTypeToLLVMType]: Created string type (i8*)" << std::endl;
        return stringType;
    }

    // Handle nullable types
    if (auto nullableType = std::dynamic_pointer_cast<NullableType>(type)) {
        auto baseType = convertTypeToLLVMType(nullableType->getInnerType());
        if (!baseType) {
            throw Error("TypeError", "Failed to convert base type of nullable type");
        }
        return llvm::PointerType::get(baseType, 0);
    }

    // Handle map types
    std::cout << "Debug [convertTypeToLLVMType]: Before map type cast, type kind=" << type->getKind()
              << ", type address=" << type.get()
              << ", typeid=" << typeid(*type.get()).name() << std::endl;
    if (auto mapType = std::dynamic_pointer_cast<MapType>(type)) {
        std::cout << "Debug [convertTypeToLLVMType]: Converting map type with key="
                  << mapType->getKeyType()->toString()
                  << " value=" << mapType->getValueType()->toString() << std::endl;

        auto keyType = convertTypeToLLVMType(mapType->getKeyType());
        if (!keyType) {
            throw Error("TypeError", "Failed to convert map key type: " + mapType->getKeyType()->toString());
        }

        auto valueType = convertTypeToLLVMType(mapType->getValueType());
        if (!valueType) {
            throw Error("TypeError", "Failed to convert map value type: " + mapType->getValueType()->toString());
        }

        std::vector<llvm::Type*> elementTypes = {keyType, valueType};
        std::string mapTypeName = "map<" + mapType->getKeyType()->toString() + "," + mapType->getValueType()->toString() + ">";

        // Check if we already have this type registered
        if (classTypes.find(mapTypeName) != classTypes.end()) {
            return classTypes[mapTypeName];
        }

        // Create and register the map type
        auto mapStructType = llvm::StructType::create(context_, elementTypes, mapTypeName);
        classTypes[mapTypeName] = mapStructType;

        // Cache the map type in typeCache
        cacheType(mapTypeName, mapType);

        // Also register any potential LLVM-suffixed versions
        std::string suffixedName = mapTypeName + ".0";
        classTypes[suffixedName] = mapStructType;
        cacheType(suffixedName, mapType);

        // Register members for both names
        std::vector<std::pair<std::string, llvm::Type*>> mapMembers;
        mapMembers.push_back({"key", keyType});
        mapMembers.push_back({"value", valueType});
        classMemberInfo[mapTypeName] = mapMembers;
        classMemberInfo[suffixedName] = mapMembers;

        std::cout << "Debug [convertTypeToLLVMType]: Created and registered map struct type: " << mapTypeName
                  << " and " << suffixedName << std::endl;
        return mapStructType;
    }

    // Handle class types
    if (auto classType = std::dynamic_pointer_cast<ClassType>(type)) {
        std::string className = classType->getName();
        if (hasClass(className)) {
            auto* structType = getClassType(className);
            if (!structType) {
                throw Error("TypeError", "Failed to get LLVM type for class " + className);
            }
            return structType;
        }
        throw Error("TypeError", "Class " + className + " not found in registry");
    }

    // Handle array types
    if (auto arrayType = std::dynamic_pointer_cast<ArrayType>(type)) {
        auto elementType = convertTypeToLLVMType(arrayType->getElementType());
        if (!elementType) {
            throw Error("TypeError", "Failed to convert array element type");
        }
        return llvm::ArrayType::get(elementType, 0);  // Dynamic size array
    }

    // Handle function types
    if (auto functionType = std::dynamic_pointer_cast<FunctionType>(type)) {
        std::vector<llvm::Type*> paramTypes;
        for (const auto& paramType : functionType->getParameterTypes()) {
            auto llvmParamType = convertTypeToLLVMType(paramType);
            if (!llvmParamType) {
                throw Error("TypeError", "Failed to convert function parameter type");
            }
            paramTypes.push_back(llvmParamType);
        }
        auto returnType = convertTypeToLLVMType(functionType->getReturnType());
        if (!returnType) {
            throw Error("TypeError", "Failed to convert function return type");
        }
        return llvm::FunctionType::get(returnType, paramTypes, false);
    }

    std::string errorMsg = "Unable to convert type: " + type->toString();
    std::cout << "Debug [convertTypeToLLVMType]: " << errorMsg << std::endl;
    throw Error("TypeError", errorMsg);
}

// Register a map type with key and value types
std::shared_ptr<Type> TypeRegistry::registerMapType(const std::string& keyType, const std::string& valueType) {
    std::cout << "Debug [registerMapType]: Registering map type with key=" << keyType << " value=" << valueType << std::endl;

    // Get or convert key type
    auto keyTypeObj = getCachedType(keyType);
    if (!keyTypeObj) {
        throw Error("TypeError", "Unknown key type: " + keyType);
    }

    // Get or convert value type
    auto valueTypeObj = getCachedType(valueType);
    if (!valueTypeObj) {
        throw Error("TypeError", "Unknown value type: " + valueType);
    }

    // Create map type
    auto mapType = std::make_shared<MapType>(keyTypeObj, valueTypeObj);
    std::string mapTypeName = "map<" + keyType + "," + valueType + ">";

    // Convert to LLVM type and cache
    auto llvmType = convertTypeToLLVMType(mapType);
    if (!llvmType) {
        throw Error("TypeError", "Failed to convert map type to LLVM type");
    }

    // Cache the type
    cacheType(mapTypeName, mapType);

    std::cout << "Debug [registerMapType]: Successfully registered map type: " << mapTypeName << std::endl;
    return mapType;
}

// Register an array type
std::shared_ptr<Type> TypeRegistry::registerArrayType(const std::string& elementType) {
    std::cout << "Debug [registerArrayType]: Registering array type with element type=" << elementType << std::endl;

    // Get or convert element type
    auto elementTypeObj = getCachedType(elementType);
    if (!elementTypeObj) {
        throw Error("TypeError", "Unknown element type: " + elementType);
    }

    // Create array type
    auto arrayType = std::make_shared<ArrayType>(elementTypeObj);
    std::string arrayTypeName = elementType + "[]";

    // Convert to LLVM type and cache
    auto llvmType = convertTypeToLLVMType(arrayType);
    if (!llvmType) {
        throw Error("TypeError", "Failed to convert array type to LLVM type");
    }

    // Cache the type
    cacheType(arrayTypeName, arrayType);

    std::cout << "Debug [registerArrayType]: Successfully registered array type: " << arrayTypeName << std::endl;
    return arrayType;
}

void TypeRegistry::registerNamespace(const std::string& ns) {
    std::cout << "Debug [registerNamespace]: Registering namespace: " << ns << std::endl;

    // Skip empty namespace
    if (ns.empty()) {
        return;
    }

    // Check if namespace is already registered
    if (registeredNamespaces.find(ns) != registeredNamespaces.end()) {
        std::cout << "Debug [registerNamespace]: Namespace already registered: " << ns << std::endl;
        return;
    }

    // Register parent namespaces first
    size_t pos = 0;
    while ((pos = ns.find("::", pos)) != std::string::npos) {
        std::string parentNs = ns.substr(0, pos);
        if (!parentNs.empty() && registeredNamespaces.find(parentNs) == registeredNamespaces.end()) {
            std::cout << "Debug [registerNamespace]: Registering parent namespace: " << parentNs << std::endl;
            registeredNamespaces.insert(parentNs);
        }
        pos += 2;
    }

    // Register the full namespace
    std::cout << "Debug [registerNamespace]: Registering full namespace: " << ns << std::endl;
    registeredNamespaces.insert(ns);
}

void TypeRegistry::registerNamespaceAlias(const std::string& alias, const std::string& target) {
    std::cout << "Debug [registerNamespaceAlias]: Registering alias " << alias << " -> " << target << std::endl;
    namespaceAliases[alias] = target;
}

bool TypeRegistry::isNamespaceRegistered(const std::string& ns) const {
    std::cout << "Debug [isNamespaceRegistered]: Checking namespace: " << ns << std::endl;

    // Check direct registration first
    if (registeredNamespaces.find(ns) != registeredNamespaces.end()) {
        std::cout << "Debug [isNamespaceRegistered]: Found direct registration for " << ns << std::endl;
        return true;
    }

    // Check if it's an alias
    auto it = namespaceAliases.find(ns);
    if (it != namespaceAliases.end()) {
        std::cout << "Debug [isNamespaceRegistered]: Found alias for " << ns << " -> " << it->second << std::endl;
        return isNamespaceRegistered(it->second);
    }

    // Don't consider parent namespace registration as sufficient
    // The full namespace path must be registered
    std::cout << "Debug [isNamespaceRegistered]: Namespace not found: " << ns << std::endl;
    return false;
}

std::string TypeRegistry::resolveNamespace(const std::string& ns) const {
    std::cout << "Debug [resolveNamespace]: Resolving namespace: " << ns << std::endl;

    // Check if it's an alias
    auto it = namespaceAliases.find(ns);
    if (it != namespaceAliases.end()) {
        std::cout << "Debug [resolveNamespace]: Found alias " << ns << " -> " << it->second << std::endl;
        return resolveNamespace(it->second);
    }

    // If it's a registered namespace, return it directly
    if (registeredNamespaces.find(ns) != registeredNamespaces.end()) {
        std::cout << "Debug [resolveNamespace]: Found direct registration for " << ns << std::endl;
        return ns;
    }

    // Try to resolve parent namespace
    size_t separator = ns.find("::");
    if (separator != std::string::npos) {
        std::string parentNs = ns.substr(0, separator);
        std::string remainder = ns.substr(separator + 2);
        std::cout << "Debug [resolveNamespace]: Checking parent namespace: " << parentNs << " with remainder: " << remainder << std::endl;
        std::string resolvedParent = resolveNamespace(parentNs);
        if (!resolvedParent.empty()) {
            std::string resolved = resolvedParent + "::" + remainder;
            std::cout << "Debug [resolveNamespace]: Resolved to: " << resolved << std::endl;
            return resolved;
        }
    }

    std::cout << "Debug [resolveNamespace]: Namespace not found: " << ns << std::endl;
    return "";  // Namespace not found
}

std::vector<std::string> TypeRegistry::getRegisteredNamespaces() const {
    std::vector<std::string> namespaces;
    namespaces.insert(namespaces.end(), registeredNamespaces.begin(), registeredNamespaces.end());
    return namespaces;
}

std::shared_ptr<Type> TypeRegistry::getFunctionType(const std::string& functionName) const {
    std::cout << "Debug [getFunctionType]: Looking up function type for: " << functionName << std::endl;

    // Look up function type in typeCache
    auto it = typeCache.find(functionName);
    if (it != typeCache.end()) {
        std::cout << "Debug [getFunctionType]: Found cached type for: " << functionName << std::endl;
        return it->second;
    }

    std::cout << "Debug [getFunctionType]: No type found for function: " << functionName << std::endl;
    return nullptr;
}

// Get LLVM type for a Pryst type
llvm::Type* TypeRegistry::getLLVMType(std::shared_ptr<Type> type) {
    std::cout << "Debug [getLLVMType]: Converting type " << type->toString() << std::endl;
    auto llvmType = convertTypeToLLVMType(type);
    if (!llvmType) {
        std::cerr << "Error [getLLVMType]: Failed to convert type " << type->toString() << std::endl;
        throw Error("TypeError", "Failed to convert type " + type->toString());
    }
    return llvmType;
}

// Get bool type
llvm::Type* TypeRegistry::getBoolType() const {
    return classTypes.at("bool");
}

// Get all registered types
const std::unordered_map<std::string, std::shared_ptr<Type>>& TypeRegistry::getAllTypes() const {
    return typeCache;
}

// Register interface type
void TypeRegistry::registerInterfaceType(std::shared_ptr<InterfaceType> interfaceType) {
    std::cout << "Debug [registerInterfaceType]: Registering interface " << interfaceType->getName() << std::endl;
    cacheType(interfaceType->getName(), interfaceType);
}

// Check if a class implements an interface
bool TypeRegistry::implementsInterface(const std::string& className, const std::string& interfaceName) const {
    auto it = interfaceImplementations.find(className);
    if (it != interfaceImplementations.end()) {
        return it->second.find(interfaceName) != it->second.end();
    }
    return false;
}

// Register interface implementation
void TypeRegistry::registerInterfaceImplementation(const std::string& className, const std::string& interfaceName) {
    std::cout << "Debug [registerInterfaceImplementation]: Registering " << className << " implements " << interfaceName << std::endl;

    // Verify class exists
    if (!hasClass(className)) {
        throw Error("TypeError", "Class not found: " + className);
    }

    // Verify interface exists in type cache
    auto interfaceType = getCachedType(interfaceName);
    if (!interfaceType || !std::dynamic_pointer_cast<InterfaceType>(interfaceType)) {
        throw Error("TypeError", "Interface not found: " + interfaceName);
    }

    // Register the implementation
    interfaceImplementations[className].insert(interfaceName);
    std::cout << "Debug [registerInterfaceImplementation]: Successfully registered interface implementation" << std::endl;
}

// Get LLVM context
llvm::LLVMContext& TypeRegistry::getContext() {
    return context_;
}

} // namespace pryst
