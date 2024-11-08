#include "type_info.hpp"
#include <sstream>

bool TypeRegistry::debugEnabled = false;

// Helper function to check if a type is numeric
bool TypeInfo::isNumericType(const TypeInfoPtr& type) {
    return type->getName() == "int" || type->getName() == "float";
}

// Helper function to get common numeric type
TypeInfoPtr TypeInfo::getCommonNumericType(const TypeInfoPtr& t1, const TypeInfoPtr& t2) {
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
        // Allow pointer type conversions
        if (other->getKind() == Kind::Pointer) {
            // Allow conversion between pointer types
            return name_ == "pointer" || other->getName() == "pointer";
        }
        return false;
    }

    // Same type is always convertible
    if (name_ == other->getName()) return true;

    // Numeric conversions
    if (TypeInfo::isNumericType(std::make_shared<BasicTypeInfo>(name_)) &&
        TypeInfo::isNumericType(other)) {
        return true;
    }

    // Everything can be converted to string
    if (other->getName() == "str") return true;

    // Allow pointer type conversions
    if (name_ == "pointer" || other->getName() == "pointer") {
        return true;
    }

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
            !TypeInfo::getCommonNumericType(paramTypes_[i], otherParams[i])) {
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
// getInstance() is defined in the header file



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

// Implementation of BasicTypeInfo::toString
std::string BasicTypeInfo::toString() const {
    return name_;  // Basic types just return their name
}

// Implementation of FunctionTypeInfo::toString
std::string FunctionTypeInfo::toString() const {
    std::stringstream ss;
    ss << "fn<" << returnType_->toString() << ">(";
    for (size_t i = 0; i < paramTypes_.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << paramTypes_[i]->toString();
    }
    ss << ")";
    return ss.str();
}

// Implementation of ClassTypeInfo::toString
std::string ClassTypeInfo::toString() const {
    std::string result = name_;
    if (parent_) {
        result += ":" + parent_->getName();
    }
    return result;
}

// Implementation of ArrayTypeInfo::isConvertibleTo
bool ArrayTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    if (other->getKind() != Kind::Array) {
        // Allow conversion to basic type if array has conversion method
        if (other->getKind() == Kind::Basic) {
            // Arrays can be converted to strings
            if (other->getName() == "str") return true;
        }
        return false;
    }

    auto otherArray = std::static_pointer_cast<ArrayTypeInfo>(other);
    if (size != otherArray->getSize()) return false;

    return elementType->isConvertibleTo(otherArray->getElementType());
}

// Implementation of PointerTypeInfo::isConvertibleTo
bool PointerTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    if (other->getKind() != Kind::Pointer) {
        // Allow conversion to basic type if it's a pointer type
        if (other->getKind() == Kind::Basic) {
            // Pointers can be converted to strings
            if (other->getName() == "str") return true;
            // Allow conversion between pointer types
            if (other->getName() == "pointer") return true;
        }
        return false;
    }

    auto otherPtr = std::static_pointer_cast<PointerTypeInfo>(other);
    return pointeeType->isConvertibleTo(otherPtr->getPointeeType());
}

// Implementation of ModuleTypeInfo::isConvertibleTo
bool ModuleTypeInfo::isConvertibleTo(const TypeInfoPtr& other) const {
    // Modules are not convertible to other types except string representation
    if (other->getKind() == Kind::Basic && other->getName() == "str") return true;
    return other->getKind() == Kind::Module && other->getName() == name;
}
