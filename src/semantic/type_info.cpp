#include "type_info.hpp"
#include <sstream>

namespace pryst {

// Helper function to check if a type is numeric
bool isNumericType(const TypeInfoPtr& type) {
    return type->getName() == "int" || type->getName() == "float";
}

// Helper function to get common numeric type
TypeInfoPtr getCommonNumericType(const TypeInfoPtr& t1, const TypeInfoPtr& t2) {
    if (!isNumericType(t1) || !isNumericType(t2)) return nullptr;

    // If either type is float, result is float
    if (t1->getName() == "float" || t2->getName() == "float") {
        return TypeRegistry::getInstance().getFloatType();
    }

    // Otherwise both are int
    return TypeRegistry::getInstance().getIntType();
}

// Implementation of type conversion rules
bool BasicTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    if (other->getKind() != Kind::Basic) {
        // Allow conversion to class type if class has c! conversion method
        if (other->getKind() == Kind::Class) {
            auto classType = std::static_pointer_cast<ClassTypeInfo>(other);
            std::string convMethodName = "c!" + classType->getName();
            return classType->hasMethod(convMethodName);
        }
        return false;
    }

    // Same type is always convertible
    if (name_ == other->getName()) return true;

    // Numeric conversions
    if (isNumericType(std::make_shared<BasicTypeInfo>(name_)) &&
        isNumericType(other)) {
        return true;
    }

    // Everything can be converted to string
    if (other->getName() == "str") return true;

    return false;
}

// Implementation of function type conversion rules
bool FunctionTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    if (other->getKind() != Kind::Function) return false;

    auto otherFn = std::static_pointer_cast<FunctionTypeInfo>(other);

    // Check return type compatibility
    if (!returnType_->isConvertibleTo(otherFn->getReturnType())) return false;

    // Check parameter types compatibility
    const auto& otherParams = otherFn->getParamTypes();
    if (paramTypes_.size() != otherParams.size()) return false;

    for (size_t i = 0; i < paramTypes_.size(); ++i) {
        // Parameter types must be exactly the same or have compatible numeric types
        if (!paramTypes_[i]->isConvertibleTo(otherParams[i]) &&
            !getCommonNumericType(paramTypes_[i], otherParams[i])) {
            return false;
        }
    }

    return true;
}

// Implementation of class type conversion rules
bool ClassTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    if (other->getKind() != Kind::Class) {
        // Allow conversion to basic type if class has conversion method
        if (other->getKind() == Kind::Basic) {
            std::string convMethodName = other->getName();
            return hasMethod(convMethodName);
        }
        return false;
    }

    auto otherClass = std::static_pointer_cast<ClassTypeInfo>(other);

    // Check inheritance chain
    const ClassTypeInfo* current = this;
    while (current) {
        if (current->getName() == otherClass->getName()) return true;
        current = current->getParent().get();
    }

    // Check if we have a conversion method to the target class
    std::string convMethodName = "c!" + otherClass->getName();
    return hasMethod(convMethodName);
}

// Implementation of type registry methods
TypeRegistry& TypeRegistry::getInstance() {
    static TypeRegistry instance;
    return instance;
}

TypeInfoPtr TypeRegistry::getOrCreateBasicType(const std::string& name) {
    auto it = types_.find(name);
    if (it != types_.end()) return it->second;

    auto type = std::make_shared<BasicTypeInfo>(name);
    types_[name] = type;
    return type;
}

TypeInfoPtr TypeRegistry::registerType(TypeInfoPtr type) {
    types_[type->toString()] = type;
    return type;
}

TypeInfoPtr TypeRegistry::getFunctionType(TypeInfoPtr returnType,
                                        const std::vector<TypeInfoPtr>& paramTypes) {
    std::stringstream ss;
    ss << "fn<" << returnType->toString() << ">(";
    for (size_t i = 0; i < paramTypes.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << paramTypes[i]->toString();
    }
    ss << ")";

    std::string typeStr = ss.str();
    auto it = types_.find(typeStr);
    if (it != types_.end()) return it->second;

    auto type = std::make_shared<FunctionTypeInfo>(returnType, paramTypes);
    types_[typeStr] = type;
    return type;
}


ClassTypeInfoPtr TypeRegistry::createClassType(const std::string& name,
                                             ClassTypeInfoPtr parent) {
    auto it = types_.find(name);
    if (it != types_.end()) {
        if (auto classType = std::dynamic_pointer_cast<ClassTypeInfo>(it->second)) {
            return classType;
        }
    }

    auto classType = std::make_shared<ClassTypeInfo>(name, parent);
    types_[name] = classType;
    return classType;
}

} // namespace pryst
