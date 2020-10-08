grammar Pryst;

options {
	language = Python3;
}
compilationUnit:
	packageDeclaration? importDeclaration* typeDeclaration* EOF;

packageDeclaration: PACKAGE qualifiedName ';';

importDeclaration: IMPORT STATIC? qualifiedName ('.' '*')? ';';

typeDeclaration:
	classModifier* (classDeclaration | enumDeclaration)
	| ';';

modifier: classModifier;

classModifier: PUBLIC | PROTECTED | PRIVATE | STATIC;

classDeclaration:
	CLASS IDENTIFIER typeParameters? (EXTENDS typeType)? classBody;

typeParameters: '<' typeParameter (',' typeParameter)* '>';

typeParameter: IDENTIFIER;

enumDeclaration:
	ENUM IDENTIFIER '{' enumConstants? ','? enumBodyDeclarations? '}';

enumConstants: enumConstant (',' enumConstant)*;

enumConstant: IDENTIFIER arguments? classBody?;

enumBodyDeclarations: ';' classBodyDeclaration*;

classBody: '{' classBodyDeclaration* '}';

classBodyDeclaration:
	';'
	| STATIC? block
	| modifier* memberDeclaration;

memberDeclaration:
	methodDeclaration
	| genericMethodDeclaration
	| fieldDeclaration
	| constructorDeclaration
	| genericConstructorDeclaration
	| classDeclaration
	| enumDeclaration;

/* We use rule this even for void methods which cannot have [] after parameters. This simplifies
 grammar and we can consider void to be a type, which renders the [] matching as a context-sensitive
 issue or a semantic check for invalid return type after parsing.
 */
methodDeclaration:
	typeTypeOrVoid IDENTIFIER formalParameters ('[' ']')* methodBody;

methodBody: block | ';';

typeTypeOrVoid: typeType | VOID;

genericMethodDeclaration: typeParameters methodDeclaration;

genericConstructorDeclaration:
	typeParameters constructorDeclaration;

constructorDeclaration:
	IDENTIFIER formalParameters constructorBody = block;

fieldDeclaration: typeType variableDeclarators ';';

constDeclaration:
	typeType constantDeclarator (',' constantDeclarator)* ';';

constantDeclarator:
	IDENTIFIER ('[' ']')* '=' variableInitializer;

variableDeclarators:
	variableDeclarator (',' variableDeclarator)*;

variableDeclarator:
	variableDeclaratorId ('=' variableInitializer)?;

variableDeclaratorId: IDENTIFIER ('[' ']')*;

variableInitializer: arrayInitializer | expression;

arrayInitializer:
	'{' (variableInitializer (',' variableInitializer)* (',')?)? '}';

classType:
	IDENTIFIER typeArguments? ('.' IDENTIFIER typeArguments?)*;

typeArgument: typeType | '?' ((EXTENDS | SUPER) typeType)?;

qualifiedNameList: qualifiedName (',' qualifiedName)*;

formalParameters: '(' formalParameterList? ')';

formalParameterList:
	formalParameter (',' formalParameter)* (
		',' lastFormalParameter
	)?
	| lastFormalParameter;

formalParameter: typeType variableDeclaratorId;

lastFormalParameter: typeType '...' variableDeclaratorId;

qualifiedName: IDENTIFIER ('.' IDENTIFIER)*;

literal:
	integerLiteral
	| floatLiteral
	| CHAR_LITERAL
	| STRING_LITERAL
	| BOOL_LITERAL
	| NULL_LITERAL;

integerLiteral:
	DECIMAL_LITERAL
	| HEX_LITERAL
	| OCT_LITERAL
	| BINARY_LITERAL;

floatLiteral: FLOAT_LITERAL | HEX_FLOAT_LITERAL;

elementValuePairs: elementValuePair (',' elementValuePair)*;

elementValuePair: IDENTIFIER '=' elementValue;

elementValue: expression | elementValueArrayInitializer;

elementValueArrayInitializer:
	'{' (elementValue (',' elementValue)*)? (',')? '}';

defaultValue: DEFAULT elementValue;

// STATEMENTS / BLOCKS

block: '{' blockStatement* '}';

blockStatement:
	localVariableDeclaration ';'
	| statement
	| localTypeDeclaration;

localVariableDeclaration: typeType variableDeclarators;

localTypeDeclaration: classModifier* classDeclaration | ';';

statement:
	blockLabel = block
	| IF parExpression statement (ELSE statement)?
	| FOR '(' forControl ')' statement
	| WHILE parExpression statement
	| DO statement WHILE parExpression ';'
	| TRY block (catchClause+ finallyBlock? | finallyBlock)
	| TRY resourceSpecification block catchClause* finallyBlock?
	| SWITCH parExpression '{' switchBlockStatementGroup* switchLabel* '}'
	| RETURN expression? ';'
	| THROW expression ';'
	| BREAK IDENTIFIER? ';'
	| CONTINUE IDENTIFIER? ';'
	| SEMI
	| statementExpression = expression ';'
	| identifierLabel = IDENTIFIER ':' statement;

catchClause: CATCH '(' catchType IDENTIFIER ')' block;

catchType: qualifiedName ('|' qualifiedName)*;

finallyBlock: FINALLY block;

resourceSpecification: '(' resources ';'? ')';

resources: resource (';' resource)*;

resource: classType variableDeclaratorId '=' expression;

/** Matches cases then statements, both of which are mandatory. To handle empty cases at the end, we
 * add switchLabel* to statement.
 */
switchBlockStatementGroup: switchLabel+ blockStatement+;

switchLabel:
	CASE (
		constantExpression = expression
		| enumConstantName = IDENTIFIER
	) ':'
	| DEFAULT ':';

forControl:
	enhancedForControl
	| forInit? ';' expression? ';' forUpdate = expressionList?;

forInit: localVariableDeclaration | expressionList;

enhancedForControl:
	typeType variableDeclaratorId ':' expression;

// EXPRESSIONS

parExpression: '(' expression ')';

expressionList: expression (',' expression)*;

methodCall:
	IDENTIFIER '(' expressionList? ')'
	| THIS '(' expressionList? ')'
	| SUPER '(' expressionList? ')';

expression:
	primary
	| expression bop = '.' (
		IDENTIFIER
		| methodCall
		| THIS
		| NEW nonWildcardTypeArguments? innerCreator
		| SUPER superSuffix
		| explicitGenericInvocation
	)
	| expression '[' expression ']'
	| methodCall
	| NEW creator
	| '(' typeType ')' expression
	| expression postfix = ('++' | '--')
	| prefix = ('+' | '-' | '++' | '--') expression
	| prefix = ('~' | '!') expression
	| expression bop = ('*' | '/' | '%') expression
	| expression bop = ('+' | '-') expression
	| expression bop = ('<=' | '>=' | '>' | '<') expression
	| expression bop = ('==' | '!=') expression
	| expression bop = '&' expression
	| expression bop = '^' expression
	| expression bop = '|' expression
	| expression bop = '&&' expression
	| expression bop = '||' expression
	| expression bop = ('<<' | '>>') expression
	| <assoc = right> expression bop = '?' expression ':' expression
	| <assoc = right> expression bop = (
		'='
		| '+='
		| '-='
		| '*='
		| '/='
		| '&='
		| '|='
		| '^='
		| '>>='
		| '<<='
		| '%='
	) expression
	| lambdaExpression;

lambdaExpression: lambdaParameters '=>' lambdaBody;

lambdaParameters:
	IDENTIFIER
	| '(' formalParameterList? ')'
	| '(' IDENTIFIER (',' IDENTIFIER)* ')';

lambdaBody: expression | block;

primary:
	'(' expression ')'
	| THIS
	| SUPER
	| literal
	| IDENTIFIER
	| typeTypeOrVoid '.' CLASS
	| nonWildcardTypeArguments (
		explicitGenericInvocationSuffix
		| THIS arguments
	);

creator:
	nonWildcardTypeArguments createdName classCreatorRest
	| createdName (arrayCreatorRest | classCreatorRest);

createdName:
	IDENTIFIER typeArgumentsOrDiamond? (
		'.' IDENTIFIER typeArgumentsOrDiamond?
	)*
	| primitiveType;

innerCreator:
	IDENTIFIER nonWildcardTypeArgumentsOrDiamond? classCreatorRest;

arrayCreatorRest:
	'[' (
		']' ('[' ']')* arrayInitializer
		| expression ']' ('[' expression ']')* ('[' ']')*
	);

classCreatorRest: arguments classBody?;

explicitGenericInvocation:
	nonWildcardTypeArguments explicitGenericInvocationSuffix;

typeArgumentsOrDiamond: '<' '>' | typeArguments;

nonWildcardTypeArgumentsOrDiamond:
	'<' '>'
	| nonWildcardTypeArguments;

nonWildcardTypeArguments: '<' typeList '>';

typeList: typeType (',' typeType)*;

typeType: (classType | primitiveType) ('[' ']')*;

primitiveType:
	BOOL
	| CHAR
	| BYTE
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE;

typeArguments: '<' typeArgument (',' typeArgument)* '>';

superSuffix: arguments | '.' IDENTIFIER arguments?;

explicitGenericInvocationSuffix:
	SUPER superSuffix
	| IDENTIFIER arguments;

arguments: '(' expressionList? ')';

// Keywords

BOOL: 'bool';
BREAK: 'break';
BYTE: 'byte';
CASE: 'case';
CATCH: 'catch';
CHAR: 'char';
CLASS: 'class';
CONST: 'const';
CONTINUE: 'continue';
DEFAULT: 'default';
DO: 'do';
DOUBLE: 'double';
ELSE: 'else';
ENUM: 'enum';
EXTENDS: 'extends';
FINALLY: 'finally';
FLOAT: 'float';
FOR: 'for';
IF: 'if';
IMPORT: 'import';
INT: 'int';
LONG: 'long';
NEW: 'new';
PACKAGE: 'package';
PRIVATE: 'private'; // private
PROTECTED: 'protected'; // protected
PUBLIC: 'public'; // public
RETURN: 'return';
SHORT: 'short';
STATIC: 'static';
SUPER: 'super';
SWITCH: 'switch';
THIS: 'this';
THROW: 'throw';
TRY: 'try';
VOID: 'void';
WHILE: 'while';

// Literals

DECIMAL_LITERAL: ('0' | [1-9] (Digits? | '_'+ Digits)) [lL]?;
HEX_LITERAL:
	'0' [xX] [0-9a-fA-F] ([0-9a-fA-F_]* [0-9a-fA-F])? [lL]?;
OCT_LITERAL: '0' '_'* [0-7] ([0-7_]* [0-7])? [lL]?;
BINARY_LITERAL: '0' [bB] [01] ([01_]* [01])? [lL]?;

FLOAT_LITERAL: (Digits '.' Digits? | '.' Digits) ExponentPart? [fFdD]?
	| Digits (ExponentPart [fFdD]? | [fFdD]);

HEX_FLOAT_LITERAL:
	'0' [xX] (HexDigits '.'? | HexDigits? '.' HexDigits) [pP] [+-]? Digits [fFdD]?;

BOOL_LITERAL: 'true' | 'false';

CHAR_LITERAL: '\'' (~['\\\r\n] | EscapeSequence) '\'';

STRING_LITERAL: '"' (~["\\\r\n] | EscapeSequence)* '"';
NULL_LITERAL: 'null';
// Separators
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
SEMI: ';';
COMMA: ',';
DOT: '.';
// Operators
ASSIGN: '=';
GT: '>';
LT: '<';
BANG: '!';
TILDE: '~';
QUESTION: '?';
COLON: ':';
EQUAL: '==';
LE: '<=';
GE: '>=';
NOTEQUAL: '!=';
AND: '&&';
OR: '||';
INC: '++';
DEC: '--';
ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
BITAND: '&';
BITOR: '|';
CARET: '^';
MOD: '%';
LSHIFT: '<<';
RSHIFT: '>>';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';
MOD_ASSIGN: '%=';
LSHIFT_ASSIGN: '<<=';
RSHIFT_ASSIGN: '>>=';
// Java 8 tokens
ARROW: '=>';
// Additional symbols not defined in the lexical specification
ELLIPSIS: '...';
// Whitespace and comments
WS: [ \t\r\n\u000C]+ -> channel(HIDDEN);
COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);

// Identifiers

IDENTIFIER: Letter LetterOrDigit*;

// Fragment rules

fragment ExponentPart: [eE] [+-]? Digits;

fragment EscapeSequence:
	'\\' [btnfr"'\\]
	| '\\' ([0-3]? [0-7])? [0-7]
	| '\\' 'u'+ HexDigit HexDigit HexDigit HexDigit;
fragment HexDigits: HexDigit ((HexDigit | '_')* HexDigit)?;
fragment HexDigit: [0-9a-fA-F];
fragment Digits: [0-9] ([0-9_]* [0-9])?;
fragment LetterOrDigit: Letter | [0-9];
fragment Letter:
	[a-zA-Z$_] // these are the "pryst letters" below 0x7F
	| ~[\u0000-\u007F\uD800-\uDBFF] // covers all characters above 0x7F which are not a surrogate
	| [\uD800-\uDBFF] [\uDC00-\uDFFF];
// covers UTF-16 surrogate pairs encodings for U+10000 to U+10FFFF