grammar OnlyObjectOriented;


WS: [ \t] -> skip;


ID: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*;
NUMBER: ('0'..'9')+('.' ('0'..'9')+)?;
HEX: '0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+;
OCT: '0' ('o' | 'O') ('0'..'7')+;
BIN: '0' ('b' | 'B') ('0'..'1')+;
CHAR: '\'' (('\u0020'..'\u0026' | '\u0028'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\'))) '\'';
STRING: '"' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '"';


start: decls? semi? EOF;


decls: decls semi+ decl | decl;
decl: defcls | defunc | decvar;


defcls: 'class' nl ID nl '{' nl (members semi)? '}';
members: members semi+ member | member;
member: ('private' | 'protected')? (decvar | defunc);
defunc: 'def' ID ('(' args ')')? (':' ID)? '{' impls '}';
args: args ',' arg | arg | ;
arg: ID ':' ID;


impls: impls semi+ impl | impl;
impl: decvar | defvar | ifstmt tailif? | forstmt | whilestmt | returnstmt | breakstmt | continuestmt | ;


decvar: ('val' | 'var') nl ID nl ((':' nl ID nl ('=' nl rv)?) | ('=' nl rv));
defvar: rv;


ifstmt: ifstmt nl 'else' nl onlyif | onlyif;
onlyif: 'if' nl '(' nl rv nl ')' nl '{' nl impls nl '}';
tailif: 'else' nl '{' nl impls nl '}';
forstmt: 'for' nl '(' nl ((rv nl)? ';' nl (rv nl)? ';' nl rv? | ID nl ':' nl rv) nl ')' nl '{' nl impls nl '}';
whilestmt: 'while' '(' nl rv nl ')' '{' nl impls nl '}';
returnstmt: 'return' nl rv?;
breakstmt: 'break';
continuestmt: 'continue';

//start: rv EOF;
rv: expr;
expr:
    ('!' | '~' | '+' | '-') nl expr
    | expr nl ('*' | '/' | '%') nl expr
    | expr nl ('+' | '-') nl expr
    | expr nl ('>=' | '<=' | '>' | '<') nl expr
    | expr nl ('==' | '!=') nl expr
    | expr nl '&' nl expr
    | '^' nl expr
    | expr nl '|' nl expr
    | expr nl '&&' nl expr
    | expr nl '||' nl expr
    | <assoc=right> expr nl '?' nl expr nl ':' nl expr
    | <assoc=right> expr nl '=' nl expr
    | valexpr
    ;
valexpr:
    autoexpr
    | CHAR
    | STRING
    | BIN
    | OCT
    | HEX
    | NUMBER
    ;
autoexpr: (('++' | '--') nl)? access;
access: access tailaccess | headaccess;
tailaccess: '(' nl valuelist nl ')' | '[' nl rv nl ']' | '.' nl ID | ('++' | '--');
headaccess: '(' nl rv nl ')' | ID;
valuelist: valuelist nl ',' nl rv | rv | ;


nl: '\n'*;
semi: (';' | '\n'+);