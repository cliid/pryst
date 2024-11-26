#include "advanced_types.hpp"
#include <stdexcept>

namespace pryst {
namespace type_system {
namespace advanced {

bool UnionType::isAssignableTo(const std::shared_ptr<Type>& other) const {
    // A union type is assignable to another type if any of its member types is assignable to that type
    for (const auto& type : types_) {
        if (type->isAssignableTo(other)) {
            return true;
        }
    }
    return false;
}

bool IntersectionType::isAssignableTo(const std::shared_ptr<Type>& other) const {
    // An intersection type is assignable to another type if all of its member types are assignable to that type
    for (const auto& type : types_) {
        if (!type->isAssignableTo(other)) {
            return false;
        }
    }
    return true;
}

bool HigherKindedType::isAssignableTo(const std::shared_ptr<Type>& other) const {
    if (auto otherHigherKinded = std::dynamic_pointer_cast<HigherKindedType>(other)) {
        // Check if base types match and type parameters are compatible
        return name_ == otherHigherKinded->getName() &&
               typeParameters_.size() == otherHigherKinded->getTypeParameters().size();
    }
    return false;
}

bool ParameterizedType::isAssignableTo(const std::shared_ptr<Type>& other) const {
    if (auto otherParam = std::dynamic_pointer_cast<ParameterizedType>(other)) {
        // Check if base types match
        if (baseType_ != otherParam->getBaseType()) {
            return false;
        }

        // Check if type arguments are compatible
        const auto& otherArgs = otherParam->getTypeArguments();
        if (typeArguments_.size() != otherArgs.size()) {
            return false;
        }

        for (size_t i = 0; i < typeArguments_.size(); ++i) {
            if (!typeArguments_[i]->isAssignableTo(otherArgs[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

} // namespace advanced
} // namespace type_system
} // namespace pryst
