grammar ScriptGrammar;


WS: [ \t\n] -> skip;
SEMI: ';';
NUMBER: ('0'..'9')+('.' ('0'..'9')+)?;
HEX: '0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+;
OCT: '0' ('o' | 'O') ('0'..'7')+;
BIN: '0' ('b' | 'B') ('0'..'1')+;
ID: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*;
STRING
    : ('"' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '"')
    | ('\'' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '\'')
    | ('r' '"' .*? '"')
    ;
BLOCK_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);


program: declarations EOF;
declarations: declarations declarations | classDeclaration | functionDeclaration | variableDeclaration SEMI;


classDeclaration: 'class' ID ('extend' ID | ) '{' (members | ) '}';
members: members members | member;
member: ('private' | 'protected' | 'public' | ) ('static' | ) (functionDeclaration | variableDeclaration SEMI);


variableDeclaration: ID '=' expression;
functionDeclaration: 'def' ID ('(' (params | ) ')' | ) blockStatement;
params: params ',' params | ID;


statements
    : statements statements
    | expression SEMI
    | ifStatement
    | forStatement
    | whileStatement
    | returnStatement SEMI
    | continueStatement SEMI
    | breakStatement SEMI
    | blockStatement
    | SEMI
    ;
blockStatement: '{' (statements | ) '}';


ifStatement: multiIfStatement elseStatement;
multiIfStatement: multiIfStatement 'else' multiIfStatement | 'if' '(' expression ')' blockStatement;
elseStatement: 'else' blockStatement | ;


forStatement: 'for' '(' ((expression | ) SEMI (expression | ) SEMI (expression | ) | expression 'in' expression) ')' blockStatement;
whileStatement: 'while' '(' expression ')' blockStatement;


returnStatement: 'return' (expression | );
continueStatement: 'continue';
breakStatement: 'break';


expression
    : ('!' | '~' | '+' | '-') expression
    | expression ('*' | '/' | '%') expression
    | expression ('+' | '-') expression
    | expression ('>=' | '<=' | '>' | '<') expression
    | expression ('==' | '!=') expression
    | expression '&' expression
    | expression '^' expression
    | expression '|' expression
    | expression '&&' expression
    | expression '||' expression
    | <assoc=right> expression '?' expression ':' expression
    | ('new' ID | ID | '(' expression ')') (accessExpression | )
    | (NUMBER | HEX | OCT | BIN | STRING | 'true' | 'false' | 'null')
    | <assoc=right> expression '=' expression
    ;
accessExpression
    : accessExpression accessExpression
    | '[' expression ']'
    | '(' (arguments | ) ')'
    | '.' ID
    ;
arguments: arguments ',' arguments | expression;


