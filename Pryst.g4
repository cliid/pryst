grammar Pryst;

program: declaration* EOF;

declaration
    : functionDecl
    | variableDecl
    | statement
    ;

functionDecl
    : type IDENTIFIER '(' paramList? ')' block
    ;

variableDecl
    : type IDENTIFIER ('=' expression)? ';'
    ;

paramList
    : param (',' param)*
    ;

param
    : type IDENTIFIER
    ;

type
    : 'int'
    | 'float'
    | 'bool'
    | 'str'
    | type '[' ']'
    ;

statement
    : expressionStmt
    | ifStmt
    | whileStmt
    | forStmt
    | returnStmt
    | block
    ;

expressionStmt
    : expression ';'
    ;

ifStmt
    : 'if' '(' expression ')' statement ('else' statement)?
    ;

whileStmt
    : 'while' '(' expression ')' statement
    ;

forStmt
    : 'for' '(' (variableDecl | expressionStmt | ';')
      expression? ';'
      expression? ')' statement
    ;

returnStmt
    : 'return' expression? ';'
    ;

block
    : '{' declaration* '}'
    ;

expression
    : assignment
    ;

assignment
    : (call '.')? IDENTIFIER '=' assignment
    | logicOr
    ;

logicOr
    : logicAnd ('||' logicAnd)*
    ;

logicAnd
    : equality ('&&' equality)*
    ;

equality
    : comparison (('!=' | '==') comparison)*
    ;

comparison
    : addition (('<' | '<=' | '>' | '>=') addition)*
    ;

addition
    : multiplication (('+' | '-') multiplication)*
    ;

multiplication
    : unary (('*' | '/' | '%') unary)*
    ;

unary
    : ('!' | '-' | '++' | '--') unary
    | postfix
    ;

postfix
    : primary ('++' | '--')?
    ;

call
    : primary ('(' arguments? ')' | '[' expression ']' | '.' IDENTIFIER)*
    ;

primary
    : 'true' | 'false' | 'null' | 'this'
    | NUMBER | STRING | IDENTIFIER
    | '(' expression ')'
    | 'super' '.' IDENTIFIER
    ;

arguments
    : expression (',' expression)*
    ;

NUMBER: [0-9]+ ('.' [0-9]+)?;
STRING: '"' .*? '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
COMMENT: '//' .*? '\n' -> skip;
WS: [ \t\r\n]+ -> skip;
