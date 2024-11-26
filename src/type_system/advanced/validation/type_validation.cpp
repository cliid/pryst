#include "type_validation.hpp"
#include <algorithm>

using std::shared_ptr;
using std::vector;
using std::dynamic_pointer_cast;

namespace pryst {
namespace core {

TypeValidation::TypeValidation(shared_ptr<TypeRegistry> registry)
    : typeRegistry_(registry) {}

bool TypeValidation::validateCompatibility(
    shared_ptr<Type> source,
    shared_ptr<Type> target,
    bool allowImplicitConversion) {

    if (!source || !target) {
        return false;
    }

    // Direct type equality
    if (source->equals(target)) {
        return true;
    }

    // Handle union types
    if (auto sourceUnion = dynamic_pointer_cast<type_system::advanced::UnionType>(source)) {
        // Union type is compatible if any of its members is compatible
        return std::any_of(sourceUnion->getTypes().begin(), sourceUnion->getTypes().end(),
            [this, target, allowImplicitConversion](const shared_ptr<Type>& memberType) {
                return validateCompatibility(memberType, target, allowImplicitConversion);
            });
    }

    // Handle intersection types
    if (auto sourceIntersection = dynamic_pointer_cast<type_system::advanced::IntersectionType>(source)) {
        // Intersection type is compatible if all of its members are compatible
        return std::all_of(sourceIntersection->getTypes().begin(), sourceIntersection->getTypes().end(),
            [this, target, allowImplicitConversion](const shared_ptr<Type>& memberType) {
                return validateCompatibility(memberType, target, allowImplicitConversion);
            });
    }

    // Handle nullable types
    if (auto targetNullable = dynamic_pointer_cast<NullableType>(target)) {
        return validateCompatibility(source, targetNullable->getInnerType(), allowImplicitConversion);
    }

    // Handle parameterized types
    if (auto sourceParam = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(source)) {
        if (auto targetParam = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(target)) {
            if (sourceParam->getBaseType() != targetParam->getBaseType()) {
                return false;
            }
            const auto& sourceArgs = sourceParam->getTypeArguments();
            const auto& targetArgs = targetParam->getTypeArguments();
            if (sourceArgs.size() != targetArgs.size()) {
                return false;
            }
            for (size_t i = 0; i < sourceArgs.size(); ++i) {
                if (!validateCompatibility(sourceArgs[i], targetArgs[i], allowImplicitConversion)) {
                    return false;
                }
            }
            return true;
        }
    }

    // Check implicit conversions if allowed
    if (allowImplicitConversion) {
        return isImplicitlyConvertible(source, target);
    }

    return false;
}

bool TypeValidation::validateFunctionCall(
    const shared_ptr<FunctionType>& funcType,
    const vector<shared_ptr<Type>>& argTypes) {

    if (!funcType) {
        return false;
    }

    const auto& paramTypes = funcType->getParameterTypes();

    // Check argument count
    if (argTypes.size() != paramTypes.size()) {
        return false;
    }

    // Check each argument type
    for (size_t i = 0; i < argTypes.size(); ++i) {
        if (!validateCompatibility(argTypes[i], paramTypes[i], true)) {
            return false;
        }
    }

    return true;
}

bool TypeValidation::validateGenericConstraints(
    const shared_ptr<GenericType>& genericType,
    const vector<shared_ptr<Type>>& typeArgs) {

    if (!genericType) {
        return false;
    }

    // Validate number of type arguments
    if (typeArgs.size() != genericType->getTypeParameters().size()) {
        return false;
    }

    // Handle higher-kinded type constraints
    if (auto higherKinded = dynamic_pointer_cast<type_system::advanced::HigherKindedType>(genericType)) {
        // Validate higher-kinded type parameters
        const auto& params = higherKinded->getTypeParameters();
        if (params.size() != typeArgs.size()) {
            return false;
        }
        return true;
    }

    return true;
}

bool TypeValidation::validateUnionType(const shared_ptr<Type>& unionType) {
    auto union_ = dynamic_pointer_cast<type_system::advanced::UnionType>(unionType);
    if (!union_) return false;

    const auto& types = union_->getTypes();
    return !types.empty() && std::all_of(types.begin(), types.end(),
        [this](const shared_ptr<Type>& type) {
            return type != nullptr;
        });
}

bool TypeValidation::validateIntersectionType(const shared_ptr<Type>& intersectionType) {
    auto intersection = dynamic_pointer_cast<type_system::advanced::IntersectionType>(intersectionType);
    if (!intersection) return false;

    const auto& types = intersection->getTypes();
    return !types.empty() && std::all_of(types.begin(), types.end(),
        [this](const shared_ptr<Type>& type) {
            return type != nullptr && validateMethodCompatibility(type, type);
        });
}

bool TypeValidation::validateParameterizedType(const shared_ptr<Type>& paramType) {
    auto param = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(paramType);
    if (!param) return false;

    return typeRegistry_->hasType(param->getName()) &&
           std::all_of(param->getTypeArguments().begin(), param->getTypeArguments().end(),
               [this](const shared_ptr<Type>& arg) {
                   return arg != nullptr && validateTypeParameter(arg);
               });
}

bool TypeValidation::validateTypeParameter(const shared_ptr<Type>& typeParam) {
    if (auto param = dynamic_pointer_cast<TypeParameter>(typeParam)) {
        return !param->hasConstraint() || validateTypeConstraints(param, param->getConstraint());
    }
    return true;
}

bool TypeValidation::validateHigherKindedType(
    const shared_ptr<Type>& higherKindedType,
    const shared_ptr<Type>& appliedType) {

    auto hkt = dynamic_pointer_cast<type_system::advanced::HigherKindedType>(higherKindedType);
    if (!hkt) return false;

    return validateTypeConstraints(appliedType, hkt->getConstraint());
}

bool TypeValidation::validateRecursiveType(const shared_ptr<Type>& recursiveType) {
    if (auto param = dynamic_pointer_cast<type_system::advanced::ParameterizedType>(recursiveType)) {
        return std::all_of(param->getTypeArguments().begin(), param->getTypeArguments().end(),
            [this, &recursiveType](const shared_ptr<Type>& arg) {
                return arg != recursiveType || validateParameterizedType(arg);
            });
    }
    return true;
}

bool TypeValidation::validateTypeConstraints(
    const shared_ptr<Type>& type,
    const shared_ptr<Type>& constraint) {

    return type && constraint && validateCompatibility(type, constraint, false);
}

bool TypeValidation::validateMethodCompatibility(
    const shared_ptr<Type>& type1,
    const shared_ptr<Type>& type2) {

    if (auto interface1 = dynamic_pointer_cast<InterfaceType>(type1)) {
        if (auto interface2 = dynamic_pointer_cast<InterfaceType>(type2)) {
            return !interface1->hasConflictingMethods(interface2);
        }
    }
    return true;
}

bool TypeValidation::isImplicitlyConvertible(
    shared_ptr<Type> source,
    shared_ptr<Type> target) {

    // Handle primitive type conversions
    if (source->isPrimitive() && target->isPrimitive()) {
        auto sourcePrim = dynamic_pointer_cast<PrimitiveType>(source);
        auto targetPrim = dynamic_pointer_cast<PrimitiveType>(target);

        // Allow implicit conversion to larger types
        return sourcePrim->getSize() <= targetPrim->getSize();
    }

    // Handle array type conversions
    if (auto sourceArray = dynamic_pointer_cast<ArrayType>(source)) {
        if (auto targetArray = dynamic_pointer_cast<ArrayType>(target)) {
            return validateCompatibility(
                sourceArray->getElementType(),
                targetArray->getElementType(),
                true
            );
        }
    }

    return false;
}

} // namespace core
} // namespace pryst
