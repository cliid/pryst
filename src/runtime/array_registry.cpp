#include "runtime_registry.hpp"
#include "array_impl.hpp"
#include "llvm/IR/DerivedTypes.h"

namespace pryst {
namespace core {

void registerArrayClass(RuntimeRegistry& registry, llvm::Module* module) {
    // Get Array struct type from module
    auto arrayStructTy = module->getTypeByName("struct.pryst.core.Array");
    if (!arrayStructTy) {
        throw std::runtime_error("Array struct type not found in module");
    }

    // Register Array class
    registry.registerClass("Array", "pryst::core::Array", arrayStructTy);

    // Register constructor
    registry.registerClassMethod("Array", {
        "Array",  // Using class name as constructor name
        (void*)pryst_core_Array_new,
        {"str"},  // elementType
        "Array"
    });

    // Register length method
    registry.registerClassMethod("Array", {
        "length",
        (void*)pryst_core_Array_length,
        {},  // no parameters
        "int"
    });

    // Register push method
    registry.registerClassMethod("Array", {
        "push",
        (void*)pryst_core_Array_push,
        {"any"},  // element
        "void"
    });

    // Register pop method
    registry.registerClassMethod("Array", {
        "pop",
        (void*)pryst_core_Array_pop,
        {},  // no parameters
        "any"
    });

    // Register shift method
    registry.registerClassMethod("Array", {
        "shift",
        (void*)pryst_core_Array_shift,
        {},  // no parameters
        "any"
    });

    // Register unshift method
    registry.registerClassMethod("Array", {
        "unshift",
        (void*)pryst_core_Array_unshift,
        {"any"},  // element
        "void"
    });

    // Register indexOf method
    registry.registerClassMethod("Array", {
        "indexOf",
        (void*)pryst_core_Array_indexOf,
        {"any"},  // element
        "int"
    });

    // Register slice method
    registry.registerClassMethod("Array", {
        "slice",
        (void*)pryst_core_Array_slice,
        {"int", "int"},  // start, end
        "Array"
    });

    // Register join method
    registry.registerClassMethod("Array", {
        "join",
        (void*)pryst_core_Array_join,
        {"str"},  // delimiter
        "str"
    });

    // Register destructor
    registry.registerClassMethod("Array", {
        "delete",
        (void*)pryst_core_Array_delete,
        {},  // no parameters
        "void"
    });
}

} // namespace core
} // namespace pryst
