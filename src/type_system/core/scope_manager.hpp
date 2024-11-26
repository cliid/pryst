#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "types.hpp"
#include "type_registry.hpp"
#include "error.hpp"

namespace pryst {

class ScopeManager {
public:
    explicit ScopeManager(TypeRegistry& typeRegistry) : typeRegistry_(typeRegistry) {
        pushScope();  // Create global scope
    }

    void pushScope() {
        scopes_.push_back(Scope());
    }

    void popScope() {
        if (scopes_.size() <= 1) {
            throw Error("ScopeError", "Cannot pop global scope");
        }
        scopes_.pop_back();
    }

    void declareVariable(const std::string& name, std::shared_ptr<Type> type) {
        if (currentScope().variables.find(name) != currentScope().variables.end()) {
            throw Error("ScopeError", "Variable already declared in current scope: " + name);
        }
        currentScope().variables[name] = type;
    }

    std::shared_ptr<Type> getVariableType(const std::string& name) {
        for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
            auto found = it->variables.find(name);
            if (found != it->variables.end()) {
                return found->second;
            }
        }
        throw Error("ScopeError", "Undefined variable: " + name);
    }

    const std::unordered_map<std::string, std::shared_ptr<Type>>& getCurrentScope() const {
        if (scopes_.empty()) {
            throw Error("ScopeError", "No active scope");
        }
        return scopes_.back().variables;
    }

    // Narrow type for a variable in current scope
    void narrowType(const std::string& name, std::shared_ptr<Type> newType) {
        if (currentScope().variables.find(name) == currentScope().variables.end()) {
            throw Error("ScopeError", "Cannot narrow type of undefined variable: " + name);
        }

        auto currentType = currentScope().variables[name];

        // Handle error type narrowing
        if (typeRegistry_.isErrorType(currentType->toString()) &&
            typeRegistry_.isErrorType(newType->toString())) {
            if (!typeRegistry_.isSubclassOf(newType->toString(), currentType->toString())) {
                throw Error("TypeError", "Invalid type narrowing for error type");
            }
        }
        // Handle nullable type narrowing
        else if (currentType->getKind() == Type::Kind::Nullable) {
            auto nullableType = std::static_pointer_cast<NullableType>(currentType);
            if (!typeRegistry_.isAssignable(nullableType->getInnerType(), newType)) {
                throw Error("TypeError", "Invalid type narrowing for nullable type");
            }
        }
        else if (!typeRegistry_.isAssignable(currentType, newType)) {
            throw Error("TypeError", "Invalid type narrowing");
        }

        currentScope().variables[name] = newType;
    }

private:
    struct Scope {
        std::unordered_map<std::string, std::shared_ptr<Type>> variables;
    };

    std::vector<Scope> scopes_;
    TypeRegistry& typeRegistry_;

    Scope& currentScope() {
        if (scopes_.empty()) {
            throw Error("ScopeError", "No active scope");
        }
        return scopes_.back();
    }
};  // End of ScopeManager class
} // namespace pryst
