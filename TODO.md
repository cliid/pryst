# ANTLR Reference Update Todo List

## High Priority Files
These files are most likely to contain direct ANTLR-generated file references and need immediate attention:

1. src/main.cpp
   - Check parser/lexer initialization
   - Update include paths for PrystLexer.h and PrystParser.h
   - Verify visitor class references

2. src/compiler.cpp & compiler.hpp
   - Update ANTLR visitor class includes
   - Check for any direct parser/lexer references
   - Verify namespace usage matches generated files

3. src/type_checker.cpp & type_checker.hpp
   - Update BaseVisitor includes
   - Check visitor implementation inheritance
   - Verify ANTLR context class references

4. src/llvm_codegen.cpp & llvm_codegen.hpp
   - Update visitor includes
   - Check ANTLR context usage in code generation
   - Verify parser tree node references

## Medium Priority Files
These files may contain indirect ANTLR references:

5. src/types.cpp & types.hpp
   - Check for any type system integration with ANTLR
   - Verify AST node type references

6. src/runtime.cpp
   - Check for any runtime parser/lexer usage
   - Verify error handling with ANTLR contexts

7. src/webserver.cpp
   - Check for any dynamic parsing features
   - Verify error reporting using ANTLR contexts

## Update Process
For each file:
1. Check current include paths
2. Update to use files from src/generated/
3. Verify namespace usage (pryst::)
4. Test compilation after each update
5. Document any issues encountered

## Notes
- All ANTLR-generated files are now in src/generated/
- Use proper namespace qualifiers
- Avoid editing generated files
- Update includes to use relative paths from src/generated/
