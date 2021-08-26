%{

%}

%%

"//" {
    int c;
    while((c = yyinput()) != 0)
    {
        if(c == '\n')
        {
            yyout.write("\n", 1);
            break;
        }
    }
}
"/*" {
    int c;
    while ((c = yyinput()) != 0)
    {
        if(c == '\n')
        {
            yyout.write("\n", 1);
        }
        else if ( c == '*')
        {
            if((c = yyinput()) == '/')
                break;
            else
                unput(c);
        }
    }
}

%%
int yyFlexLexer::yywrap()
{
    return 1;
}
