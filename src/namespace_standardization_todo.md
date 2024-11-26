# Namespace Standardization Todo List

## Core Type System Files
- [x] type_registry.hpp
- [x] type.hpp (includes FunctionType, ArrayType, MapType, UnionType, IntersectionType)
- [x] error_type.hpp

## Error Handling Files
- [x] diagnostic_error_listener.hpp (replaces diagnostic.hpp)
- [x] error_handler.hpp
- [x] error.hpp (replaces semantic_error.hpp)
- [x] error_chain.hpp
- [x] error_propagation.hpp
- [x] error_handling/advanced/* (all advanced error handling files)

## Runtime Implementation
- [x] runtime_registry.hpp (updated to use core namespace)
- [x] runtime.hpp (renamed RuntimeRegistry to RuntimeTypeSystem)
- [x] runtime_type_ops.hpp (updated includes and namespace usage)

## Code Generation
- [x] llvm_codegen.hpp (moved to core namespace, updated type references)
- [x] llvm_type_converter.hpp (renamed from type_converter.hpp, moved to core namespace)
- [-] ir_builder.hpp (functionality integrated in llvm_codegen.hpp)

## Standard Rules
1. Use explicit namespace blocks:
   ```cpp
   namespace pryst {
   namespace core {
   // code here
   } // namespace core
   } // namespace pryst
   ```

2. Never use `pryst::` inside namespace blocks
3. Always use `core::` qualification for types
4. Use trailing underscore for private members
5. Keep includes organized with core/ prefix

## Progress Tracking
- [x] Review all files
- [x] Update namespace declarations
- [x] Fix type qualifications
- [x] Standardize member naming
- [ ] Update include statements
- [ ] Verify compilation
- [ ] Run tests

## Notes
- FunctionType, ArrayType, MapType, UnionType, and IntersectionType are all defined in types.hpp
- All type-related namespace updates have been completed in the consolidated types.hpp file
- Error handling system has been fully updated to use core namespace
- Advanced error handling components are properly namespaced
- Runtime system has been updated to use core namespace consistently
- Resolved RuntimeRegistry duplication by creating RuntimeTypeSystem
- Code generation components moved to core namespace with consistent type references
- IR builder functionality is part of llvm_codegen.hpp, not a separate file
