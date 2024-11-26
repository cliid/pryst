#include "types.hpp"

namespace pryst {
namespace core {

// Type definitions
std::shared_ptr<pryst::core::Type> INT_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Int);
std::shared_ptr<pryst::core::Type> FLOAT_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Float);
std::shared_ptr<pryst::core::Type> BOOL_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Bool);
std::shared_ptr<pryst::core::Type> STRING_TYPE = std::make_shared<PrimitiveType>(Type::Kind::String);
std::shared_ptr<pryst::core::Type> VOID_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Void);
std::shared_ptr<pryst::core::Type> ERROR_TYPE = std::make_shared<ErrorType>("Unknown error");
std::shared_ptr<pryst::core::Type> NULL_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Null);
std::shared_ptr<pryst::core::Type> ANY_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Any);

bool UnionType::satisfiesConstraint(const std::shared_ptr<Type>& type) const {
    // Handle error type propagation
    if (type->isError()) {
        return true;  // Allow error types to satisfy any constraint to prevent error cascading
    }

    // Check if type satisfies any of the union constraints
    bool satisfiesAny = std::any_of(types_.begin(), types_.end(),
        [&type](const std::shared_ptr<Type>& constraint) -> bool {
            if (constraint->isError()) {
                return false;  // Error constraints always fail
            }
            return type->isInstanceOf(constraint);
        });

    if (!satisfiesAny) {
        // Create detailed error message for type mismatch
        std::string validTypes;
        for (size_t i = 0; i < types_.size(); ++i) {
            if (i > 0) validTypes += " | ";
            validTypes += types_[i]->toString();
        }
        ERROR_TYPE = std::make_shared<ErrorType>(
            "Type '" + type->toString() + "' does not satisfy any of the union constraints: " + validTypes);
        return false;
    }
    return true;
}

bool IntersectionType::satisfiesConstraint(const std::shared_ptr<Type>& type) const {
    // Handle error type propagation
    if (type->isError()) {
        return true;  // Allow error types to satisfy any constraint to prevent error cascading
    }

    // Check if type satisfies all intersection constraints
    for (const auto& constraint : types_) {
        if (constraint->isError()) {
            continue;  // Skip error constraints
        }
        if (!type->isInstanceOf(constraint)) {
            // Create detailed error message for type mismatch
            ERROR_TYPE = std::make_shared<ErrorType>(
                "Type '" + type->toString() + "' does not satisfy intersection constraint '" +
                constraint->toString() + "'");
            return false;
        }
    }
    return true;
}

} // namespace core
} // namespace pryst
