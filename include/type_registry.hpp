#pragma once

#include "type.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace pryst {

class TypeRegistry {
public:
    TypeRegistry() = default;

    bool isErrorType(const std::string& typeName) const {
        auto it = types_.find(typeName);
        return it != types_.end() && it->second->isError();
    }

    void registerType(const std::string& name, std::shared_ptr<Type> type) {
        types_[name] = type;
    }

    void registerArrayType(std::shared_ptr<Type> elementType) {
        std::string arrayTypeName = elementType->toString() + "[]";
        types_[arrayTypeName] = std::make_shared<ArrayType>(elementType);
    }

    std::shared_ptr<Type> getType(const std::string& name) const {
        auto it = types_.find(name);
        if (it == types_.end()) {
            throw Error("TypeError", "Unknown type: " + name);
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Type>> types_;
};

} // namespace pryst
