%{
#include "rv.yacc.hh"
yy::parser::semantic_type yylval;
#include <string>
#include <map>
#include <deque>
struct Word {
    char *ptr;
    int length;
};

class Space
{
public:
    static std::vector<std::string*> storage;
    static std::string* allocate(char* s)
    {
        std::string *ptr = new std::string(s);
        storage.emplace_back(ptr);
        return ptr;
    }
    static void release()
    {
        for (auto& ptr : storage) 
        {
            delete ptr;
        }
    }
};

std::vector<std::string*> Space::storage;


Word word;
void set_word(const char* p)
{
    std::string *sp = Space::allocate(const_cast<char *>(p));
    word.ptr = const_cast<char *> ((*sp).c_str());
    word.length = (int) sp->length();
}
std::deque<std::string> seq;
yy::parser::token::token_kind_type keywords(const char* word)
{
    std::string iWord(word);
    //std::cout << "[LEX] " << iWord << std::endl;
    static std::map<std::string, yy::parser::token::token_kind_type> mapper {
        {"new"     , yy::parser::token::token_kind_type::NEW},
        {"void"    , yy::parser::token::token_kind_type::TYPE},
        {"bool"    , yy::parser::token::token_kind_type::TYPE},
        {"int"     , yy::parser::token::token_kind_type::TYPE},
        {"byte"    , yy::parser::token::token_kind_type::TYPE},
        {"char"    , yy::parser::token::token_kind_type::TYPE},
        {"float"   , yy::parser::token::token_kind_type::TYPE},
        {"string"  , yy::parser::token::token_kind_type::TYPE},
        {"true"    , yy::parser::token::token_kind_type::TRUE},
        {"false"   , yy::parser::token::token_kind_type::FALSE},
        {"def"     , yy::parser::token::token_kind_type::DEF},
        {"var"     , yy::parser::token::token_kind_type::DEF},
        {"val"     , yy::parser::token::token_kind_type::DEF},
        {"for"     , yy::parser::token::token_kind_type::FOR},
        {"if"      , yy::parser::token::token_kind_type::IF},
        {"else"    , yy::parser::token::token_kind_type::ELSE},
        {"return"  , yy::parser::token::token_kind_type::RETURN},
        {"class"   , yy::parser::token::token_kind_type::DEF},
        {"import"  , yy::parser::token::token_kind_type::IMPORT},
        {"private" , yy::parser::token::token_kind_type::PRIVATE},
        {"static"  , yy::parser::token::token_kind_type::STATIC},
        {"eof"     , yy::parser::token::token_kind_type::ENDING},
        {"EOF"     , yy::parser::token::token_kind_type::ENDING}
    };
    return mapper.find(iWord) != mapper.end() ? mapper[iWord] : yy::parser::token::token_kind_type::ID;
}

yy::parser::token::token_kind_type number(const char* num) {
    std::string iNum(num);
    if (iNum.find('.') != std::string::npos) {
        return yy::parser::token::token_kind_type::FLOAT;
    } else {
        return yy::parser::token::token_kind_type::INT;
    }
}

%}


%%

[\n]                         {}
" "                          {}
";"                          {return yy::parser::token::token_kind_type::SEMI;}
":"                          {return yy::parser::token::token_kind_type::COLON;}
","                          {return yy::parser::token::token_kind_type::COMMA;}
"{"                          {return yy::parser::token::token_kind_type::LBP;}
"}"                          {return yy::parser::token::token_kind_type::RBP;}
"("                          {return yy::parser::token::token_kind_type::LP;}
")"                          {return yy::parser::token::token_kind_type::RP;}
"["                          {return yy::parser::token::token_kind_type::LSP;}
"]"                          {return yy::parser::token::token_kind_type::RSP;}
_?[a-zA-Z_][a-zA-Z0-9_]*     {set_word(yytext);return keywords(yytext);}
\"[^\"]*\"                   {set_word(yytext);return yy::parser::token::token_kind_type::STR;}
\'[^\']\'                    {set_word(yytext);return yy::parser::token::token_kind_type::CHAR;}
([0-9]+\.)?[0-9]+            {set_word(yytext);return number(yytext);}
"."                          {return yy::parser::token::token_kind_type::DOT;}
"*"                          {return yy::parser::token::token_kind_type::MUL;}
"/"                          {return yy::parser::token::token_kind_type::DIV;}
"%"                          {return yy::parser::token::token_kind_type::MOD;}
"++"                         {return yy::parser::token::token_kind_type::SADD;}
"+"                          {return yy::parser::token::token_kind_type::ADD;}
"--"                         {return yy::parser::token::token_kind_type::SSUB;}
"-"                          {return yy::parser::token::token_kind_type::SUB;}
"^"                          {return yy::parser::token::token_kind_type::XOR;}
"=>"                         {return yy::parser::token::token_kind_type::ARROW;}
"=="                         {return yy::parser::token::token_kind_type::EQ;}
"="                          {return yy::parser::token::token_kind_type::ASSIGN;}
">="                         {return yy::parser::token::token_kind_type::GE;}
"<="                         {return yy::parser::token::token_kind_type::LE;}
"<<"                         {return yy::parser::token::token_kind_type::LSHIFT;}
">>"                         {return yy::parser::token::token_kind_type::RSHIFT;}
">"                          {return yy::parser::token::token_kind_type::GT;}
"<"                          {return yy::parser::token::token_kind_type::LT;}
"&&"                         {return yy::parser::token::token_kind_type::AND;}
"&"                          {return yy::parser::token::token_kind_type::BAND;}
"||"                         {return yy::parser::token::token_kind_type::OR;}
"|"                          {return yy::parser::token::token_kind_type::BOR;}
"!="                         {return yy::parser::token::token_kind_type::NE;}
"!"                          {return yy::parser::token::token_kind_type::NOT;}
"~"                          {return yy::parser::token::token_kind_type::ANTI;}

%%

FlexLexer* lexer = new yyFlexLexer;

int yyFlexLexer::yywrap()
{
    return 0;
}

int yylex(yy::parser::semantic_type* value) {
    int _r = lexer->yylex();
    value->ycText = word.ptr;
    std::string text(word.ptr, word.length);
    seq.push_back(text);
    int len = seq.size();
    int max = 10;
    if (len > max) 
    {
        for (int i = 0; i < len - max; i++) {
            seq.pop_front();
        }
    }
    return _r;
}