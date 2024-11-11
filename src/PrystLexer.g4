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
TRY: 'try';
CATCH: 'catch';
AS: 'as';
BREAK: 'break';
CONTINUE: 'continue';
NEW: 'new';
MAP: 'map';
FROM: 'from';
THIS: 'this';
OPEN: 'open';

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

// File operation tokens
FILE: 'File';
READ: 'read';
WRITE: 'write';
READ_TO_STRING: 'readToString';
WRITE_ALL: 'writeAll';
CLOSE: 'close';

IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;

// String handling with interpolation
STRING: '"' -> pushMode(STRING_MODE);

// Whitespace and comments
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;

// String mode for handling interpolation
mode STRING_MODE;
STRING_CONTENT: ~[\\${"\r\n]+;
ESCAPE_SEQUENCE: '\\' ([\\rnt"$] | '{' | '}');
INTERPOLATION_START: '${' -> pushMode(INTERPOLATION_MODE);
QUOTE_END: '"' -> popMode;
STRING_ESCAPE_ERROR: '\\' . -> skip;

// Interpolation mode for handling expressions inside strings
mode INTERPOLATION_MODE;
INTERP_WS: [ \t\r\n]+ -> skip;
INTERP_CONTENT: ~[{}]+;
INTERP_END: '}' -> popMode;

// Error handling
INVALID_CHAR: . -> skip;
INVALID_IDENTIFIER: [0-9] [a-zA-Z_][a-zA-Z0-9_]* -> skip;
