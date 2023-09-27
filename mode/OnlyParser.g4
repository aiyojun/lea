parser grammar OnlyParser;


start: L_BRACE stmts? R_BRACE;
stmts: stmts (SEMI | NEWLINE)+ stmt | stmt;
stmt : assign;
assign: ID EQ expr;
expr:
      PLUS expr
    | expr MUL expr
    | expr PLUS expr
    | NUMBER
    | ID
    ;


