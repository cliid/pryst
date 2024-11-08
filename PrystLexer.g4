lexer grammar PrystLexer;

// Keywords
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
TRY         : 'try' ;
CATCH       : 'catch' ;
LET         : 'let' ;
FN          : 'fn' ;
CONST       : 'const' ;
CONST_EXPR  : 'const!' ;

// Types
INT         : 'int' ;
FLOAT       : 'float' ;
BOOL        : 'bool' ;
STR         : 'str' ;
VOID        : 'void' ;

// Operators and punctuation
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

// Literals
NUMBER      : [0-9]+ ('.' [0-9]+)? ;
IDENTIFIER  : [a-zA-Z_][a-zA-Z_0-9]* ;

// String handling
STRING_START : '"' -> pushMode(IN_STRING) ;

// Comments and whitespace
COMMENT     : '//' ~[\r\n]* -> skip ;
WS          : [ \t\r\n]+ -> skip ;

// String interpolation mode
mode IN_STRING;
STRING_CONTENT : ~["\\\r\n${]+ ;
ESCAPE_SEQ : '\\' [btnfr"'\\] | '\\u' [0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F] ;
INTERP_START : '${' -> pushMode(DEFAULT_MODE) ;
STRING_END : '"' -> popMode ;
