grammar abc;

WS: [ \t\n] -> skip;
//NUMBER: ('0'..'9')+('.' ('0'..'9')+)?;
NUMBER: (('0'..'9')+('.' ('0'..'9')+)?) | ('0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+) | ('0' ('o' | 'O') ('0'..'7')+) | ('0' ('b' | 'B') ('0'..'1')+);
ID: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*;
//HEX: '0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+;
//OCT: '0' ('o' | 'O') ('0'..'7')+;
//BIN: '0' ('b' | 'B') ('0'..'1')+;
//CHAR: '\'' (('\u0020'..'\u0026' | '\u0028'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\'))) '\'';
STRING: ('"' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '"')
    | ('\'' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '\'')
    | ('r' '"' .*? '"')
    ;
BLOCK_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);


prog: decls EOF;
decls: decls decls | declClass | declFunction | declVar ';';


declClass: 'class' ID ('extend' ID | ) '{' (declMembers | ) '}';
declMembers: declMembers declMembers | declMember;
declMember: ('private' | 'protected' | 'public' | ) ('static' | ) (declFunction | declVar ';');


//declFunction: 'def' ID ('(' (declArgs | ) ')' | ) (':' ID | ) '{' (stmts | ) '}';
declFunction: 'def' ID ('(' (declArgs | ) ')' | ) '{' (stmts | ) '}';
declArgs
    : declArgs ',' declArgs
    | ID //':' (ID | 'i8' | 'i32' | 'i64' | 'f32' | 'f64' | 'string' | 'boolean')
    ;


stmts
    : stmts stmts
//    | (declVar | expr | ) ';'
    | (declVar | expr | ) ';'
    | stmtCondition
//    | stmtSwitch
    | stmtFor
    | stmtWhile
    | stmtReturn ';'
    | stmtContinue ';'
    | stmtBreak ';'
    | '{' (stmts | ) '}'
    ;

//declVar: ('val' | 'var') ID (':' ID | ) ('=' expr | );
declVar: ID '=' expr;


stmtCondition: stmtIf (stmtElseIfs | ) (stmtElse | );
stmtIf: 'if' '(' expr ')' '{' (stmts | ) '}';
stmtElseIfs: stmtElseIfs stmtElseIfs | stmtElseIf;
stmtElseIf: 'else' 'if' '(' expr ')' '{' (stmts | ) '}';
stmtElse: 'else' '{' (stmts | ) '}';


//stmtSwitch: 'switch' '(' expr ')' '{' (stmtCases | ) stmtDefault '}';
//stmtCases
//    : stmtCases stmtCases
//    | 'case' (ID | NUMBER | HEX | OCT | BIN | CHAR | STRING) ':' stmts
//    ;
//stmtDefault: 'default' ':' stmts;


//stmtFor: 'for' '(' ((declVar | expr | ) ';' (expr | ) ';' (expr | ) | declVar 'in' expr) ')' '{' (stmts | ) '}';
stmtFor: 'for' '(' ((expr | ) ';' (expr | ) ';' (expr | ) | expr 'in' expr) ')' '{' (stmts | ) '}';
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
//    | ('++' | '--' | ) (ID | '(' expr ')') (accs | )
    | ('new' ID | ID | '(' expr ')') (accs | )
//    | (NUMBER | STRING | CHAR | HEX | OCT | BIN | 'true' | 'false' | 'null')
    | (NUMBER | STRING | 'true' | 'false' | 'null')
    | <assoc=right> expr '=' expr
    ;
accs
    : accs accs
    | '[' expr ']'
    | '(' (args | ) ')'
    | '.' ID
//    | ('++' | '--')
//    | 'as' ID
//    | 'match' '{' (cases | ) '}'
    ;
args: args ',' args | expr;
//cases: cases cases | expr '->' (expr | ) ';';