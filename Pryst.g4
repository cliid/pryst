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
    : type IDENTIFIER LPAREN paramList? RPAREN LBRACE declaration* RBRACE
    ;

variableDecl
    : type IDENTIFIER (EQUAL expression)? SEMICOLON
    ;

classDeclaration
    : CLASS IDENTIFIER (EXTENDS IDENTIFIER)? classBody
    ;

classBody
    : LBRACE classMember* RBRACE
    ;

classMember
    : type IDENTIFIER (EQUAL expression)? SEMICOLON  # classVariableDecl
    | type IDENTIFIER LPAREN paramList? RPAREN LBRACE declaration* RBRACE # classFunctionDecl
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
    : expression SEMICOLON                          # exprStatement
    | IF LPAREN expression RPAREN statement (ELSE statement)?  # ifStatement
    | WHILE LPAREN expression RPAREN statement               # whileStatement
    | FOR LPAREN (variableDecl | expression SEMICOLON | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement                  # forStatement
    | RETURN expression? SEMICOLON                  # returnStatement
    | LBRACE declaration* RBRACE                    # blockStatement
    ;

expression
    : assignment
    | logicOr
    ;

assignment
    : IDENTIFIER EQUAL expression
    | call DOT IDENTIFIER EQUAL expression
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
    : primary (LPAREN arguments? RPAREN)*
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
