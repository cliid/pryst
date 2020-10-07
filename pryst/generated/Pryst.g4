grammar Pryst;

options {
	language = Python3;
}

program: function*;

function: functionHead LBRACE functionBody RBRACE;

functionHead: type_ ID LPAREN arguments RPAREN;

arg: type_ ID;
arguments: arg? (',' arg)*;

functionBody: (statement)*;

statement: assignmentStatement | returnStatement | ifStatement;

returnStatement: 'return' expression;

assignmentStatement: type_ ID EQ expression;

ifStatement:
	'if' LPAREN equation RPAREN LBRACE (statement)* RBRACE;

expression:
	functionCall								# expressionFunctionCall
	| expression op = POW expression			# expressionPow
	| expression op = (TIMES | DIV) expression	# expressionMul
	| expression op = (PLUS | MINUS) expression	# expressionAdd
	| LPAREN expression RPAREN					# expressionNested
	| (PLUS | MINUS)* atom						# expressionNumber;

equation: expression op = relop expression;

relop: EQ_EQ | GT | LT;

param: expression;
params: param? (',' param)*;

functionCall: ID LPAREN params RPAREN;

atom: op = INT | op = DECIMAL | op = ID;

type_: 'int' | 'double';

ID: [a-zA-Z]+ DIGIT*;
TIMES: '*';
DIV: '/';
PLUS: '+';
MINUS: '-';
LPAREN: '(';
RPAREN: ')';
POW: '^';
EQ: '=';
EQ_EQ: '==';
LBRACE: '{';
RBRACE: '}';

GT: '>';
LT: '<';

INT: DIGIT+;
DECIMAL: INT '.' INT;

fragment DIGIT: [0-9];
fragment SIGN: (MINUS)?;

WS: [ \r\n\t]+ -> skip;

COMMENT: '/*' .*? '*/' -> skip;

LINE_COMMENT: '//' ~[\r\n]* -> skip;