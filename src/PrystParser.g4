parser grammar PrystParser;

options { tokenVocab=PrystLexer; }

// Parser rules
program: importDecl* declaration* EOF;

importDecl
    : IMPORT importPath SEMICOLON
    | IMPORT importPath AS IDENTIFIER SEMICOLON
    | FROM importPath IMPORT IDENTIFIER (COMMA IDENTIFIER)* SEMICOLON
    ;

importPath: IDENTIFIER (DOUBLE_COLON IDENTIFIER)*;

declaration
    : functionDecl
    | classDecl
    | interfaceDecl
    | varDecl
    | tryStmt
    ;

functionDecl
    : type? IDENTIFIER genericParams? LPAREN parameters? RPAREN (ARROW (type | VOID))? block
    ;

parameters: parameter (COMMA parameter)*;
parameter: type IDENTIFIER;

block: LBRACE statement* RBRACE;

statement
    : block
    | varDecl
    | assignment
    | expressionStmt
    | ifStmt
    | whileStmt
    | forStmt
    | returnStmt
    | tryStmt
    | breakStmt
    | continueStmt
    ;

varDecl
    : (CONST | CONST_EXPR)? type identifierList ASSIGN expression SEMICOLON
    | LET identifierList ASSIGN expression SEMICOLON
    | type identifierList (ASSIGN expression)? SEMICOLON
    | CONST identifierList ASSIGN expression SEMICOLON
    ;

identifierList: IDENTIFIER (COMMA IDENTIFIER)*;


assignment: expression ASSIGN expression SEMICOLON;

ifStmt: IF LPAREN expression RPAREN statement (ELSE statement)?;
whileStmt: WHILE LPAREN expression RPAREN statement;
forStmt
    : FOR LPAREN type IDENTIFIER IN expression RPAREN statement
    | FOR LPAREN
        (varDecl | expressionStmt | SEMICOLON)
        expression? SEMICOLON
        expression? RPAREN
        statement
    ;
returnStmt: RETURN expression? SEMICOLON;
tryStmt: TRY block (CATCH LPAREN type IDENTIFIER RPAREN block)*;
breakStmt: BREAK SEMICOLON;
continueStmt: CONTINUE SEMICOLON;

expressionStmt: expression SEMICOLON;

classDecl
    : CLASS IDENTIFIER genericParams?
      (EXTENDS IDENTIFIER genericArgs?)?
      (IMPLEMENTS IDENTIFIER genericArgs? (COMMA IDENTIFIER genericArgs?)*)?
      LBRACE
        (constructorDecl | classMember)*
      RBRACE
    ;

interfaceDecl
    : INTERFACE IDENTIFIER genericParams?
      (EXTENDS IDENTIFIER genericArgs? (COMMA IDENTIFIER genericArgs?)*)?
      LBRACE
        interfaceMember*
      RBRACE
    ;

interfaceMember
    : type IDENTIFIER LPAREN parameters? RPAREN SEMICOLON
    | type IDENTIFIER SEMICOLON
    ;

genericParams: LT IDENTIFIER (COMMA IDENTIFIER)* GT;
genericArgs: LT type (COMMA type)* GT;

classMember
    : (CONST | CONST_EXPR)? type IDENTIFIER SEMICOLON
    | type? IDENTIFIER genericParams? LPAREN parameters? RPAREN (ARROW (type | VOID))? block
    | type IDENTIFIER LPAREN overloadParams? RPAREN block
    ;

overloadParams: parameter (COMMA parameter)*;

constructorDecl
    : IDENTIFIER LPAREN parameters? RPAREN constructorBlock
    ;

constructorBlock
    : LBRACE (THIS DOT IDENTIFIER ASSIGN expression SEMICOLON | statement)* RBRACE
    ;

type
    : functionType
    | arrayType
    | mapType
    | basicType
    ;

basicType
    : STR
    | INT
    | FLOAT
    | BOOL
    | VOID
    | IDENTIFIER
    ;

arrayType
    : basicType LBRACK RBRACK
    | arrayType LBRACK RBRACK
    ;

mapType
    : MAP LT keyType COMMA type GT
    ;

keyType
    : STR
    | INT
    ;

functionType
    : FN LT type GT LPAREN typeList? RPAREN
    | FN LPAREN typeList? RPAREN ARROW type
    ;

typeList
    : type (COMMA type)*
    ;

expression
    : primary                                               # primaryExpr
    | IDENTIFIER LPAREN arguments? RPAREN                   # builtinFunctionCall
    | NEW IDENTIFIER genericArgs? LPAREN arguments? RPAREN  # constructorExpr
    | expression DOT IDENTIFIER                             # memberAccessExpr
    | expression QUESTION_MARK DOT IDENTIFIER               # nullableMemberExpr
    | expression DOT IDENTIFIER genericArgs?
      LPAREN arguments? RPAREN                              # methodCallExpr
    | expression (LBRACK expression RBRACK)+                # arrayAccessExpr
    | LPAREN type RPAREN expression                         # castExpr
    | LPAREN expression RPAREN                              # parenExpr
    | prefix=(NOT | MINUS | INC | DEC) expression           # prefixExpr
    | expression postfix=(INC | DEC)                        # postfixExpr
    | expression op=(STAR | SLASH | PERCENT) expression     # multiplicativeExpr
    | expression op=(PLUS | MINUS) expression               # additiveExpr
    | expression op=(LT | GT | LE | GE) expression          # relationalExpr
    | expression op=(EQ | NEQ) expression                   # equalityExpr
    | expression AND expression                             # logicalAndExpr
    | expression OR expression                              # logicalOrExpr
    | <assoc=right> expression QUESTION_MARK expression COLON expression # conditionalExpr
    | <assoc=right> expression ASSIGN expression            # assignmentExpr
    | LPAREN lambdaParams? RPAREN ARROW
      (type | VOID)? block                                  # lambdaExpr
    | LPAREN lambdaParams? RPAREN ARROW expression          # lambdaExprInline
    ;

primary
    : THIS
    | IDENTIFIER
    | INTEGER
    | FLOAT_LITERAL
    | STRING
    | BOOLEAN
    | arrayLiteral
    | mapLiteral
    | FILE DOT fileOperation
    ;

builtinFunction
    : IDENTIFIER LPAREN arguments? RPAREN
    ;

chainedCall
    : DOT IDENTIFIER
    | DOT IDENTIFIER LPAREN arguments? RPAREN
    ;

constructorCall
    : IDENTIFIER LPAREN arguments? RPAREN
    ;

fileOperation
    : FILE DOT (READ | WRITE | OPEN) LPAREN stringLiteral (COMMA expression)? RPAREN
    | primary DOT (READ_TO_STRING | WRITE_ALL | CLOSE) LPAREN expression? RPAREN
    | fileOperation chainedCall
    ;

stringLiteral
    : STRING
    ;

lambdaParams
    : type IDENTIFIER (COMMA type IDENTIFIER)*
    ;

arguments: expression (COMMA expression)*;

arrayLiteral
    : LBRACK RBRACK                                           # emptyArrayLiteral
    | LBRACK expression (COMMA expression)* COMMA? RBRACK     # nonEmptyArrayLiteral
    ;

mapLiteral
    : LBRACE RBRACE                                          # emptyMapLiteral
    | LBRACE mapEntry (COMMA mapEntry)* COMMA? RBRACE        # nonEmptyMapLiteral
    ;

mapEntry
    : (STRING | INTEGER) COLON expression
    ;

mapKey
    : STRING
    | INTEGER
    ;
