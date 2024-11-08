grammar Pryst;

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
    | FN IDENTIFIER LPAREN paramList? RPAREN ARROW type functionBody
    | type IDENTIFIER LPAREN paramList? RPAREN functionBody
    ;

lambdaFunction
    : LPAREN paramList? RPAREN ARROW type LBRACE declaration* RBRACE
    | LPAREN paramList? RPAREN ARROW type expression
    ;

functionBody
    : LBRACE statement* RBRACE
    ;

variableDecl
    : (LET | CONST) IDENTIFIER EQUAL expression SEMICOLON                      # inferredVariableDecl
    | (type | CONST type | CONST_EXPR) IDENTIFIER EQUAL expression SEMICOLON   # typedVariableDecl
    | type IDENTIFIER SEMICOLON                                                # uninitializedVariableDecl
    ;

classDeclaration
    : CLASS IDENTIFIER (EXTENDS IDENTIFIER)? classBody
    ;

classBody
    : LBRACE classMember* RBRACE
    ;

classMember
    : type IDENTIFIER EQUAL expression SEMICOLON                    # ClassMemberDecl
    | LET IDENTIFIER EQUAL expression SEMICOLON                     # ClassMemberInferredDecl
    | CONST IDENTIFIER EQUAL expression SEMICOLON                   # ClassMemberConstInferredDecl
    | CONST type IDENTIFIER EQUAL expression SEMICOLON             # ClassMemberConstTypedDecl
    | IDENTIFIER LPAREN paramList? RPAREN ARROW type functionBody  # ClassMemberFunctionDecl
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
    ;

statement
    : expression SEMICOLON                          # exprStatement
    | IF LPAREN expression RPAREN statement (ELSE statement)?  # ifStatement
    | WHILE LPAREN expression RPAREN statement               # whileStatement
    | FOR LPAREN (variableDecl | expression SEMICOLON | SEMICOLON)
      expression? SEMICOLON
      expression? RPAREN statement                  # forStatement
    | RETURN expression? SEMICOLON                  # returnStatement
    | LBRACE statement* RBRACE                    # blockStatement
    | tryStatement                                # tryStmtWrapper
    | PRINT LPAREN (expression (COMMA expression)*)? RPAREN SEMICOLON      # printStatement
    ;

tryStatement
    : TRY statement (CATCH LPAREN type IDENTIFIER RPAREN statement)?
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
    : STRING                                           # StringLiteralRule
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
    | STRING
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

// Type conversion expressions
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
ARROW       : '->' ;
DOUBLE_COLON : '::' ;

PRINT       : 'print' ;
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
CONVERT     : 'convert' ;
NAMESPACE   : 'namespace' ;
MODULE      : 'module' ;
IMPORT      : 'import' ;
USING       : 'using' ;
LET         : 'let' ;
FN          : 'fn' ;
CONST       : 'const' ;
CONST_EXPR  : 'const!' ;
TRY         : 'try' ;
CATCH       : 'catch' ;

INT         : 'int' ;
FLOAT       : 'float' ;
BOOL        : 'bool' ;
STR         : 'str' ;
VOID        : 'void' ;

NUMBER      : [0-9]+ ('.' [0-9]+)? ;

// String tokens
STRING      : '"' (~["\\\r\n${] | ESCAPE_SEQ | INTERP_EXPR)* '"' ;

fragment ESCAPE_SEQ
    : '\\' [btnfr"'\\]
    | '\\u' HexDigit HexDigit HexDigit HexDigit
    ;

fragment INTERP_EXPR
    : '${' ExpressionContent '}'
    | '{' (IDENTIFIER | QualifiedId) (':' FORMAT_SPEC)? '}'
    ;

fragment ExpressionContent
    : ~[{}]+
    | '{' ExpressionContent '}'
    | NESTED_BRACE
    ;

fragment QualifiedId
    : IDENTIFIER (DOT IDENTIFIER)*
    ;

fragment NESTED_BRACE
    : '{' (~[{}] | NESTED_BRACE)* '}'
    ;

fragment FORMAT_SPEC
    : AlignmentSpec? WidthSpec? ('.' PrecisionSpec)? FormatTypeSpec?
    ;

fragment AlignmentSpec : '<' | '>' | '^' ;
fragment WidthSpec : [0-9]+ ;
fragment PrecisionSpec : [0-9]+ ;
fragment FormatTypeSpec : [dxXfFeEgGsS] ;

fragment StringCharacter
    : ~["\r\n\\$]
    | '\\' [btnfr"'\\]
    | '\\u' HexDigit HexDigit HexDigit HexDigit
    ;

fragment HexDigit : [0-9a-fA-F] ;
IDENTIFIER  : [a-zA-Z_][a-zA-Z_0-9]* ;

COMMENT     : '//' ~[\r\n]* -> skip ;
WS          : [ \t\r\n]+ -> skip ;
