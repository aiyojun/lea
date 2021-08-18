//
// Created by root on 2021/8/18.
//

#include "syntax.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> split(cstring s, cstring separator) {
    std::vector<std::string> _r;
    std::string tmp = s;
    while (tmp.length() > 0) {
        std::string::size_type pos = tmp.find_first_of(separator);
        if (pos > tmp.length() - 1) break;
        if (pos != 0)
            _r.emplace_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos + separator.length());
    }
    return std::move(_r);
}

class gas {
public:

    static std::vector<std::string> g_text;
    static std::vector<std::string> g_data;
    static std::vector<std::string> g_ro_data;
    static int allocate_ro_data;
};
int gas::allocate_ro_data = 0;
std::vector<std::string> gas::g_text{".text"};
std::vector<std::string> gas::g_data{".data"};
std::vector<std::string> gas::g_ro_data{".section .rodata"};

std::string ptr(cstring label) {return "$"+label;}
std::string rt(int i) {return "$"+std::to_string(i);}
std::string st(int i) {return "-"+std::to_string(i)+"(%rbp)";}
std::string r1(cstring r) {return  "%"+r+"l";}
std::string rh(cstring r) {return  "%"+r+"h";}
std::string r4(cstring r) {return "%e"+r+"x";}
std::string r8(cstring r) {return "%r"+r+"x";}
std::string rx4(int x) {return "%r"+std::to_string(x)+"d";}
std::string rx8(int x) {return "%r"+std::to_string(x);}

/**
 * &string => stack
 * @ptr2stack(@ptr(@declare_ro_data("string", "hello")), 8)
 *
 * double  => stack
 * @double2stack(@declare_ro_data("double", "12.12"), 16);
 *
 * integer => stack
 * @int2stack(@rt(24), 20);
 *
 * char    => stack
 * @byte2stack(@rt((int) char), 24);
 */
std::string declare_ro_data(cstring type, cstring v) {
    std::string label = ".LC"+std::to_string(++gas::allocate_ro_data);
    gas::g_ro_data.emplace_back(label+":");
         if (type == "double") gas::g_ro_data.emplace_back(".double "+v);
    else if (type == "string") gas::g_ro_data.emplace_back(".string \""+v+"\"");
    else yyerror(".rodata allocate error!");
    return label;
}
std::string declare_data(cstring type, cstring label, cstring v) {
    gas::g_data.emplace_back(label+":");
    if (type == "double") gas::g_data.emplace_back(".double "+v);
    else if (type == "int") gas::g_data.emplace_back("");
//    else if (type == "string") gas::g_data.emplace_back(".string \""+v+"\"");
    else yyerror(".data allocate error!");
    return label;
}

void double2stack(cstring ro_, int i)
{gas::g_text.emplace_back("movsd "+ro_+", %xmm0");
gas::g_text.emplace_back("movsd %xmm0,"+st(i));}
void ptr2stack(cstring ro_, int i){gas::g_text.emplace_back("movq "+ro_+","+ st(i));}
void int2stack(int x, int i){gas::g_text.emplace_back("movl "+ rt(x)+","+st(i));}
void byte2stack(int x, int i){int2stack(x, i);}

void mov4byte(cstring src, cstring dest){gas::g_text.emplace_back("movl "+src+","+dest);}
void mov8byte(cstring src, cstring dest){gas::g_text.emplace_back("movq "+src+","+dest);}

void call_enter(cstring fun_name) {
gas::g_text.emplace_back(".globl "+fun_name);
gas::g_text.emplace_back(fun_name+":");
gas::g_text.emplace_back("pushq %rbp");
gas::g_text.emplace_back("movq %rsp,%rbp");}
void call_exit()
{gas::g_text.emplace_back("popq %rbp");
gas::g_text.emplace_back("ret");}
void call(cstring fun_name)
{gas::g_text.emplace_back("call "+fun_name);}

std::vector<std::string> splits(cstring s, const std::vector<std::string>& separators) {
    std::vector<std::string> _r;

    return _r;
}

void gas_format(cstring stmt) {

}

void gas_print() {

}
