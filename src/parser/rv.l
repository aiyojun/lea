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

long __LEA_LINE__ = 1;
long __LEA_CHAR__ = 0;

int pToken = -1, iToken = -1;
std::string iLine;

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
        {"class"   , yy::parser::token::token_kind_type::CLASS},
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

[\n]                         {__LEA_LINE__++;__LEA_CHAR__ = 0;iLine = "";return yy::parser::token::token_kind_type::NEWLINE;}
" "                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;}
"//"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::LINE_COMMENT;}
"/*"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::COMMENT_BEGIN;}
"*/"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::COMMENT_END;}
";"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::SEMI;}
":"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::COLON;}
","                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::COMMA;}
"{"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::LBP;}
"}"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::RBP;}
"("                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::LP;}
")"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::RP;}
"["                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::LSP;}
"]"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::RSP;}
_?[a-zA-Z_][a-zA-Z0-9_]*     {iLine+=std::string(yytext);set_word(yytext);__LEA_CHAR__ += word.length;return keywords(yytext);}
\"[^\"]*\"                   {iLine+=std::string(yytext);set_word(yytext);__LEA_CHAR__ += word.length;return yy::parser::token::token_kind_type::STR;}
\'[^\']\'                    {iLine+=std::string(yytext);set_word(yytext);__LEA_CHAR__ += word.length;return yy::parser::token::token_kind_type::CHAR;}
([0-9]+\.)?[0-9]+            {iLine+=std::string(yytext);set_word(yytext);__LEA_CHAR__ += word.length;return number(yytext);}
"."                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::DOT;}
"*"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::MUL;}
"/"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::DIV;}
"%"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::MOD;}
"++"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::SADD;}
"+"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::ADD;}
"--"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::SSUB;}
"-"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::SUB;}
"^"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::XOR;}
"=>"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::ARROW;}
"=="                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::EQ;}
"="                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::ASSIGN;}
">="                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::GE;}
"<="                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::LE;}
"<<"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::LSHIFT;}
">>"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::RSHIFT;}
">"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::GT;}
"<"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::LT;}
"&&"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::AND;}
"&"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::BAND;}
"||"                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::OR;}
"|"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::BOR;}
"!="                         {iLine+=std::string(yytext);__LEA_CHAR__ += 2;return yy::parser::token::token_kind_type::NE;}
"!"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::NOT;}
"~"                          {iLine+=std::string(yytext);__LEA_CHAR__ += 1;return yy::parser::token::token_kind_type::ANTI;}
.                            {iLine+=std::string(yytext);__LEA_CHAR__ += 1;}

%%

FlexLexer* lexer = new yyFlexLexer;

int yyFlexLexer::yywrap()
{
    return 0;
}

int yylex(yy::parser::semantic_type* value) {
    int _r = lexer->yylex();

    do {
        if (_r == yy::parser::token::token_kind_type::LINE_COMMENT) {
            while ((_r = lexer->yylex()) != yy::parser::token::token_kind_type::NEWLINE) {}
            _r = lexer->yylex();
        } else if (_r == yy::parser::token::token_kind_type::COMMENT_BEGIN) {
            while ((_r = lexer->yylex()) != yy::parser::token::token_kind_type::COMMENT_END) {}
            _r = lexer->yylex();
        } else if (_r == yy::parser::token::token_kind_type::NEWLINE) {
            _r = lexer->yylex();
        }
    } while (
        _r == yy::parser::token::token_kind_type::LINE_COMMENT  || 
        _r == yy::parser::token::token_kind_type::COMMENT_BEGIN ||
        _r == yy::parser::token::token_kind_type::NEWLINE
    );
/*
    if (pToken == yy::parser::token::token_kind_type::CLASS) {
        std::cout << "word :" << word.ptr <<"\n";
    }

    if (pToken == yy::parser::token::token_kind_type::CLASS 
        && _r == yy::parser::token::token_kind_type::ID) {
        _r = yy::parser::token::token_kind_type::TYPE;
        std::cout << "word :" << word.ptr <<"\n";
    }*/

    pToken = iToken; iToken = _r;

    //std::cout << __LEA_LINE__ << ":" << __LEA_CHAR__ << "\n";
    //std::cout << "iToken: " << iToken << "; pToken: " << pToken << "; ID: " << yy::parser::token::token_kind_type::ID << "; CLASS: " << yy::parser::token::token_kind_type::CLASS << "\n";
    if (pToken == yy::parser::token::token_kind_type::CLASS && iToken == yy::parser::token::token_kind_type::ID) {
        iToken = yy::parser::token::token_kind_type::TYPE;
        std::cout << "New type: " << word.ptr << "\n";
    }

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
    return iToken;
}