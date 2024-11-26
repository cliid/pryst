parser grammar PrystParser;

options { tokenVocab=PrystLexer; }

program: moduleDecl* importDecl* declaration* EOF;

moduleDecl
    : MODULE importPath LBRACE declaration* RBRACE
    ;

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
    | errorDecl
    | varDecl
    | tryStmt
    ;

errorDecl
    : ERROR IDENTIFIER (EXTENDS IDENTIFIER)?
      LBRACE
        (constructorDecl | errorMember)*
      RBRACE
    ;

functionDecl
    : returnType IDENTIFIER genericParams? LPAREN parameters? RPAREN block
    ;

parameters
    : parameter (COMMA parameter)* (COMMA defaultParam)*
    ;
parameter
    : type IDENTIFIER
    ;
defaultParam
    : type IDENTIFIER ASSIGN (literal | NULL_LIT)
    ;

literal
    : INTEGER
    | FLOAT_LITERAL
    | STRING
    | BOOLEAN
    ;

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
    | printStmt
    ;

varDecl
    : CONST type identifierList ASSIGN expression SEMICOLON
    | CONST_EXPR type identifierList ASSIGN expression SEMICOLON
    | LET identifierList ASSIGN expression SEMICOLON
    | type identifierList (ASSIGN expression)? SEMICOLON
    ;

identifierList: IDENTIFIER (COMMA IDENTIFIER)*;


assignment: expression ASSIGN expression SEMICOLON;

ifStmt: IF LPAREN expression RPAREN statement (ELSE statement)?;
whileStmt: WHILE LPAREN expression RPAREN statement;
forStmt
    : FOR LPAREN (LET | type) IDENTIFIER IN expression RPAREN statement
    | FOR LPAREN
        (varDecl | expressionStmt | SEMICOLON)
        expression? SEMICOLON
        expression? RPAREN
        statement
    ;
returnStmt: RETURN expression? SEMICOLON;
tryStmt: TRY block catchClause* (FINALLY block)?;
catchClause: CATCH LPAREN type IDENTIFIER (CHAIN expression)? RPAREN block;
breakStmt: BREAK SEMICOLON;
continueStmt: CONTINUE SEMICOLON;
printStmt: PRINT LPAREN expression RPAREN SEMICOLON;

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
    : returnType IDENTIFIER LPAREN parameters? RPAREN SEMICOLON
    | returnType IDENTIFIER SEMICOLON
    ;

genericParams: LT IDENTIFIER (COMMA IDENTIFIER)* GT;
genericArgs: LT type (COMMA type)* GT;

classMember
    : (CONST | CONST_EXPR)? type IDENTIFIER SEMICOLON
    | returnType IDENTIFIER genericParams? LPAREN parameters? RPAREN block
    | returnType IDENTIFIER LPAREN overloadParams? RPAREN block
    ;

overloadParams: parameter (COMMA parameter)*;

constructorDecl
    : IDENTIFIER LPAREN parameters? RPAREN constructorBlock
    ;

constructorBlock
    : LBRACE (THIS DOT IDENTIFIER ASSIGN expression SEMICOLON | statement)* RBRACE
    ;

type
    : primaryType typeRest*
    ;

typeRest
    : PIPE primaryType
    | AMP primaryType
    ;

primaryType
    : nullableType
    | qualifiedType genericArgs?
    | functionType
    | arrayType
    | mapType
    | basicType
    ;

qualifiedType
    : IDENTIFIER (DOUBLE_COLON IDENTIFIER)*
    ;

returnType
    : type
    | VOID
    ;

nullableType
    : (qualifiedType | functionType | arrayType | mapType | basicType) QUESTION_MARK
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
    : FN LT returnType GT LPAREN typeList? RPAREN
    ;

typeList
    : type (COMMA type)*
    ;

expression
    : primary                                               # primaryExpr
    | NEW qualifiedType genericArgs? LPAREN arguments? RPAREN  # constructorExpr
    | IDENTIFIER LPAREN arguments? RPAREN                   # functionCallExpr
    | expression INSTANCEOF type                            # instanceofExpr
    | TYPEOF expression                                     # typeofExpr
    | expression DOT IDENTIFIER                             # memberAccessExpr
    | expression QUESTION_MARK DOT IDENTIFIER               # nullableChain
    | expression DOT IDENTIFIER genericArgs?
      LPAREN arguments? RPAREN                              # methodCallExpr
    | expression QUESTION_MARK DOT IDENTIFIER genericArgs?
      LPAREN arguments? RPAREN                              # nullableMethodCallExpr
    | expression (LBRACK expression RBRACK)+                # arrayAccessExpr
    | LPAREN type RPAREN expression                         # castExpr
    | expression NOT                                        # nonNullAssertExpr
    | LPAREN expression RPAREN                              # parenExpr
    | prefix=(NOT | MINUS | INC | DEC) expression           # prefixExpr
    | expression postfix=(INC | DEC)                        # postfixExpr
    | expression op=(STAR | SLASH | PERCENT) expression     # multiplicativeExpr
    | expression op=(PLUS | MINUS) expression               # additiveExpr
    | expression op=(LT | GT | LE | GE) expression          # relationalExpr
    | expression op=(EQ | NEQ) expression                   # equalityExpr
    | expression NULL_COALESCE expression                   # nullCoalesceExpr
    | expression AND expression                             # logicalAndExpr
    | expression OR expression                              # logicalOrExpr
    | <assoc=right> expression QUESTION_MARK expression COLON expression # conditionalExpr
    | <assoc=right> expression ASSIGN expression            # assignmentExpr
    | LPAREN lambdaParams? RPAREN ARROW
      (returnType block | expression)                       # lambdaExpr
    ;

primary
    : THIS
    | IDENTIFIER
    | INTEGER
    | FLOAT_LITERAL
    | STRING
    | stringInterpolation
    | BOOLEAN
    | NULL_LIT
    | arrayLiteral
    | mapLiteral
    ;

stringInterpolation
    : STRING_START expression (STRING_MIDDLE expression)* STRING_END
    ;

chainedCall
    : DOT IDENTIFIER
    | DOT IDENTIFIER LPAREN arguments? RPAREN
    | QUESTION_MARK DOT IDENTIFIER
    | QUESTION_MARK DOT IDENTIFIER LPAREN arguments? RPAREN
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

errorMember
    : type IDENTIFIER SEMICOLON                                  # errorField
    | returnType IDENTIFIER LPAREN parameters? RPAREN block      # errorMethod
    | CHAIN type IDENTIFIER SEMICOLON                           # errorChainField
    ;
