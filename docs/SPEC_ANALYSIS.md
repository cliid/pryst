# Pryst Language Specification Analysis

## Overview
Pryst combines C-like syntax with modern safety features to prevent segmentation faults while maintaining high performance. The language achieves this through strong typing, garbage collection, and elimination of explicit pointer manipulation.

## 1. Lexical Structure
### Keywords (Reserved Words)
```
int, float, bool, str, void
let, class, return, if, else, while, for, in
import, try, catch, as, break, continue
```

### Operators
- Arithmetic: `+ - * / %`
- Assignment: `=`
- Comparison: `== != < > <= >=`
- Logical: `&& || !`
- String: `+` (concatenation)
- Error: `?` (propagation)
- Lambda: `->` (definition)

### Literals
- Integers: 64-bit signed `[0-9]+`
- Floats: 64-bit IEEE-754 `[0-9]+\.[0-9]+`
- Strings: UTF-8 `"([^"]|\\")*"`
- Booleans: `true|false`
- Arrays: `{ comma-separated-expressions }`
- Maps: `{ key:value pairs }`

### Identifiers
Pattern: `[a-zA-Z_][a-zA-Z0-9_]*`

## 2. Type System
### Built-in Types
- Basic: `int` (64-bit), `float` (64-bit), `bool`, `str` (UTF-8), `void`
- Compound: Arrays `T[]`, Maps `map<K,V>`
- User-defined: Classes

### Type Safety Features
- Strong static typing
- No implicit conversions (except int->float)
- Generic type parameters
- Type inference for locals only

### Type Casting
Two equivalent syntaxes for type casting:
```pryst
// C-style cast
(type) expression
// Function-style cast
type(expression)
```

## 3. Functions
### Function Declarations
```pryst
return_type function_name(param_type1 param1, param_type2 param2) {
    statements
    return expression;
}
```

### Lambda Functions
```pryst
(Type1 param1, Type2 param2) -> expression
(Type1 param1, Type2 param2) -> { statements }
```

## 4. Control Flow
### Structures
- If statements: `if (condition) { statements }`
- While loops: `while (condition) { statements }`
- For loops:
  ```pryst
  // C-style for loop
  for (int i = 0; i < 10; i = i + 1) {
      statements
  }

  // Iterator-style for loop
  for (type item in iterable) {
      statements
  }
  ```
- Error handling: `try { statements } catch (Error e) { statements }`

## 5. Error Handling
### Features
- Error propagation operator (`?`)
- Try-catch blocks
- Stack trace support
- Type-safe error handling

## 6. Classes
### Class Definition
```pryst
class ClassName {
    // Fields (explicit types required)
    type1 field1;
    type2 field2;

    // Constructor
    ClassName(param_type1 param1) {
        this.field1 = param1;
    }

    // Methods
    return_type method_name(param_type param) {
        statements
    }
}
```

## 7. Built-in Types Implementation
### String Methods
- `length()`, `contains()`, `upper()`, `lower()`, `trim()`, `split()`

### Array Methods
- `push()`, `pop()`, `length()`, `map()`, `filter()`, `reduce()`

### Map Methods
- `get()`, `set()`, `has()`, `remove()`, `keys()`, `values()`, `length()`

## 8. Modules
### Import Syntax
```pryst
import namespace::module;
import namespace::module as alias;
from namespace::module import item1, item2;
```

## 9. Web Framework
### Server Features
- Server setup: `Server server(port)`
- Route handlers: `server.get()`, `server.post()`
- Request object: path, method, headers, query, body, JSON
- Response object: status, header, send, JSON

## 10. Standard Library
### Components
- File operations (open, read, write, close)
- JSON handling (parse, stringify)
- String manipulation (UTF-8)
- Container operations

## 11. Memory Management
### Safety Features
- Garbage collected (no manual management)
- No explicit pointers
- References only in function parameters
- Deterministic cleanup through scope
- Automatic array bounds checking

## 12. Implementation Requirements
### Compiler Phases
1. Lexical analysis (ANTLR4)
2. Parsing (ANTLR4 grammar)
3. Type checking (explicit types)
4. LLVM IR generation (LLVM 14)
5. Optimization passes
6. Binary generation

### Runtime Requirements
- Garbage collector implementation
- UTF-8 string handling
- Dynamic arrays
- Hash table maps
- Web server implementation

## 13. Example Implementation Analysis
The provided example demonstrates:
- Module imports
- Class definition with methods
- Lambda functions for handlers
- Error propagation
- Container usage
- Web server setup
- JSON handling
- Type inference
- Memory safety

## 14. Grammar (EBNF)
```ebnf
program ::= import* declaration*
import ::= 'import' identifier ('as' identifier)? ';'
        | 'from' identifier 'import' identifier (',' identifier)* ';'
declaration ::= functionDecl | classDecl | varDecl
functionDecl ::= type identifier '(' parameters? ')' block
parameters ::= parameter (',' parameter)*
parameter ::= type identifier
block ::= '{' statement* '}'
statement ::= varDecl | assignment | functionCall | ifStmt
            | whileStmt | forStmt | returnStmt | tryStmt
varDecl ::= (type identifier | 'let' identifier) '=' expression ';'
assignment ::= expression '=' expression ';'
ifStmt ::= 'if' '(' expression ')' block ('else' block)?
whileStmt ::= 'while' '(' expression ')' block
forStmt ::= 'for' '(' forInit? ';' expression? ';' expression? ')' block
          | 'for' '(' type identifier 'in' expression ')' block
forInit ::= varDecl | assignment | expression
returnStmt ::= 'return' expression? ';'
tryStmt ::= 'try' block 'catch' '(' 'Error' identifier ')' block
expression ::= literal | identifier | functionCall | binaryOp
             | unaryOp | lambda | arrayLiteral | mapLiteral
             | typeCast
typeCast ::= '(' type ')' expression
           | type '(' expression ')'
lambda ::= '(' parameters? ')' '->' (block | expression)
```

## 15. Implementation Notes
### Key Implementation Decisions
1. LLVM Integration
   - Use LLVM 14 for optimization
   - Generate debug information
   - Implement error handling

2. Memory Safety
   - Implement bounds checking
   - Track object lifetimes
   - Handle circular references

3. Type System
   - Implement generic type resolution
   - Handle type inference
   - Manage error types

4. Build Process
   - Single-pass compilation
   - No preprocessor
   - Direct binary generation

### Safety Guarantees
1. No Segfaults Through:
   - Bounds checking
   - Null checks
   - Type safety
   - Memory management

2. Performance Considerations:
   - LLVM optimizations
   - Minimal runtime overhead
   - Efficient garbage collection

## Conclusion
The specification provides a complete blueprint for a modern, safe programming language that prevents common C-style errors while maintaining familiar syntax and high performance. The implementation requirements are clear and achievable using LLVM 14 and ANTLR4.
