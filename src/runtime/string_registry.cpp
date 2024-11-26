#include "runtime_registry.hpp"
#include "string_impl.hpp"
#include "llvm/IR/DerivedTypes.h"

namespace pryst {
namespace core {

void registerStringClass(RuntimeRegistry& registry, llvm::Module* module) {
    // Get String struct type from module
    auto stringStructTy = module->getTypeByName("struct.pryst.core.String");
    if (!stringStructTy) {
        throw std::runtime_error("String struct type not found in module");
    }

    // Register String class
    registry.registerClass("String", "pryst::core::String", stringStructTy);

    // Register constructor
    registry.registerClassMethod("String", {
        "String",  // Using class name as constructor name
        (void*)pryst_core_String_new,
        {"str"},  // value
        "String"
    });

    // Register length method
    registry.registerClassMethod("String", {
        "length",
        (void*)pryst_core_String_length,
        {},  // no parameters
        "int"
    });

    // Register substring method
    registry.registerClassMethod("String", {
        "substring",
        (void*)pryst_core_String_substring,
        {"int", "int"},  // start, length
        "String"
    });

    // Register indexOf method
    registry.registerClassMethod("String", {
        "indexOf",
        (void*)pryst_core_String_indexOf,
        {"str"},  // search string
        "int"
    });

    // Register lastIndexOf method
    registry.registerClassMethod("String", {
        "lastIndexOf",
        (void*)pryst_core_String_lastIndexOf,
        {"str"},  // search string
        "int"
    });

    // Register replace method
    registry.registerClassMethod("String", {
        "replace",
        (void*)pryst_core_String_replace,
        {"str", "str"},  // from, to
        "String"
    });

    // Register split method
    registry.registerClassMethod("String", {
        "split",
        (void*)pryst_core_String_split,
        {"str"},  // delimiter
        "str[]"  // returns array of strings
    });

    // Register trim method
    registry.registerClassMethod("String", {
        "trim",
        (void*)pryst_core_String_trim,
        {},  // no parameters
        "String"
    });

    // Register toString method
    registry.registerClassMethod("String", {
        "toString",
        (void*)pryst_core_String_toString,
        {},  // no parameters
        "str"
    });

    // Register destructor
    registry.registerClassMethod("String", {
        "delete",
        (void*)pryst_core_String_delete,
        {},  // no parameters
        "void"
    });
}

} // namespace core
} // namespace pryst
