lexer grammar PrystLexer;

// Basic types
INTEGER: [0-9]+;
FLOAT_LITERAL: [0-9]+ '.' [0-9]+ ([eE][+-]?[0-9]+)?;
BOOLEAN: 'true' | 'false';

// Keywords
INT: 'int';
FLOAT: 'float';
BOOL: 'bool';
STR: 'str';
VOID: 'void';
FN: 'fn';
LET: 'let';
CONST: 'const';
CONST_EXPR: 'const!';
CLASS: 'class';
INTERFACE: 'interface';
EXTENDS: 'extends';
IMPLEMENTS: 'implements';
RETURN: 'return';
IF: 'if';
ELSE: 'else';
WHILE: 'while';
FOR: 'for';
IN: 'in';
IMPORT: 'import';
MODULE: 'module';
TRY: 'try';
CATCH: 'catch';
FINALLY: 'finally';
AS: 'as';
BREAK: 'break';
CONTINUE: 'continue';
NEW: 'new';
MAP: 'map';
FROM: 'from';
THIS: 'this';
NULL_LIT: 'null';
INSTANCEOF: 'instanceof';
TYPEOF: 'typeof';
ERROR: 'error';
CHAIN: 'chain';
PRINT: 'print';
NULL_COALESCE: '??';

PLUS: '+';
MINUS: '-';
STAR: '*';
SLASH: '/';
PERCENT: '%';
ASSIGN: '=';
EQ: '==';
NEQ: '!=';
LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
AND: '&&';
OR: '||';
NOT: '!';
PIPE: '|';
AMP: '&';
QUESTION_MARK: '?';
COLON: ':';
ARROW: '->';
INC: '++';
DEC: '--';

LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
SEMICOLON: ';';
COMMA: ',';
DOT: '.';
DOUBLE_COLON: '::';



IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;

STRING: '"' (~[\\"\r\n] | '\\' .)* '"';
STRING_START: '"' (~[\\${"\r\n] | '\\' .)* '${' -> pushMode(INTERPOLATION);
STRING_MIDDLE: '}' (~[\\${"\r\n] | '\\' .)* '${' -> pushMode(INTERPOLATION);
STRING_END: '}' (~[\\${"\r\n] | '\\' .)* '"' -> popMode;

// Whitespace and comments
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

// Error handling
INVALID_CHAR: . -> skip;
INVALID_IDENTIFIER: [0-9] [a-zA-Z_][a-zA-Z0-9_]* -> skip;

mode INTERPOLATION;
INTERP_WS: [ \t\r\n]+ -> skip;
INTERP_LPAREN: '(' -> type(LPAREN);
INTERP_RPAREN: ')' -> type(RPAREN);
INTERP_PLUS: '+' -> type(PLUS);
INTERP_MINUS: '-' -> type(MINUS);
INTERP_STAR: '*' -> type(STAR);
INTERP_SLASH: '/' -> type(SLASH);
INTERP_DOT: '.' -> type(DOT);
INTERP_COMMA: ',' -> type(COMMA);
INTERP_IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]* -> type(IDENTIFIER);
INTERP_INTEGER: [0-9]+ -> type(INTEGER);
INTERP_STRING: '"' (~[\\"\r\n] | '\\' .)* '"' -> type(STRING);
