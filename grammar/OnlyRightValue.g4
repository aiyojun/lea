grammar OnlyRightValue;

WS: [ \t] -> skip;
ID: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '_' | '0'..'9')*;
NUMBER: ('0'..'9')+('.' ('0'..'9')+)?;
HEX: '0' ('x' | 'X') ('0'..'9' | 'a'..'f' | 'A'..'F')+;
OCT: '0' ('o' | 'O') ('0'..'7')+;
BIN: '0' ('b' | 'B') ('0'..'1')+;
CHAR: '\'' (('\u0020'..'\u0026' | '\u0028'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\'))) '\'';
STRING: '"' (('\u0020'..'\u0021' | '\u0023'..'\u007F') | ('\\' ('b' | 't' | 'n' | 'f' | 'r' | '"' | '\'' | '\\')))* '"';

//BIT_OR: '\n'* '|' '\n'*;
//BIT_AND: '&';
//QM: '?';
//MOD: '\n'* '%' '\n'*;
//MUL: '\n'* '*' '\n'*;
//DIV: '\n'* '/' '\n'*;
//INV: '~';
//NOT: '!';
//EQ: '\n'* '==' '\n'*;
//NE: '\n'* '!=' '\n'*;
//GT: '>';
//GE: '>=';
//LT: '<';
//LE: '<=';
//PLUS: '+';
//MINUS: '-';
//INC: '++';
//DEC: '--';
start: impls? semi+;
impls: impls semi+ impl | impl;
impl: decvar | defvar;


defvar: (ID mnl '=' mnl)? rv;
decvar: ('val' | 'var') mnl ID mnl ((':' mnl ID mnl ('=' mnl rv)?) | ('=' mnl rv));



//start: start x | x;
//x: rv (';' | '\n'+);
rv: expr;

expr:
    ('!' | '~' | '+' | '-') mnl expr
    | expr mnl ('*' | '/' | '%') mnl expr
    | expr mnl ('+' | '-') mnl expr
    | expr mnl ('>=' | '<=' | '>' | '<') mnl expr
    | expr mnl ('==' | '!=') mnl expr
    | expr mnl '&' mnl expr
    | '^' mnl expr
    | expr mnl '|' mnl expr
    | expr mnl '&&' mnl expr
    | expr mnl '||' mnl expr
    | expr mnl '?' mnl expr mnl ':' mnl expr
    | valexpr
;
valexpr:
      preexpr
    | jrv
    | CHAR
    | STRING
    | BIN
    | OCT
    | HEX
    | NUMBER
    ;
//    | lambdaimpl
preexpr: ('++' | '--') mnl loopaccessexpr | loopaccessexpr;
loopaccessexpr: loopaccessexpr accesstail | accesshead;
accesshead: '(' mnl rv mnl ')' | ID;
accesstail: '(' mnl valuelist mnl ')' | '[' mnl rv mnl ']' | '.' mnl ID | ('++' | '--');
valuelist: valuelist mnl ',' mnl rv | rv | ;



jrv: '[' mnl valuelist mnl ']' | '{' mnl kvlist mnl '}';
kvlist: kvlist mnl ',' mnl kv | kv;
kv: STRING mnl ':' mnl rv | '[' mnl rv mnl ']' mnl ':' mnl rv;



//lambdaimpl: '(' lambdavaluelist ')' '->' (rv | '{'  '}');
//lambdavaluelist: lambdavaluelist ',' lambdaarg | lambdaarg | ;
//lambdaarg: ID ':' complextype;
//complextype: basictype | ID | lambdatype;
//
//basictype: 'i8' | 'i32' | 'i64' | 'f32' | 'f64' | 'string' | 'char' | 'bool' | 'void';
//lambdatype: '(' typelist ')' '->' complextype;
//typelist: typelist ',' complextype | complextype | ;
//
//
//optnl: '\n'*;
mnl: '\n'*;
semi: (';' | '\n'+);
