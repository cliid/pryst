parser grammar PrystParser;

options {
    tokenVocab=PrystLexer;
}

program: declaration* EOF;

declaration
    : functionDecl
    | variableDecl
    | classDecl
    | usingDecl
    | statement
    | namespaceDecl
    | moduleDecl
    | importDecl
    ;

usingDecl
    : USING NAMESPACE qualifiedIdentifier SEMICOLON
    | USING MODULE qualifiedIdentifier SEMICOLON
    | USING NAMESPACE qualifiedIdentifier block
    | USING MODULE qualifiedIdentifier block
    ;

namespaceDecl: NAMESPACE qualifiedIdentifier block;

moduleDecl: MODULE qualifiedIdentifier block;

importDecl: IMPORT importPath SEMICOLON;

importPath: IDENTIFIER (DOUBLE_COLON IDENTIFIER)*;

functionDecl: namedFunction | lambdaFunction;

namedFunction
    : FN LESS type GREATER IDENTIFIER LPAREN paramList? RPAREN block
    | FN IDENTIFIER LPAREN paramList? RPAREN ARROW type block
    | type IDENTIFIER LPAREN paramList? RPAREN block
    ;

lambdaFunction
    : LPAREN paramList? RPAREN ARROW type block
    | LPAREN paramList? RPAREN ARROW type expression
    ;

block: LBRACE declaration* RBRACE;

variableDecl
    : (LET | CONST) IDENTIFIER EQUAL expression SEMICOLON
    | (type | CONST type | CONST_EXPR) IDENTIFIER EQUAL expression SEMICOLON
    | type IDENTIFIER SEMICOLON
    ;

classDecl: CLASS IDENTIFIER (EXTENDS IDENTIFIER)? classBody;

classBody: LBRACE classMember* RBRACE;

classMember
    : type IDENTIFIER EQUAL expression SEMICOLON
    | LET IDENTIFIER EQUAL expression SEMICOLON
    | CONST IDENTIFIER EQUAL expression SEMICOLON
    | CONST type IDENTIFIER EQUAL expression SEMICOLON
    | IDENTIFIER LPAREN paramList? RPAREN ARROW type block
    ;

paramList: param (COMMA param)*;

param
    : type IDENTIFIER
    | FN LESS type GREATER LPAREN paramTypeList? RPAREN IDENTIFIER
    ;

paramTypeList: type (COMMA type)*;

type
    : INT_TYPE
    | FLOAT_TYPE
    | BOOL_TYPE
    | STR_TYPE
    | VOID_TYPE
    | IDENTIFIER
    | type LBRACKET RBRACKET
    | FN LESS type GREATER LPAREN paramTypeList? RPAREN
    ;

statement
    : expression SEMICOLON
    | IF LPAREN expression RPAREN statement (ELSE statement)?
    | WHILE LPAREN expression RPAREN statement
    | FOR LPAREN (variableDecl | expression SEMICOLON | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement
    | RETURN expression? SEMICOLON
    | block
    | tryCatchStmt
    | PRINT LPAREN (expression (COMMA expression)*)? RPAREN SEMICOLON
    ;

expression
    : assignment
    | lambdaFunction
    | typeCastExpr
    | typeConversionExpr
    | classConversionExpr
    | stringLiteral
    | logicOr
    ;

stringLiteral: STRING_START stringPart* STRING_END;

stringPart
    : STRING_CONTENT
    | ESCAPE_SEQ
    | INTERP_START expression INTERP_END
    ;

assignment: (call DOT)? qualifiedIdentifier EQUAL expression;

logicOr: logicAnd (OR logicAnd)*;

logicAnd: equality (AND equality)*;

equality: comparison ((NOT_EQUAL | EQUAL_EQUAL) comparison)*;

comparison: addition ((LESS | LESS_EQUAL | GREATER | GREATER_EQUAL) addition)*;

addition: multiplication ((PLUS | MINUS) multiplication)*;

multiplication: unary ((STAR | SLASH | PERCENT) unary)*;

unary
    : (BANG | MINUS | INCREMENT | DECREMENT) unary
    | postfix
    ;

postfix: primary (suffix | INCREMENT | DECREMENT)*;

suffix
    : callSuffix
    | memberSuffix
    ;

callSuffix: LPAREN arguments? RPAREN;

memberSuffix
    : DOT IDENTIFIER
    | DOT IDENTIFIER LPAREN arguments? RPAREN
    ;

call: qualifiedIdentifier (DOT IDENTIFIER)*;

primary
    : TRUE
    | FALSE
    | NULL
    | THIS
    | NUMBER
    | STRING
    | qualifiedIdentifier (LPAREN arguments? RPAREN)?
    | LPAREN expression RPAREN
    | SUPER DOT IDENTIFIER
    | newExpr
    ;

qualifiedIdentifier: IDENTIFIER (DOUBLE_COLON IDENTIFIER)*;

newExpr: NEW IDENTIFIER LPAREN arguments? RPAREN;

arguments: expression (COMMA expression)*;

typeCastExpr
    : LPAREN type RPAREN expression
    | type LPAREN expression RPAREN
    ;

typeConversionExpr: type DOT CONVERT LPAREN expression RPAREN;

classConversionExpr: IDENTIFIER DOT CONVERT LPAREN expression RPAREN;

tryCatchStmt: TRY statement (CATCH LPAREN IDENTIFIER RPAREN statement)?;
