grammar Pryst;

program
    : declaration* EOF
    ;

declaration
    : functionDecl
    | variableDecl
    | classDeclaration
    | statement
    ;

// Function Declaration
functionDecl
    : type IDENTIFIER LPAREN paramList? RPAREN block
    ;

// Variable Declaration
variableDecl
    : type IDENTIFIER (EQUAL expression)? SEMICOLON
    ;

// Class Declaration
classDeclaration
    : CLASS IDENTIFIER (EXTENDS IDENTIFIER)? LBRACE classMember* RBRACE
    ;

// Class Member: Variable or Function Declaration
classMember
    : variableDecl
    | functionDecl
    ;

// Parameter List
paramList
    : param (COMMA param)*
    ;

// Parameter
param
    : type IDENTIFIER
    ;

// Type Definitions
type
    : INT
    | FLOAT
    | BOOL
    | STR
    | IDENTIFIER           // For user-defined types (classes)
    | type LBRACKET RBRACKET  // For array types
    ;

// Statements
statement
    : expressionStmt
    | ifStmt
    | whileStmt
    | forStmt
    | returnStmt
    | block
    ;

// Expression Statement
expressionStmt
    : expression SEMICOLON
    ;

// If Statement
ifStmt
    : IF LPAREN expression RPAREN statement (ELSE statement)?
    ;

// While Statement
whileStmt
    : WHILE LPAREN expression RPAREN statement
    ;

// For Statement
forStmt
    : FOR LPAREN (variableDecl | expressionStmt | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement
    ;

// Return Statement
returnStmt
    : RETURN expression? SEMICOLON
    ;

// Block of Statements
block
    : LBRACE declaration* RBRACE
    ;

// Expressions
expression
    : assignment
    | logicOr
    ;

// Assignment Expression
assignment
    : (call DOT)? IDENTIFIER EQUAL expression
    ;

// Logical OR Expression
logicOr
    : logicAnd (OR logicAnd)*
    ;

// Logical AND Expression
logicAnd
    : equality (AND equality)*
    ;

// Equality Expression
equality
    : comparison ((NOT_EQUAL | EQUAL_EQUAL) comparison)*
    ;

// Comparison Expression
comparison
    : addition ((LESS | LESS_EQUAL | GREATER | GREATER_EQUAL) addition)*
    ;

// Addition/Subtraction Expression
addition
    : multiplication ((PLUS | MINUS) multiplication)*
    ;

// Multiplication/Division Expression
multiplication
    : unary ((STAR | SLASH | PERCENT) unary)*
    ;

// Unary Expression
unary
    : (BANG | MINUS | INCREMENT | DECREMENT) unary
    | postfix
    ;

// Postfix Expression
postfix
    : primary callSuffix* (INCREMENT | DECREMENT)?
    ;

// Function Call or Member Access
call
    : primary callSuffix*
    ;

// Call Suffix for Function Calls and Member Access
callSuffix
    : LPAREN arguments? RPAREN       // Function call
    | LBRACKET expression RBRACKET   // Array indexing
    | DOT IDENTIFIER                 // Member access
    ;

// Primary Expressions
primary
    : TRUE
    | FALSE
    | NULL
    | THIS
    | NUMBER
    | STRING
    | IDENTIFIER
    | LPAREN expression RPAREN
    | SUPER DOT IDENTIFIER
    | newExpression
    ;

// Object Creation Expression
newExpression
    : NEW IDENTIFIER LPAREN arguments? RPAREN
    ;

// Arguments for Function Calls
arguments
    : expression (COMMA expression)*
    ;

// Lexer Rules

// Operators and Punctuation
LPAREN      : '(';
RPAREN      : ')';
LBRACE      : '{';
RBRACE      : '}';
LBRACKET    : '[';
RBRACKET    : ']';
COMMA       : ',';
DOT         : '.';
MINUS       : '-';
PLUS        : '+';
SEMICOLON   : ';';
SLASH       : '/';
STAR        : '*';
BANG        : '!';
EQUAL       : '=';
GREATER     : '>';
LESS        : '<';
NOT_EQUAL   : '!=';
EQUAL_EQUAL : '==';
GREATER_EQUAL : '>=';
LESS_EQUAL  : '<=';
AND         : '&&';
OR          : '||';
INCREMENT   : '++';
DECREMENT   : '--';
PERCENT     : '%';

// Keywords
CLASS       : 'class';
EXTENDS     : 'extends';
ELSE        : 'else';
FALSE       : 'false';
FOR         : 'for';
IF          : 'if';
NULL        : 'null';
RETURN      : 'return';
SUPER       : 'super';
THIS        : 'this';
TRUE        : 'true';
WHILE       : 'while';
NEW         : 'new';

// Types
INT         : 'int';
FLOAT       : 'float';
BOOL        : 'bool';
STR         : 'str';

// Literals
NUMBER      : [0-9]+ ('.' [0-9]+)?;
STRING      : '"' (~["\\] | '\\' .)* '"';

// Identifiers
IDENTIFIER  : [a-zA-Z_][a-zA-Z_0-9]*;

// Comments and Whitespace
COMMENT     : '//' ~[\r\n]* -> skip;
WS          : [ \t\r\n]+ -> skip;
