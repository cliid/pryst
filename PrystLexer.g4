lexer grammar PrystLexer;

// Keywords
PRINT: 'print';
CLASS: 'class';
EXTENDS: 'extends';
ELSE: 'else';
FALSE: 'false';
FOR: 'for';
IF: 'if';
NULL: 'null';
RETURN: 'return';
SUPER: 'super';
THIS: 'this';
TRUE: 'true';
WHILE: 'while';
NEW: 'new';
CONVERT: 'convert';
NAMESPACE: 'namespace';
MODULE: 'module';
IMPORT: 'import';
USING: 'using';
LET: 'let';
FN: 'fn';
CONST: 'const';
CONST_EXPR: 'const!';
TRY: 'try';
CATCH: 'catch';

// Types
INT_TYPE: 'int';
FLOAT_TYPE: 'float';
BOOL_TYPE: 'bool';
STR_TYPE: 'str';
VOID_TYPE: 'void';

// Operators and punctuation
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COMMA: ',';
DOT: '.';
MINUS: '-';
PLUS: '+';
SEMICOLON: ';';
SLASH: '/';
STAR: '*';
BANG: '!';
EQUAL: '=';
LESS: '<';
GREATER: '>';
NOT_EQUAL: '!=';
EQUAL_EQUAL: '==';
GREATER_EQUAL: '>=';
LESS_EQUAL: '<=';
AND: '&&';
OR: '||';
INCREMENT: '++';
DECREMENT: '--';
PERCENT: '%';
ARROW: '->';
DOUBLE_COLON: '::';

// Fragments for building other tokens
fragment DIGIT: [0-9];
fragment LETTER: [a-zA-Z];
fragment IDENTIFIER_START: LETTER | '_';
fragment IDENTIFIER_PART: LETTER | DIGIT | '_';

// Literals
NUMBER: DIGIT+ ('.' DIGIT+)?;
IDENTIFIER: IDENTIFIER_START IDENTIFIER_PART*;
STRING: '"' ~["\r\n]* '"';

// String interpolation
STRING_START: '"' -> pushMode(IN_STRING);

// Comments and whitespace
COMMENT: '//' ~[\r\n]* -> skip;
WS: [ \t\r\n]+ -> skip;

// String interpolation mode
mode IN_STRING;
STRING_CONTENT: ~["\\\r\n${]+;
ESCAPE_SEQ: '\\' [btnfr"'\\] | '\\u' [0-9a-fA-F]{4};
INTERP_START: '${' -> pushMode(DEFAULT_MODE);
INTERP_END: '}' -> popMode;
STRING_END: '"' -> popMode;
