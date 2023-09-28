grammar abc;

WS: [ \t\n] -> skip;
NUMBER: ('0'..'9')+('.' ('0'..'9')+)?;
ID: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*;
HEX: '0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+;
OCT: '0' ('o' | 'O') ('0'..'7')+;
BIN: '0' ('b' | 'B') ('0'..'1')+;
CHAR: '\'' (('\u0020'..'\u0026' | '\u0028'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\'))) '\'';
STRING: '"' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '"';
BLOCK_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);


start: decls EOF;
decls: decls decls | declClass | declFunction | declVar;


declClass: 'class' ID '{' (declMembers | ) '}';
declMembers: declMembers declMembers | declMember;
declMember: ('private' | 'protected' | 'public' | ) (declFunction | declVar);


declFunction: 'def' ID ('(' (declTypes | ) ')' | ) (':' ID | ) '{' (stmts | ) '}';
declTypes
    : declTypes ',' declTypes
    | ID ':' ID
    ;


stmts
    : stmts stmts
    | (declVar | expr | ) ';'
    | stmtCondition
    | stmtSwitch
    | stmtFor
    | stmtWhile
    | stmtReturn ';'
    | stmtContinue ';'
    | stmtBreak ';'
    | '{' (stmts | ) '}'
    ;
declVar: ('val' | 'var') ID (':' ID | ) ('=' expr | );


stmtCondition: stmtIf (stmtElseIfs | ) (stmtElse | );
stmtIf: 'if' '(' expr ')' '{' (stmts | ) '}';
stmtElseIfs: stmtElseIfs stmtElseIfs | stmtElseIf;
stmtElseIf: 'else' 'if' '(' expr ')' '{' (stmts | ) '}';
stmtElse: 'else' '{' (stmts | ) '}';


stmtSwitch: 'switch' '(' expr ')' '{' (stmtCases | ) stmtDefault '}';
stmtCases
    : stmtCases stmtCases
    | 'case' (ID | NUMBER | HEX | OCT | BIN | CHAR | STRING) ':' stmts
    ;
stmtDefault: 'default' ':' stmts;


stmtFor: 'for' '(' ((declVar | expr) (';' (expr | ) ';' (expr | ) | ':' expr) | ';' (expr | ) ';' (expr | )) ')' '{' (stmts | ) '}';
stmtWhile: 'while' '(' expr ')' '{' (stmts | ) '}';


stmtReturn: 'return' (expr | );
stmtContinue: 'continue';
stmtBreak: 'break';


expr
    : ('!' | '~' | '+' | '-') expr
    | expr ('*' | '/' | '%') expr
    | expr ('+' | '-') expr
    | expr ('>=' | '<=' | '>' | '<') expr
    | expr ('==' | '!=') expr
    | expr '&' expr
    | '^' expr
    | expr '|' expr
    | expr '&&' expr
    | expr '||' expr
    | <assoc=right> expr '?' expr ':' expr
    | ('++' | '--' | ) (ID | '(' expr ')') (accs | )
    | (NUMBER | STRING | CHAR | HEX | OCT | BIN)
    | <assoc=right> expr '=' expr
    ;
accs
    : accs accs
    | '[' expr ']'
    | '(' (args | ) ')'
    | '.' ID
    | ('++' | '--')
    | 'as' ID
    | 'match' '{' (cases | ) '}'
    ;
args: args ',' args | expr;
cases: cases cases | expr '->' (expr | ) ';';