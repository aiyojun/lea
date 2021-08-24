//
// Created by Mr.Jun on 2021/8/18.
//

#include "grammar.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

std::string file_writer::out;

std::vector<std::string> split(cstring s, cstring separator) {
    std::vector<std::string> _r;
    std::string tmp = s;
    while (tmp.length() > 0) {
        std::string::size_type pos = tmp.find_first_of(separator);
        if (pos > tmp.length() - 1) { if (tmp.length() > 0) _r.emplace_back(tmp);break; }
        if (pos != 0)
            _r.emplace_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos + separator.length());
    }
//    std::cout << "_r: ";
//    for (cstring pp : _r) std::cout << pp << " | ";
//    std::cout << std::endl;
    return std::move(_r);
}

std::vector<std::string> splits(cstring s, const std::vector<std::string>& separators) {
    std::vector<std::string> _r;
    if (separators.empty()) return _r;
    _r = split(s, separators[0]);
    std::vector<std::string> _r2;
    std::vector<std::string> _r3;
    for (int i = 1; i < separators.size(); i++) {
        _r2.clear();
        for (int j = 0; j <_r.size(); j++) {
            _r3 = split(_r[j], separators[i]);
            _r2.insert(_r2.end(), _r3.begin(), _r3.end());
        }
        _r = _r2;
    }
    return std::move(_r);
}

std::string quote(cstring s) {
    if (s[0] != '"' || s[s.length() - 1] != '"') return "\"" + s + "\"";
    return s;
}

class gas {
public:
    static std::vector<std::string> g_text;
    static std::vector<std::string> g_data;
    static std::vector<std::string> g_ro_data;
    static std::vector<std::string> arg_reg;
    static int allocate_ro_data;
    static int xmm_i;
    static int arg_i;
    static int g_branch_i;
    static int bp_i;
    static std::map<std::string, int> stack_i;
    static std::map<std::string, std::string> data_g;
    static std::map<std::string, std::string> bss_g;
};
int gas::allocate_ro_data = 0;
int gas::xmm_i = 0;
int gas::arg_i = 0;
int gas::g_branch_i = 0;
int gas::bp_i = 0;
std::vector<std::string> gas::g_text{".text"};
std::vector<std::string> gas::g_data{".data"};
std::vector<std::string> gas::g_ro_data{".section .rodata"};
std::vector<std::string> gas::arg_reg{"di", "si", "d", "c", "8", "9"};
std::map<std::string, int> gas::stack_i;
std::map<std::string, std::string> gas::data_g;
std::map<std::string, std::string> gas::bss_g;

std::string ptr(cstring label) {return "$"+label;}
std::string ptr_ip(cstring label) {return label+"(%rip)";}
std::string rt(int i) {return "$"+std::to_string(i);}
std::string st(int i) {return "-"+std::to_string(i)+"(%rbp)";}
std::string r1(cstring r) {return  "%"+r+"l";}
std::string rh(cstring r) {return  "%"+r+"h";}
std::string r4(cstring r) {return "%e"+r+"x";}
std::string r8(cstring r) {return "%r"+r+"x";}
std::string rx4(int x) {return "%r"+std::to_string(x)+"d";}
std::string rx8(int x) {return "%r"+std::to_string(x);}
std::string ri4(cstring x) {return "%e"+x;}
std::string ri8(cstring x) {return "%r"+x;}

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
    else if (type == "string") gas::g_ro_data.emplace_back(".string "+ quote(v));
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

/**
 * declare variable in stack
 */
void g_stack_clear(){gas::bp_i=0;gas::stack_i.clear();}
int g_stack_address(cstring name) {
    if (gas::stack_i.find(name) != gas::stack_i.end()) {
        return gas::stack_i[name];
    }
    throw std::runtime_error("no " + name + " in stack");
}
void stack4bytes(cstring name, cstring src) {
    gas::bp_i+=4;
    gas::g_text.emplace_back("movl "+src+","+st(gas::bp_i));
    gas::stack_i[name] = gas::bp_i;
}
void stack8bytes(cstring name, cstring src) {
    gas::bp_i+=8;
    gas::g_text.emplace_back("movl "+src+","+st(gas::bp_i));
    gas::stack_i[name] = gas::bp_i;
}
void stack_double(cstring name, cstring src){
    gas::bp_i+=8;
    double2stack(src, gas::bp_i);
    gas::stack_i[name] = gas::bp_i;
}

void double2stack(cstring ro_, int i)
{gas::g_text.emplace_back("movsd "+ro_+", %xmm0");
gas::g_text.emplace_back("movsd %xmm0,"+st(i));}
void ptr2stack(cstring ro_, int i){gas::g_text.emplace_back("movq "+ro_+","+ st(i));}
void int2stack(int x, int i){gas::g_text.emplace_back("movl "+ rt(x)+","+st(i));}
void byte2stack(int x, int i){int2stack(x, i);}

void args_clear() {gas::xmm_i=0;gas::arg_i=0;}
void mov2xmm(cstring src) {gas::g_text.emplace_back("movsd "+src+",%xmm"+std::to_string(gas::xmm_i++));}
void mov2xmm0(cstring src) {gas::g_text.emplace_back("movsd "+src+",%xmm0");}
void xmm0mov(cstring dest) {gas::g_text.emplace_back("movsd %xmm0,"+dest);}
void mov4byte(cstring src, cstring dest){gas::g_text.emplace_back("movl "+src+","+dest);}
void mov8byte(cstring src, cstring dest){gas::g_text.emplace_back("movq "+src+","+dest);}
void mov4byte2arg(cstring src) {
    if (gas::arg_i < 2)
        gas::g_text.emplace_back("movl "+src+","+ ri4(gas::arg_reg[gas::arg_i]));
    else if (gas::arg_i < 4)
        gas::g_text.emplace_back("movl "+src+","+ r4(gas::arg_reg[gas::arg_i]));
    else if (gas::arg_i < 6)
        gas::g_text.emplace_back("movl "+src+","+ rx4(atoi(gas::arg_reg[gas::arg_i].c_str())));
    else
        yyerror("overflow args reg");
    gas::arg_i++;
}
void mov8byte2arg(cstring src) {
    if (gas::arg_i < 2)
        gas::g_text.emplace_back("movq "+src+","+ ri8(gas::arg_reg[gas::arg_i]));
    else if (gas::arg_i < 4)
        gas::g_text.emplace_back("movq "+src+","+ r8(gas::arg_reg[gas::arg_i]));
    else if (gas::arg_i < 6)
        gas::g_text.emplace_back("movq "+src+","+ rx8(atoi(gas::arg_reg[gas::arg_i].c_str())));
    else
        yyerror("overflow args reg");
    gas::arg_i++;
}

void function_enter(cstring fun_name) {
gas::g_text.emplace_back(".globl "+fun_name);
gas::g_text.emplace_back(fun_name+":");
gas::g_text.emplace_back("pushq %rbp");
gas::g_text.emplace_back("movq %rsp,%rbp");}
void function_exit()
{gas::g_text.emplace_back("popq %rbp");
gas::g_text.emplace_back("ret");}
void function_call(cstring fun_name)
{gas::g_text.emplace_back("call "+fun_name);}



std::string format_gas(cstring stmt) {
    std::vector<std::string> separators{" ", ","};
    std::vector<std::string> stmt_s = splits(stmt, separators);
    if (stmt_s.empty()) throw std::runtime_error("no assemble");
    std::string _r;
    std::string prefix = "    ";
//    std::vector<std::string> declare_label{
//        ".text", ".data", ".globl", ".section",
//        ".string", ".double", ".long",
//        ".size", ".align", ".type"
//    };
//    if (std::find(declare_label.begin(), declare_label.end(), stmt_s[0]) != declare_label.end()) {
//        _r.append(prefix);
//    }
    std::string first = stmt_s[0];
    if (stmt_s.size() == 1 && first[first.length() - 1] == ':') {}
    else {_r.append(prefix);}

    if (stmt_s.size() > 1) {
        char buf[512]{0};
        sprintf(buf, "%-10s", stmt_s[0].c_str());
        _r.append(std::string(buf));
        for (int i = 1; i < stmt_s.size(); i++) {
            sprintf(buf, "%-8s", stmt_s[i].c_str());
            _r.append(std::string(buf));
            if (i + 1 < stmt_s.size()) _r.append(", ");
        }
    } else {
        _r.append(stmt_s[0]);
    }
    return std::move(_r);
}

//#define formatter format_gas
#define formatter

std::string generate_gas() {
    std::string _r;
    for (cstring s : gas::g_data) _r.append(formatter(s)).append("\n");
    for (cstring s : gas::g_text) _r.append(formatter(s)).append("\n");
    for (cstring s : gas::g_ro_data) _r.append(formatter(s)).append("\n");
    return std::move(_r);
}

void print_gas() {
    printf("** gas **\n");
    std::string _r(generate_gas());
    printf("%s\n", _r.c_str());
    if (!file_writer::out.empty()) {
        file_writer writer;
        writer.open(file_writer::out);
        writer.write(_r);
        writer.close();
    }
}