#include "runtime_registry.hpp"
#include "error_impl.hpp"
#include "llvm/IR/DerivedTypes.h"

namespace pryst {
namespace core {

void registerErrorClass(RuntimeRegistry& registry, llvm::Module* module) {
    // Get Error struct type from module
    auto errorStructTy = module->getTypeByName("struct.pryst.core.Error");
    if (!errorStructTy) {
        throw std::runtime_error("Error struct type not found in module");
    }

    // Register Error class
    registry.registerClass("Error", "pryst::core::Error", errorStructTy);

    // Register constructor
    registry.registerClassMethod("Error", {
        "Error",  // Using class name as constructor name
        (void*)pryst_core_Error_new,
        {"str", "int"},  // message, code (with default)
        "Error"
    });

    // Register getMessage method
    registry.registerClassMethod("Error", {
        "getMessage",
        (void*)pryst_core_Error_getMessage,
        {},  // no parameters
        "str"
    });

    // Register getCode method
    registry.registerClassMethod("Error", {
        "getCode",
        (void*)pryst_core_Error_getCode,
        {},  // no parameters
        "int"
    });

    // Register toString method
    registry.registerClassMethod("Error", {
        "toString",
        (void*)pryst_core_Error_toString,
        {},  // no parameters
        "str"
    });

    // Register destructor
    registry.registerClassMethod("Error", {
        "delete",
        (void*)pryst_core_Error_delete,
        {},  // no parameters
        "void"
    });
}

} // namespace core
} // namespace pryst
