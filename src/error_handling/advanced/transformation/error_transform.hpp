#pragma once

#include "../../../type_system/advanced/types.hpp"
#include "../../../type_system/advanced/type_registry.hpp"
#include <memory>
#include <string>
#include <vector>
#include <functional>

using std::shared_ptr;
using std::string;
using std::vector;

namespace pryst {
namespace core {

class ErrorTransform {
public:
    explicit ErrorTransform(shared_ptr<TypeRegistry> registry);

    shared_ptr<Type> transformError(
        shared_ptr<Type> sourceError,
        shared_ptr<Type> targetError);

    shared_ptr<Type> transformToCustomError(
        shared_ptr<Type> sourceError,
        const string& customErrorType);

    // Advanced error transformation methods
    shared_ptr<Type> transformErrorWithContext(
        shared_ptr<Type> sourceError,
        shared_ptr<Type> targetError,
        const string& context);

    shared_ptr<Type> chainErrorTransformation(
        const vector<shared_ptr<Type>>& errorChain,
        shared_ptr<Type> targetError);

    shared_ptr<Type> transformUnionError(
        shared_ptr<Type> unionError,
        const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer);

    shared_ptr<Type> transformIntersectionError(
        shared_ptr<Type> intersectionError,
        const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer);

    shared_ptr<Type> transformParameterizedError(
        shared_ptr<Type> paramError,
        const std::function<shared_ptr<Type>(shared_ptr<Type>)>& transformer);

private:
    shared_ptr<TypeRegistry> typeRegistry_;

    // Helper methods for error transformation
    bool isCompatibleErrorType(shared_ptr<Type> source, shared_ptr<Type> target);
    shared_ptr<Type> mergeErrorTypes(const vector<shared_ptr<Type>>& errors);
};

} // namespace core
} // namespace pryst
