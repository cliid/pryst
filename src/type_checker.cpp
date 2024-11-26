#include "type_checker.hpp"
#include "type_system/core/types.hpp"
#include "type_system/core/type_registry.hpp"
#include "runtime/core/runtime_registry.hpp"

namespace pryst {
namespace core {

// Use LLVM namespace explicitly to avoid conflicts
using llvm::Value;
using llvm::Function;
using llvm::BasicBlock;
using llvm::IRBuilder;
using llvm::Module;
using llvm::LLVMContext;

using namespace antlr4;
using namespace std;

// Import specific types from pryst::types namespace
using pryst::types::Type;
using pryst::types::ArrayType;
using pryst::types::ErrorType;
using pryst::types::FunctionType;

inline any wrapType(shared_ptr<llvm::Type> type) {
    return any(type);
}

bool areTypesCompatible(shared_ptr<Type> t1, shared_ptr<Type> t2) {
    return t1->isAssignableTo(t2);
}

TypeChecker::TypeChecker(llvm::LLVMContext& context, TypeRegistry& typeRegistry,
    RuntimeRegistry& runtimeRegistry, ErrorHandler& errorHandler)
    : context_(context)
    , typeRegistry_(typeRegistry)
    , runtimeRegistry_(runtimeRegistry)
    , errorHandler_(errorHandler)
    , isInLoop(false) {
    initializeGlobalScope();
}

std::shared_ptr<Type> TypeChecker::checkArrayAssignment(
    std::shared_ptr<Type> targetArray,
    std::shared_ptr<Type> sourceArray) {

    if (!targetArray || !sourceArray) {
        return std::make_shared<pryst::types::ErrorType>("Null array reference");
    }

    // Check if both types are array types using dynamic cast
    auto targetArrayType = std::dynamic_pointer_cast<pryst::types::ArrayType>(targetArray);
    auto sourceArrayType = std::dynamic_pointer_cast<pryst::types::ArrayType>(sourceArray);

    if (!targetArrayType || !sourceArrayType) {
        return std::make_shared<pryst::types::ErrorType>(
            "Invalid array assignment: both types must be arrays");
    }

    auto targetElemType = targetArrayType->getElementType();
    auto sourceElemType = sourceArrayType->getElementType();

    if (!areTypesCompatible(sourceElemType, targetElemType)) {
        return std::make_shared<pryst::types::ErrorType>(
            "Incompatible array types: cannot assign " + sourceElemType->toString() +
            " array to " + targetElemType->toString() + " array"
        );
    }

    return targetArray;
}

} // namespace core
} // namespace pryst
