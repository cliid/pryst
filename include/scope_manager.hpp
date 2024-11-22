#pragma once

#include "type.hpp"
#include "type_registry.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <sstream>

namespace pryst {

class ScopeManager {
public:
    explicit ScopeManager(std::shared_ptr<TypeRegistry> registry) : typeRegistry_(registry) {
        // Initialize with global scope
        scopes_.push_back(Scope());
    }

    struct VisibilityChange {
        std::string name;
        std::string originalVisibility;
        std::string newVisibility;
        int originalLevel;
        int newLevel;
    };

    struct ErrorHandlingChange {
        std::string name;
        std::string originalErrorType;
        std::string newErrorType;
        int level;
    };

    struct NullabilityChange {
        std::string name;
        bool wasNullable;
        bool isNullable;
        int level;
    };

    void pushScope() {
        std::cout << "Debug [ScopeManager::pushScope]: Creating new scope" << std::endl;
        scopes_.push_back(Scope());
    }

    void popScope() {
        std::cout << "Debug [ScopeManager::popScope]: Attempting to pop scope" << std::endl;
        if (scopes_.size() <= 1) {
            throw Error("ScopeError", "Cannot pop global scope");
        }
        scopes_.pop_back();
    }

    void declareVariable(const std::string& name, std::shared_ptr<Type> type) {
        std::cout << "Debug [ScopeManager::declareVariable]: Declaring " << name << " with type " << type->toString() << std::endl;
        auto& scope = currentScope();
        if (scope.variables.find(name) != scope.variables.end()) {
            throw Error("ScopeError", "Variable '" + name + "' already declared in current scope");
        }
        scope.variables[name] = type;
    }

    std::shared_ptr<Type> lookupVariable(const std::string& name) const {
        std::cout << "Debug [ScopeManager::lookupVariable]: Looking up " << name << std::endl;
        for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
            auto varIt = it->variables.find(name);
            if (varIt != it->variables.end()) {
                return varIt->second;
            }
        }
        throw Error("ScopeError", "Variable not found: " + name);
    }

    std::vector<std::pair<std::string, std::shared_ptr<Type>>> getVariablesAtLevelOrdered(size_t level) const {
        std::cout << "Debug [ScopeManager::getVariablesAtLevelOrdered]: Getting variables at level " << level << std::endl;
        if (level >= scopes_.size()) {
            return {};
        }
        std::vector<std::pair<std::string, std::shared_ptr<Type>>> vars;
        for (const auto& [name, type] : scopes_[level].variables) {
            vars.emplace_back(name, type);
        }
        return vars;
    }

    std::vector<VisibilityChange> getVisibilityChanges() const {
        std::cout << "Debug [ScopeManager::getVisibilityChanges]: Analyzing visibility changes" << std::endl;
        std::vector<VisibilityChange> changes;
        std::unordered_map<std::string, std::pair<std::string, int>> firstVisibility;

        for (size_t i = 0; i < scopes_.size(); ++i) {
            for (const auto& [name, type] : scopes_[i].variables) {
                if (firstVisibility.find(name) != firstVisibility.end()) {
                    VisibilityChange change;
                    change.name = name;
                    change.originalLevel = firstVisibility[name].second;
                    change.newLevel = i;
                    change.originalVisibility = firstVisibility[name].first;
                    change.newVisibility = type->toString();
                    changes.push_back(change);
                } else {
                    firstVisibility[name] = {type->toString(), static_cast<int>(i)};
                }
            }
        }
        return changes;
    }

    std::vector<ErrorHandlingChange> getErrorHandlingChanges() const {
        std::cout << "Debug [ScopeManager::getErrorHandlingChanges]: Analyzing error handling changes" << std::endl;
        std::vector<ErrorHandlingChange> changes;

        for (size_t i = 0; i < scopes_.size(); ++i) {
            for (const auto& [name, type] : scopes_[i].variables) {
                if (typeRegistry_->isErrorType(type->toString())) {
                    ErrorHandlingChange change;
                    change.name = name;
                    change.newErrorType = type->toString();
                    change.level = i;
                    changes.push_back(change);
                }
            }
        }
        return changes;
    }

    std::vector<NullabilityChange> getNullabilityChanges() const {
        std::cout << "Debug [ScopeManager::getNullabilityChanges]: Analyzing nullability changes" << std::endl;
        std::vector<NullabilityChange> changes;

        for (size_t i = 0; i < scopes_.size(); ++i) {
            for (const auto& [name, type] : scopes_[i].variables) {
                if (type->isNullable()) {
                    NullabilityChange change;
                    change.name = name;
                    change.wasNullable = false;
                    change.isNullable = true;
                    change.level = i;
                    changes.push_back(std::move(change));
                }
            }
        }
        return changes;
    }

    std::string generateScopeReport() const {
        std::stringstream ss;
        ss << "Scope Report:\n";
        ss << "=============\n\n";

        // Visibility changes
        auto visChanges = getVisibilityChanges();
        if (!visChanges.empty()) {
            ss << "Visibility Changes:\n";
            ss << "------------------\n";
            for (const auto& change : visChanges) {
                ss << "Variable: " << change.name << "\n";
                ss << "  Original Level: " << change.originalLevel << "\n";
                ss << "  New Level: " << change.newLevel << "\n";
                ss << "  Original Type: " << change.originalVisibility << "\n";
                ss << "  New Type: " << change.newVisibility << "\n\n";
            }
        }


        // Error handling changes
        auto errChanges = getErrorHandlingChanges();
        if (!errChanges.empty()) {
            ss << "Error Handling Changes:\n";
            ss << "----------------------\n";
            for (const auto& change : errChanges) {
                ss << "Variable: " << change.name << "\n";
                ss << "  Level: " << change.level << "\n";
                ss << "  Error Type: " << change.newErrorType << "\n\n";
            }
        }

        // Nullability changes
        auto nullChanges = getNullabilityChanges();
        if (!nullChanges.empty()) {
            ss << "Nullability Changes:\n";
            ss << "-------------------\n";
            for (const auto& change : nullChanges) {
                ss << "Variable: " << change.name << "\n";
                ss << "  Level: " << change.level << "\n";
                ss << "  Was Nullable: " << (change.wasNullable ? "Yes" : "No") << "\n";
                ss << "  Is Nullable: " << (change.isNullable ? "Yes" : "No") << "\n\n";
            }
        }

        return ss.str();
    }

private:
    struct Scope {
        std::unordered_map<std::string, std::shared_ptr<Type>> variables;
    };

    std::vector<Scope> scopes_;
    std::shared_ptr<TypeRegistry> typeRegistry_;

    Scope& currentScope() {
        if (scopes_.empty()) {
            throw Error("ScopeError", "No active scope");
        }
        return scopes_.back();
    }
};

} // namespace pryst
