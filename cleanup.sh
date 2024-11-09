#!/bin/bash

# Remove class_info.hpp as it's no longer needed
echo "Removing class_info.hpp..."
rm -f src/codegen/class_info.hpp

# Remove consolidated auxiliary files
echo "Removing auxiliary files that have been consolidated..."

# LLVM codegen files
echo "Cleaning up LLVM codegen files..."
rm -f src/codegen/llvm_codegen.cpp.{fix,bak,new,consolidated}*
mv src/codegen/llvm_codegen.cpp.merged.consolidated src/codegen/llvm_codegen.cpp
mv src/codegen/llvm_codegen.hpp.merged.consolidated src/codegen/llvm_codegen.hpp

# Visitor methods
echo "Cleaning up visitor methods files..."
rm -f src/codegen/visitor_methods.cpp.{fix,new}*

# Builtin functions
echo "Cleaning up builtin functions files..."
rm -f src/codegen/builtin_functions.cpp.fix*

# Semantic analyzer
echo "Cleaning up semantic analyzer files..."
rm -f src/semantic/semantic_analyzer.{cpp,hpp}.{fix,new}*

# Diagnostic visitor
echo "Cleaning up diagnostic visitor files..."
rm -f src/diagnostic/diagnostic_visitor.{cpp,hpp}.{fix,new}*

# Remove duplicate implementations
echo "Cleaning up duplicate implementations..."
rm -f src/semantic/type_registry.cpp  # Keep the one in codegen
rm -f src/utils/llvm_utils.hpp       # Keep the one in codegen

echo "Cleanup complete!"
