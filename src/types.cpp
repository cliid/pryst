#include "types.hpp"

namespace pryst {

std::shared_ptr<Type> INT_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Int);
std::shared_ptr<Type> FLOAT_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Float);
std::shared_ptr<Type> BOOL_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Bool);
std::shared_ptr<Type> STRING_TYPE = std::make_shared<PrimitiveType>(Type::Kind::String);
std::shared_ptr<Type> VOID_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Void);
std::shared_ptr<Type> ERROR_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Error);
std::shared_ptr<Type> NULL_TYPE = std::make_shared<PrimitiveType>(Type::Kind::Null);

} // namespace pryst
