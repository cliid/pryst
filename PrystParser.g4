parser grammar PrystParser;

options { tokenVocab=PrystLexer; }

program
    : (namespaceDecl | moduleDecl | importDecl | declaration)* EOF
    ;

declaration
    : functionDecl
    | variableDecl
    | classDeclaration
    | usingDecl
    | statement
    ;

usingDecl
    : (USING NAMESPACE | USING MODULE) qualifiedIdentifier SEMICOLON                    # GlobalUsingDecl
    | USING NAMESPACE qualifiedIdentifier LBRACE declaration* RBRACE                    # BlockScopedNamespaceDecl
    | USING MODULE qualifiedIdentifier LBRACE declaration* RBRACE                       # BlockScopedModuleDecl
    ;

namespaceDecl
    : NAMESPACE qualifiedIdentifier LBRACE (declaration | moduleDecl)* RBRACE
    ;

moduleDecl
    : MODULE qualifiedIdentifier LBRACE declaration* RBRACE
    ;

importDecl
    : IMPORT importPath SEMICOLON
    ;

importPath
    : IDENTIFIER (DOUBLE_COLON IDENTIFIER)*
    ;

functionDecl
    : namedFunction
    | lambdaFunction
    ;

namedFunction
    : FN LESS type GREATER IDENTIFIER LPAREN paramList? RPAREN functionBody
    | FN IDENTIFIER LPAREN paramList? RPAREN (ARROW (type | VOID))? functionBody
    | (type | VOID) IDENTIFIER LPAREN paramList? RPAREN functionBody
    ;

lambdaFunction
    : LPAREN paramList? RPAREN ARROW (type | VOID)? LBRACE declaration* RBRACE
    | LPAREN paramList? RPAREN ARROW (type | VOID)? expression
    ;

functionBody
    : LBRACE statement* RBRACE
    ;

variableDecl
    : (LET | CONST | type | CONST type | CONST_EXPR) IDENTIFIER (EQUAL expression)? SEMICOLON
    ;

classDeclaration
    : CLASS IDENTIFIER (EXTENDS IDENTIFIER)? classBody
    ;

classBody
    : LBRACE classMember* RBRACE
    ;

classMember
    : type IDENTIFIER (EQUAL expression)? SEMICOLON  # classVariableDecl
    | IDENTIFIER LPAREN paramList? RPAREN ARROW type functionBody # classFunctionDecl
    ;

paramList
    : param (COMMA param)*
    ;

param
    : type IDENTIFIER
    | FN LESS type GREATER LPAREN paramTypeList? RPAREN IDENTIFIER
    ;

paramTypeList
    : type (COMMA type)*
    ;

type
    : INT                                             # intType
    | FLOAT                                           # floatType
    | BOOL                                            # boolType
    | STR                                             # strType
    | VOID                                            # voidType
    | IDENTIFIER                                      # identifierType
    | type LBRACKET RBRACKET                         # arrayType
    | FN LESS type GREATER LPAREN paramTypeList? RPAREN   # functionType
    | LPAREN paramTypeList? RPAREN ARROW (type | VOID)    # lambdaType
    ;

statement
    : expression SEMICOLON                          # exprStatement
    | IF LPAREN expression RPAREN statement (ELSE statement)?  # ifStatement
    | WHILE LPAREN expression RPAREN statement               # whileStatement
    | FOR LPAREN (variableDecl | expression SEMICOLON | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement                  # forStatement
    | RETURN expression? SEMICOLON                  # returnStatement
    | TRY statement (CATCH LPAREN type IDENTIFIER RPAREN statement)* # tryCatchStatement
    | LBRACE statement* RBRACE                    # blockStatement
    | PRINT LPAREN expression RPAREN SEMICOLON      # printStatement
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

stringLiteral
    : STRING_START stringPart* STRING_END
    ;

stringPart
    : STRING_CONTENT
    | ESCAPE_SEQ
    | INTERP_START expression RBRACE
    ;

assignment
    : (call DOT)? qualifiedIdentifier EQUAL expression
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
    : primary (suffix | INCREMENT | DECREMENT)*
    ;

suffix
    : callSuffix
    | memberSuffix
    ;

callSuffix
    : LPAREN arguments? RPAREN
    ;

memberSuffix
    : DOT IDENTIFIER
    | DOT IDENTIFIER LPAREN arguments? RPAREN
    ;

call
    : qualifiedIdentifier (DOT IDENTIFIER)*
    ;

primary
    : TRUE
    | FALSE
    | NULL
    | THIS
    | NUMBER
    | qualifiedIdentifier (LPAREN arguments? RPAREN)?
    | LPAREN expression RPAREN
    | SUPER DOT IDENTIFIER
    | newExpression
    ;

qualifiedIdentifier
    : IDENTIFIER (DOUBLE_COLON IDENTIFIER)*
    ;

newExpression
    : NEW IDENTIFIER LPAREN arguments? RPAREN
    ;

arguments
    : expression (COMMA expression)*
    ;

typeCastExpr
    : LPAREN type RPAREN expression
    | type LPAREN expression RPAREN
    ;

typeConversionExpr
    : type DOT CONVERT LPAREN expression RPAREN
    ;

classConversionExpr
    : IDENTIFIER DOT CONVERT LPAREN expression RPAREN
    ;
