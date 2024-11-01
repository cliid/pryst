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

functionDecl
    : type IDENTIFIER LPAREN paramList? RPAREN block
    ;

variableDecl
    : type IDENTIFIER (EQUAL expression)? SEMICOLON
    ;

classDeclaration
    : CLASS IDENTIFIER (EXTENDS IDENTIFIER)? LBRACE classMember* RBRACE
    ;

classMember
    : variableDecl
    | functionDecl
    ;

paramList
    : param (COMMA param)*
    ;

param
    : type IDENTIFIER
    ;

type
    : INT
    | FLOAT
    | BOOL
    | STR
    | VOID
    | IDENTIFIER
    | type LBRACKET RBRACKET
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
    : expression SEMICOLON
    ;

ifStmt
    : IF LPAREN expression RPAREN statement (ELSE statement)?
    ;

whileStmt
    : WHILE LPAREN expression RPAREN statement
    ;

forStmt
    : FOR LPAREN (variableDecl | expressionStmt | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement
    ;

returnStmt
    : RETURN expression? SEMICOLON
    ;

block
    : LBRACE declaration* RBRACE
    ;

expression
    : assignment
    | logicOr
    ;

assignment
    : call EQUAL expression
    ;

logicOr
    : logicAnd (OR logicAnd)*
    ;

logicAnd
    : equality (AND equality)*
    ;

equality
    : comparison ((NOT_EQUAL | EQUAL_EQUAL) comparison)*
    ;

comparison
    : addition ((LESS | LESS_EQUAL | GREATER | GREATER_EQUAL) addition)*
    ;

addition
    : multiplication ((PLUS | MINUS) multiplication)*
    ;

multiplication
    : unary ((STAR | SLASH | PERCENT) unary)*
    ;

unary
    : (BANG | MINUS | INCREMENT | DECREMENT) unary
    | postfix
    ;

postfix
    : primary (INCREMENT | DECREMENT)?
    ;

call
    : primary callSuffix*
    ;

callSuffix
    : LPAREN arguments? RPAREN
    | LBRACKET expression RBRACKET
    | DOT IDENTIFIER
    ;

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

newExpression
    : NEW IDENTIFIER LPAREN arguments? RPAREN
    ;

arguments
    : expression (COMMA expression)*
    ;

// Lexer Rules

LPAREN      : '(' ;
RPAREN      : ')' ;
LBRACE      : '{' ;
RBRACE      : '}' ;
LBRACKET    : '[' ;
RBRACKET    : ']' ;
COMMA       : ',' ;
DOT         : '.' ;
MINUS       : '-' ;
PLUS        : '+' ;
SEMICOLON   : ';' ;
SLASH       : '/' ;
STAR        : '*' ;
BANG        : '!' ;
EQUAL       : '=' ;
GREATER     : '>' ;
LESS        : '<' ;
NOT_EQUAL   : '!=' ;
EQUAL_EQUAL : '==' ;
GREATER_EQUAL : '>=' ;
LESS_EQUAL  : '<=' ;
AND         : '&&' ;
OR          : '||' ;
INCREMENT   : '++' ;
DECREMENT   : '--' ;
PERCENT     : '%' ;

CLASS       : 'class' ;
EXTENDS     : 'extends' ;
ELSE        : 'else' ;
FALSE       : 'false' ;
FOR         : 'for' ;
IF          : 'if' ;
NULL        : 'null' ;
RETURN      : 'return' ;
SUPER       : 'super' ;
THIS        : 'this' ;
TRUE        : 'true' ;
WHILE       : 'while' ;
NEW         : 'new' ;

INT         : 'int' ;
FLOAT       : 'float' ;
BOOL        : 'bool' ;
STR         : 'str' ;
VOID        : 'void' ;

NUMBER      : [0-9]+ ('.' [0-9]+)? ;
STRING      : '"' (~["\r\n\\] | '\\' .)* '"' ;
IDENTIFIER  : [a-zA-Z_][a-zA-Z_0-9]* ;

COMMENT     : '//' ~[\r\n]* -> skip ;
WS          : [ \t\r\n]+ -> skip ;
