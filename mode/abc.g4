grammar abc;
WS: [ \t] -> skip;
x: a b? c EOF;
a: '_';
b: '(' '+';
c: '(' '-';

y: y 'a' y | ;