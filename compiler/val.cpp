//
// Created by root on 2021/8/17.
//

#include "syntax.h"
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <map>

#define debug_printf printf_empty

using cstring=const std::string&;

std::string join(cstring c, const std::vector<std::string>& v)
{std::string _r;for(int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}

template<typename T, typename _>
bool contains(std::map<T, _> map, T key)
{return map.find(key) != map.end();}

class factor {
public:
    factor() {}
//    factor(cstring n) {usage=3;name=n;}
    factor(cstring n, int t) {usage=1;name=n;name_type=t;}
    factor(cstring v, cstring t) {usage=2;value=v;type=t;}
    int usage = -1;
    int mode = 0; // declare/use variable

    std::string name;  // variable/function name
    int name_type = -1;
    int args_size = 0;

    std::string type;  // int,double,char,string
    std::string value; //
    std::vector<std::string> args_sign;

    static int value_deep;
    static std::string name_tmp;
    static std::string name_tmp2;
    static std::map<int, factor> invoke_stack;
    static std::map<int, std::vector<factor>> deep_stack;

    static std::vector<std::string> scope_stack;
    static void scope_push(cstring scope) {scope_stack.emplace_back(scope);}
    static void scope_pop() {scope_stack.pop_back();}
    static std::string scope() {return join(".", scope_stack);}

    static std::map<std::string, std::map<std::string, factor>> symbols;
    static bool has_symbol(cstring name)
    {std::string sco(std::move(scope()));return contains<std::string>(symbols,sco)&&contains<std::string>(symbols[sco],name);}

    static factor variable;
    static factor function;
    static factor invoking;
};

int factor::value_deep = 0;
std::string factor::name_tmp;
std::string factor::name_tmp2;
std::map<int, factor> factor::invoke_stack;
std::map<int, std::vector<factor>> factor::deep_stack;
std::vector<std::string> factor::scope_stack{"global"};
std::map<std::string, std::map<std::string, factor>>
    factor::symbols{{"global", std::map<std::string, factor>()}};
factor factor::variable;
factor factor::invoking;
factor factor::function;

void stack_clear() {
    factor::value_deep = 0;
    factor::name_tmp = "";
    factor::name_tmp2 = "";
    factor::invoke_stack.clear();
    factor::deep_stack.clear();
}

void record_symbol(factor& fa) {
    std::string sco(std::move(factor::scope()));
    if (!contains<std::string>(factor::symbols, sco)) {
        factor::symbols[sco] = std::map<std::string, factor>();
        factor::symbols[sco][fa.name] = fa;
    } else {
        if (contains<std::string>(factor::symbols[sco], fa.name)) {
            yyerror(("symbol " + fa.name + " already exist.").c_str());
        } else {
            factor::symbols[sco][fa.name] = fa;
        }
    }
}

void val_register(char* name) {
    factor::name_tmp = std::string(name);
}

void val_register2(char* name) {
    factor::name_tmp2 = std::string(name);
}

void function_record() {
    record_symbol(factor::function);
}

void function_name(char* name) {
    factor::function.usage = 4; // function declare
    factor::function.name = std::string(name);
}

void function_type(int usage) {
    if (usage != 4 && usage != 5) yyerror("Unsupported function type!");
    factor::function.usage = usage; // 5: function declare + implement
}

void g_function_imp() {function_enter(factor::function.name);}
void g_function_return() {
    factor& fa = factor::deep_stack[factor::value_deep][0];
    if (fa.usage==2&&fa.type=="int") {
        mov4byte(rt(atoi(fa.value.c_str())), r4("a"));
    } else if (fa.usage==2&&fa.type=="string") {
        mov8byte(ptr(declare_ro_data("string", fa.value)), r8("a"));
    } else if (fa.usage==2&&fa.type=="char") {
        mov8byte(rt((int) fa.value[0]), r4("a"));
    } else {
        yyerror("unimplemented");
    }
}
void g_function_over() {function_exit();}

void function_push_args_type(char* type) {
    factor::function.args_sign.emplace_back(std::string(type));
}

void function_return(char* type) {
    factor::function.type = std::string(type);
}

void variable_register(int mode) {
    factor::variable.usage = 3;
    factor::variable.mode = mode;
    factor::variable.name = factor::name_tmp2;
}

void variable_type(char* type) {
    factor::variable.type = std::string(type);
}

void variable_record() {
    record_symbol(factor::variable);
}

void variable_assign_v2() {

}

void variable_already_exist() {
//    debug_printf(">> %s\n", factor::variable.name.c_str());
    std::string sco(std::move(factor::scope()));
    if (sco != "global" && contains<std::string>(factor::symbols, sco)
            && contains<std::string>(factor::symbols[sco], factor::variable.name)
            && factor::symbols[sco][factor::variable.name].usage == 3) {
        return;
    }
    if (contains<std::string>(factor::symbols["global"], factor::variable.name)) {
        return;
    }
    yyerror(("undefined variable " + factor::variable.name).c_str());
}

//void invoking_register() {
//    factor::variable.usage = 4;
//    factor::variable.name = factor::name_tmp2;
//}
//
//void invoking_type(char* type) {
//    factor::variable.type = std::string(type);
//}
//
//void invoking_exe() {
//
//}


void symbol_print() {
    debug_printf("** symbols **\n");
    debug_printf("\033[32;1m%-15s%-20s%-15s\033[0m\n", "Name", "Scene", "sign");
    debug_printf("\033[32;1m%-15s%-20s%-15s\033[0m\n", "----", "-----", "----");
    std::map<int, std::string> scenes{
        {3, "variable"}, {4, "function declare"}, {5, "function implement"}
    };

    for (auto& sco_sym : factor::symbols) {
        debug_printf("[scope] %s\n", sco_sym.first.c_str());
        for (auto& sym : sco_sym.second) {
            std::string signs = sym.second.type;
            if (signs == "") {signs = "void";}
            signs += " : ";
            if (sym.second.usage == 4) {
                for (std::string s : sym.second.args_sign) {
                    signs.append(s).append(" | ");
                }
                debug_printf("%-15s%-20s%-15s\n",
                       sym.first.c_str(),
                       scenes[sym.second.usage].c_str(),
                       signs.c_str()
                       );
            } else {
                debug_printf("%-15s%-20s%-15s\n",
                       sym.first.c_str(),
                       scenes[sym.second.usage].c_str(),
                       signs.c_str()
                       );
            }
        }
    }
}

void heap_print() {
    debug_printf("invoke : ");
    for (auto& p : factor::invoke_stack) {
        debug_printf("%d:%s | ", p.first, p.second.name.c_str());
    }
    debug_printf("\n");
    for (const auto& stack : factor::deep_stack) {
        debug_printf("stack#%d#%d: ", stack.first, stack.second.size());
        for (const auto& item : stack.second) {
            debug_printf("%s | ", item.usage==2?item.value.c_str():item.name.c_str());
        }
        debug_printf("\n");
    }
    debug_printf("---\n");
}

void heap_var_validate() {
    std::string sym_name = factor::name_tmp;
    std::string sco(std::move(factor::scope()));
    if (sco != "global" && contains<std::string>(factor::symbols, sco)
    && contains<std::string>(factor::symbols[sco], sym_name)
    && factor::symbols[sco][sym_name].usage == 3) {
        return;
    }
    if (contains<std::string>(factor::symbols["global"], sym_name)) {
        return;
    }
    yyerror(("undefined variable " + sym_name).c_str());
}

void heap_inv_validate() {
    std::string sym_name = factor::name_tmp;
    std::string sco = "global";
    if (contains<std::string>(factor::symbols["global"], sym_name)
    && (factor::symbols[sco][sym_name].usage == 4 || factor::symbols[sco][sym_name].usage == 5)) {
        return;
    }
    yyerror(("undefined function " + sym_name).c_str());
}

void heap_var() {
    factor fa(factor::name_tmp, 0);
    // TODO: query symbol table to get type sign
    factor::deep_stack[factor::value_deep].emplace_back(fa);
    heap_print();
}

void heap_inv() {
    factor fa(factor::name_tmp, 1);
    // TODO: query symbol table to get type sign
    factor::invoke_stack[factor::value_deep] = fa;
    factor::deep_stack[factor::value_deep].emplace_back(fa);
//    factor::value_deep++;
//    debug_printf("--02 deep: %d\n", factor::value_deep);
    heap_print();
}

void heap_inv2() {
    factor::name_tmp = factor::name_tmp2;
//    debug_printf("## -> %d\n", factor::value_deep);
//    factor fa(factor::name_tmp2, 1);
//    // TODO: query symbol table to get type sign
//    factor::invoke_stack[factor::value_deep] = fa;
//    factor::deep_stack[factor::value_deep].emplace_back(fa);
//    heap_print();
    heap_inv();
}

void heap_inv_exe() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& fun = factor::invoke_stack[factor::value_deep-1];
    debug_printf("** exec fun: %s ; deep: %d ; args: %d\n", fun.name.c_str(), factor::value_deep, fun.args_size);
//    int hasDouble = 0;
    for (int i = 0; i < fun.args_size; i++) {
        unsigned int j = stack_p.size() - (fun.args_size - i);
        factor p = stack_p[j];
        if (p.usage == 2) {
            args_clear();
            if (p.type == "double") {
                mov2xmm(declare_ro_data("double", p.value));
            } else if (p.type == "string") {
                mov8byte2arg(ptr(declare_ro_data("string", p.value)));
            } else if (p.type == "int") {
                mov4byte2arg(rt(atoi(p.value.c_str())));
            } else if (p.type == "char") {
                mov4byte2arg(rt((int) p.value[0]));
            } else {
                yyerror("unsupported type at present.");
            }
        } else {
            yyerror("non-support now.");
        }
    }
    function_call(fun.name);

    for (int i = 0; i < fun.args_size; i++) {
        stack_p.pop_back();
    }
    factor::invoke_stack.erase(factor::value_deep-1);
}

void heap_inv_args_inc() {
    factor::invoke_stack[factor::value_deep-1].args_size++;
}

void heap_value(char* prefix, char* value, char* type) {
//    debug_printf("--01 deep: %d\n", factor::value_deep);
    factor::deep_stack[factor::value_deep]
        .emplace_back(factor(std::string(prefix)+std::string(value),std::string(type)));
    heap_print();
}

void heap_deep_inc() {factor::value_deep++;}
void heap_deep_dec() {factor::value_deep--;}

void calc_mul() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&p0.type=="int"&&p1.type=="int") {
        int r = atoi(p0.value.c_str()) * atoi(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "int"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        double r = atof(p0.value.c_str()) * atof(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "double"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void calc_div() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&p0.type=="int"&&p1.type=="int") {
        int r = atoi(p0.value.c_str()) / atoi(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "int"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        double r = atof(p0.value.c_str()) / atof(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "double"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void calc_add() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&p0.type=="int"&&p1.type=="int") {
        int r = atoi(p0.value.c_str()) + atoi(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "int"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        double r = atof(p0.value.c_str()) + atof(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "double"));
        return;
    }
    if (p0.usage==1) {
        std::string name = p0.name;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(name, 1));
        return;
    }
    if (p1.usage==1) {
        std::string name = p1.name;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(name, 1));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void calc_sub() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&p0.type=="int"&&p1.type=="int") {
        int r = atoi(p0.value.c_str()) - atoi(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "int"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        double r = atof(p0.value.c_str()) - atof(p1.value.c_str());
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "double"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_gt() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="double")&&(p1.type=="int"||p1.type=="double"))) {
        int r = atof(p0.value.c_str()) - atof(p1.value.c_str()) > 0 ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_gte() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="double")&&(p1.type=="int"||p1.type=="double"))) {
        int r = atof(p0.value.c_str()) - atof(p1.value.c_str()) >= 0 ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_lt() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="double")&&(p1.type=="int"||p1.type=="double"))) {
        int r = atof(p0.value.c_str()) - atof(p1.value.c_str()) < 0 ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_lte() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="double")&&(p1.type=="int"||p1.type=="double"))) {
        int r = atof(p0.value.c_str()) - atof(p1.value.c_str()) <= 0 ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_eq() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="bool")&&(p1.type=="int"||p1.type=="bool"))) {
        int r = atoi(p0.value.c_str()) == atoi(p1.value.c_str()) ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        int r = atof(p0.value.c_str()) == atof(p1.value.c_str()) ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="string"||p1.type=="string")) {
        int r = p0.value == p1.value ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="string"||p1.type=="string")) {
        int r = p0.value[0] == p1.value[0] ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_ne() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&p1.usage==2&&((p0.type=="int"||p0.type=="bool")&&(p1.type=="int"||p1.type=="bool"))) {
        int r = atoi(p0.value.c_str()) != atoi(p1.value.c_str()) ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="double"||p1.type=="double")) {
        int r = atof(p0.value.c_str()) != atof(p1.value.c_str()) ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="string"||p1.type=="string")) {
        int r = p0.value != p1.value ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    if (p0.usage==2&&p1.usage==2&&(p0.type=="string"||p1.type=="string")) {
        int r = p0.value[0] != p1.value[0] ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_not() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&(p0.type=="int"||p0.type=="bool")) {
        int r = atoi(p0.value.c_str()) == 0 ? 1 : 0;
        stack_p.pop_back(); stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_and() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&(p0.type=="int"||p0.type=="bool")) {
        int r = atoi(p0.value.c_str())!=0&&atoi(p1.value.c_str())!=0 ? 1 : 0;
        stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

void comp_or() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    if (p0.usage==2&&(p0.type=="int"||p0.type=="bool")) {
        int r = atoi(p0.value.c_str())!=0||atoi(p1.value.c_str())!=0 ? 1 : 0;
        stack_p.pop_back();
        stack_p.emplace_back(factor(std::to_string(r), "bool"));
        return;
    }
    throw std::runtime_error("undefined operation");
}

