#pragma once

#include "../../../type_system/advanced/types.hpp"
#include "../../../type_system/advanced/type_registry.hpp"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

namespace pryst {
namespace core {

class ErrorPropagation {
public:
    explicit ErrorPropagation(shared_ptr<TypeRegistry> registry);

    shared_ptr<Type> propagateError(
        shared_ptr<Type> sourceError,
        const vector<shared_ptr<Type>>& propagationPath);

    // Advanced error propagation methods
    shared_ptr<Type> propagateErrorThroughScope(
        shared_ptr<Type> error,
        const string& scopeName,
        bool propagateToParent = true);

    shared_ptr<Type> propagateErrorWithTransform(
        shared_ptr<Type> error,
        const vector<shared_ptr<Type>>& path,
        const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer);

    shared_ptr<Type> propagateUnionError(
        shared_ptr<Type> unionError,
        const vector<shared_ptr<Type>>& path);

    shared_ptr<Type> propagateIntersectionError(
        shared_ptr<Type> intersectionError,
        const vector<shared_ptr<Type>>& path);

    // Error propagation control
    void addPropagationBarrier(const string& scopeName);
    void removePropagationBarrier(const string& scopeName);
    bool shouldPropagate(const string& fromScope, const string& toScope) const;

private:
    shared_ptr<TypeRegistry> typeRegistry_;
    vector<string> propagationBarriers_;

    // Helper methods
    bool isValidPropagationPath(const vector<shared_ptr<Type>>& path) const;
    shared_ptr<Type> transformErrorForPropagation(
        shared_ptr<Type> error,
        shared_ptr<Type> contextType);
};

} // namespace core
} // namespace pryst
