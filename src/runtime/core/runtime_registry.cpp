#include "runtime_registry.hpp"
#include "../type_registry.hpp"
#include "io.hpp"
#include "web.hpp"
#include "web_types.hpp"
#include "web_impl.hpp"
#include "io_impl.hpp"
#include "map_impl.hpp"
#include "string_impl.hpp"
#include "array_impl.hpp"
#include "../error.hpp"
#include "runtime_type_ops.hpp"
#include <iostream>

namespace pryst {
namespace runtime {

RuntimeRegistry* RuntimeRegistry::instance = nullptr;

RuntimeRegistry::RuntimeRegistry(::llvm::Module* mod)
    : module(mod), typeRegistry(nullptr) {
}

void RuntimeRegistry::setTypeRegistry(TypeRegistry* registry) {
    typeRegistry = registry;
}

void RuntimeRegistry::registerFunction(const std::string& name, void* func) {
    functions[name] = func;
}

void* RuntimeRegistry::getFunction(const std::string& name) {
    auto it = functions.find(name);
    return it != functions.end() ? it->second : nullptr;
}

void RuntimeRegistry::registerType(const std::string& name, const std::string& fullName) {
    ClassType classType;
    classType.name = name;
    classType.fullName = fullName;
    classType.llvmType = nullptr;
    classes[name] = classType;
    if (name != fullName) {
        classes[fullName] = classType;
    }
}



bool RuntimeRegistry::isSubclassOf(const char* derivedType, const char* baseType) const {
    if (!derivedType || !baseType) return false;
    // Handle nullable type inheritance
    std::string derivedStr(derivedType);
    std::string baseStr(baseType);
    bool derivedNullable = derivedStr.back() == '?';
    bool baseNullable = baseStr.back() == '?';
    if (!derivedNullable && baseNullable) return false;
    if (derivedNullable) derivedStr.pop_back();
    if (baseNullable) baseStr.pop_back();

    auto derived = classes.find(derivedStr);
    auto base = classes.find(baseStr);

    if (derived == classes.end() || base == classes.end()) return false;

    const ClassType* current = &derived->second;
    while (current) {
        if (current->fullName == baseStr) return true;

        // Check implemented interfaces
        for (const auto* interface : current->implementedInterfaces) {
            if (interface->fullName == baseStr) return true;
        }

        current = current->baseClass;
    }
    return false;
}

void RuntimeRegistry::registerClass(const std::string& name, const std::string& fullName, ::llvm::StructType* type, bool isInterface) {
    ClassType classType(name, fullName);
    classType.llvmType = type;
    classType.isInterface = isInterface;
    classes[name] = classType;
    classes[fullName] = classType;
    std::cout << "Debug [registerClass]: Registered class " << fullName << std::endl;
}

void RuntimeRegistry::registerClassMethod(const std::string& className, const ClassMethod& method) {
    auto it = classes.find(className);
    if (it != classes.end()) {
        it->second.methods.push_back(method);
    }
}

void RuntimeRegistry::setBaseClass(const std::string& derivedClass, const std::string& baseClass) {
    auto derived = classes.find(derivedClass);
    auto base = classes.find(baseClass);
    if (derived != classes.end() && base != classes.end()) {
        derived->second.baseClass = &base->second;

        // Handle nullable inheritance
        std::string nullableDerived = derivedClass + "?";
        std::string nullableBase = baseClass + "?";
        auto nullableDerivedIt = classes.find(nullableDerived);
        auto nullableBaseIt = classes.find(nullableBase);
        if (nullableDerivedIt != classes.end() && nullableBaseIt != classes.end()) {
            nullableDerivedIt->second.baseClass = &nullableBaseIt->second;
        }
    }
}

const char* RuntimeRegistry::getObjectType(void* obj) const {
    if (!obj) return "null";

    // The first field of our objects is always the type identifier string
    const char* typeId = *reinterpret_cast<const char**>(obj);
    if (!typeId) return "Object";

    // Handle nullable types by returning the base type
    std::string typeStr(typeId);
    size_t nullablePos = typeStr.find('?');
    if (nullablePos != std::string::npos) {
        typeStr = typeStr.substr(0, nullablePos);
    }

    auto it = classes.find(typeStr);
    return it != classes.end() ? it->second.fullName.c_str() : "Object";
}

bool RuntimeRegistry::isNullable(void* obj) const {
    // Null objects are considered nullable
    if (!obj) return true;

    // Get type identifier from object
    const char* typeId = *reinterpret_cast<const char**>(obj);
    if (!typeId) return false;

    // Check explicit nullable registration first
    auto it = nullableTypes.find(typeId);
    if (it != nullableTypes.end()) {
        return it->second;
    }

    // Check for nullable chain (type ending with ?)
    std::string typeStr(typeId);
    return typeStr.find('?') != std::string::npos;
}

const ClassType* RuntimeRegistry::getClass(const std::string& name) const {
    // Try exact match first
    auto it = classes.find(name);
    if (it != classes.end()) {
        return &it->second;
    }

    // If not found and name contains ::, try short name
    size_t lastSeparator = name.rfind("::");
    if (lastSeparator != std::string::npos) {
        std::string shortName = name.substr(lastSeparator + 2);
        it = classes.find(shortName);
        if (it != classes.end()) {
            return &it->second;
        }
    }

    return nullptr;
}

bool RuntimeRegistry::hasClass(const std::string& name) const {
    return getClass(name) != nullptr;
}

void RuntimeRegistry::registerBuiltins() {
    if (!typeRegistry) {
        std::cerr << "Error: TypeRegistry is not set." << std::endl;
        return;
    }

    // Register core namespaces first
    typeRegistry->registerNamespace("pryst");
    typeRegistry->registerNamespace("pryst::runtime");
    typeRegistry->registerNamespace("pryst::runtime::web");

    // Register type operators
    registerFunction("instanceof", (void*)pryst_runtime_instanceof);
    registerFunction("typeof", (void*)pryst_runtime_typeof);

    // Remove web types registration from here since it's called in Compiler constructor
    std::cout << "Debug [registerBuiltins]: Registering core types" << std::endl;

    auto& context = module->getContext();

    // Register File class and its methods
    std::vector<::llvm::Type*> fileFields;
    fileFields.push_back(::llvm::Type::getInt8PtrTy(context));  // path
    fileFields.push_back(::llvm::Type::getInt8PtrTy(context));  // file handle
    auto fileStructTy = ::llvm::StructType::create(context, fileFields, "struct.pryst.io.File");

    registerClass("File", "pryst::io::File", fileStructTy);

    // Register File methods
    registerClassMethod("File", ClassMethod(
        "new",
        (void*)pryst_io_File_new,
        {"str", "str"},
        "File"
    ));

    registerClassMethod("File", ClassMethod(
        "readString",
        (void*)pryst_io_File_readString,
        {},
        "str?"
    ));

    registerClassMethod("File", ClassMethod(
        "writeString",
        (void*)pryst_io_File_writeString,
        {"str"},
        "bool"
    ));

    registerClassMethod("File", ClassMethod(
        "close",
        (void*)pryst_io_File_close,
        {},
        "void"
    ));

    // Register IO class and its static methods
    std::vector<::llvm::Type*> ioFields;  // Empty as all methods are static
    auto ioStructTy = ::llvm::StructType::create(context, ioFields, "struct.pryst.io.IO");

    registerClass("IO", "pryst::io::IO", ioStructTy);

    // Register IO static methods
    registerClassMethod("IO", ClassMethod(
        "print",
        (void*)pryst_io_print_impl,
        {"str"},
        "void"
    ));

    registerClassMethod("IO", ClassMethod(
        "println",
        (void*)pryst_io_println_impl,
        {"str"},
        "void"
    ));

    registerClassMethod("IO", ClassMethod(
        "readLine",
        (void*)pryst_io_readLine_impl,
        {},
        "str"
    ));

    registerClassMethod("IO", ClassMethod(
        "getChar",
        (void*)pryst_io_getChar_impl,
        {},
        "char"
    ));

    // Register Map class and its methods
    std::vector<::llvm::Type*> mapFields;
    mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // keyType
    mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // valueType
    mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // internal map pointer
    auto mapStructTy = ::llvm::StructType::create(context, mapFields, "struct.pryst.core.Map");

    registerClass("Map", "pryst::core::Map", mapStructTy);

    // Register Map methods
    registerClassMethod("Map", ClassMethod(
        "new",
        (void*)pryst_core_Map_new,
        {"str", "str"},
        "Map"
    ));

    registerClassMethod("Map", ClassMethod(
        "get",
        (void*)pryst_core_Map_get,
        {"str"},
        "any"
    ));

    registerClassMethod("Map", ClassMethod(
        "set",
        (void*)pryst_core_Map_set,
        {"str", "any"},
        "void"
    ));

    registerClassMethod("Map", ClassMethod(
        "has",
        (void*)pryst_core_Map_has,
        {"str"},
        "bool"
    ));

    registerClassMethod("Map", ClassMethod(
        "delete",
        (void*)pryst_core_Map_delete,
        {"str"},
        "void"
    ));

    registerClassMethod("Map", ClassMethod(
        "clear",
        (void*)pryst_core_Map_clear,
        {},
        "void"
    ));

    registerClassMethod("Map", ClassMethod(
        "keys",
        (void*)pryst_core_Map_keys,
        {},
        "str[]"
    ));

    registerClassMethod("Map", ClassMethod(
        "values",
        (void*)pryst_core_Map_values,
        {},
        "any[]"
    ));

    registerClassMethod("Map", ClassMethod(
        "size",
        (void*)pryst_core_Map_size,
        {},
        "int"
    ));
}

void RuntimeRegistry::registerWebTypes() {
    if (!typeRegistry) {
        std::cerr << "Error: TypeRegistry is not set." << std::endl;
        return;
    }

    auto& context = module->getContext();

    // Register Request class
    std::vector<::llvm::Type*> requestFields;
    requestFields.push_back(::llvm::Type::getInt8PtrTy(context));  // method
    requestFields.push_back(::llvm::Type::getInt8PtrTy(context));  // path
    // Use the proper map struct type for headers
    auto mapStructTy = ::llvm::StructType::getTypeByName(context, "struct.pryst.core.Map");
    if (!mapStructTy) {
        std::vector<::llvm::Type*> mapFields;
        mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // keyType
        mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // valueType
        mapFields.push_back(::llvm::Type::getInt8PtrTy(context));  // internal map pointer
        mapStructTy = ::llvm::StructType::create(context, mapFields, "struct.pryst.core.Map");
    }
    requestFields.push_back(mapStructTy);  // headers (map)
    auto requestStructTy = ::llvm::StructType::create(context, requestFields, "struct.pryst.runtime.web.Request");

    registerClass("Request", "pryst::runtime::web::Request", requestStructTy);

    // Register Request methods
    registerClassMethod("Request", ClassMethod(
        "new",
        (void*)pryst_web_Request_new,
        {"str", "str"},
        "Request"
    ));

    // Register Response class
    std::vector<::llvm::Type*> responseFields;
    responseFields.push_back(::llvm::Type::getInt32Ty(context));   // status
    responseFields.push_back(::llvm::Type::getInt8PtrTy(context)); // body
    responseFields.push_back(mapStructTy); // headers (map)
    auto responseStructTy = ::llvm::StructType::create(context, responseFields, "struct.pryst.runtime.web.Response");

    registerClass("Response", "pryst::runtime::web::Response", responseStructTy);

    // Register Response methods
    registerClassMethod("Response", ClassMethod(
        "new",
        (void*)pryst_web_Response_new,
        {"int", "str"},
        "Response"
    ));

    // Register WebServer class
    std::vector<::llvm::Type*> serverFields;
    serverFields.push_back(::llvm::Type::getInt8PtrTy(context));  // host
    serverFields.push_back(::llvm::Type::getInt32Ty(context));    // port
    auto serverStructTy = ::llvm::StructType::create(context, serverFields, "struct.pryst.runtime.web.WebServer");

    registerClass("WebServer", "pryst::web::WebServer", serverStructTy);

    // Register WebServer methods
    registerClassMethod("WebServer", ClassMethod(
        "new",
        (void*)pryst_web_WebServer_new,
        {"str", "int"},
        "WebServer"
    ));

    registerClassMethod("WebServer", ClassMethod(
        "start",
        (void*)pryst_web_WebServer_start,
        {},
        "void"
    ));
}

std::string RuntimeRegistry::getTypeKind(const std::string& typeName) const {
    if (isPrimitive(typeName)) return "primitive";
    if (isArray(typeName)) return "array";
    if (isInterface(typeName)) return "interface";
    return "class";
}

bool RuntimeRegistry::isArray(const std::string& typeName) const {
    return typeName.find("Array<") != std::string::npos;
}

bool RuntimeRegistry::isPrimitive(const std::string& typeName) const {
    return typeName == "int" || typeName == "float" || typeName == "bool" || typeName == "string";
}

bool RuntimeRegistry::isInterface(const std::string& typeName) const {
    auto it = classes.find(typeName);
    return it != classes.end() && it->second.isInterface;
}

bool RuntimeRegistry::implementsInterface(const std::string& typeName, const std::string& interfaceName) const {
    auto typeIt = classes.find(typeName);
    if (typeIt == classes.end()) return false;

    const ClassType* current = &typeIt->second;
    while (current) {
        for (const auto* interface : current->implementedInterfaces) {
            if (interface->fullName == interfaceName) return true;
        }
        current = current->baseClass;
    }
    return false;
}

void RuntimeRegistry::implementInterface(const std::string& className, const std::string& interfaceName) {
    auto classIt = classes.find(className);
    auto interfaceIt = classes.find(interfaceName);

    if (classIt != classes.end() && interfaceIt != classes.end() && interfaceIt->second.isInterface) {
        classIt->second.implementedInterfaces.push_back(&interfaceIt->second);
        std::cout << "Debug [implementInterface]: " << className << " now implements " << interfaceName << std::endl;
    }
}

void RuntimeRegistry::registerNullableType(const std::string& typeName) {
    std::cout << "Debug [registerNullableType]: Registering nullable type for " << typeName << std::endl;

    nullableTypes[typeName] = true;
    std::string nullableTypeName = typeName + "?";
    nullableTypes[nullableTypeName] = true;

    auto it = classes.find(typeName);
    if (it != classes.end()) {
        ClassType nullableClass = it->second;
        nullableClass.name += "?";
        nullableClass.fullName += "?";

        // Preserve inheritance relationship for nullable types
        if (nullableClass.baseClass) {
            std::string nullableBaseName = nullableClass.baseClass->fullName + "?";
            auto baseIt = classes.find(nullableBaseName);
            if (baseIt != classes.end()) {
                nullableClass.baseClass = &baseIt->second;
            }
        }

        // Copy implemented interfaces for nullable version
        nullableClass.implementedInterfaces = it->second.implementedInterfaces;

        classes[nullableClass.name] = nullableClass;
        classes[nullableClass.fullName] = nullableClass;
        std::cout << "Debug [registerNullableType]: Registered nullable class "
                  << nullableClass.fullName << std::endl;
    }
}

} // namespace runtime
} // namespace pryst
