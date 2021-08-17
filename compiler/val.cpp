//
// Created by root on 2021/8/17.
//

#include "syntax.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

using cstring=const std::string&;

std::string join(std::string c, const std::vector<std::string>& v)
{std::string _r;for(int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}

template<typename T, typename _>
bool contains(std::map<T, _> map, T key)
{return map.find(key) != map.end();}

class factor {
public:
    factor(cstring n, int t) {name=n;name_type=t;}
    factor(cstring v, cstring t) {value=v;type=t;}
    std::string name;  // variable/function name
    int name_type = -1;
    int args_size = 0;

    std::string type;  // int,double,char,string
    std::string value; //

    static int value_deep = 0;
    static std::string name_tmp;
    static std::map<int, factor> invoke_stack;
    static std::map<int, std::vector<factor>> deep_stack;

    static std::vector<std::string> scope_stack{"global"};
    static void scope_push(cstring scope) {scope_stack.emplace_back(scope);}
    static void scope_pop() {scope_stack.pop_back();}
    static std::string scope() {return join(".", scope_stack);}

    static std::map<std::string, std::map<std::string, factor>> symbols;
    static bool has_symbol(cstring name)
    {std::string sco(std::move(scope()));return contains<std::string>(symbols,sco)&&contains<std::string>(symbols[sco],name);}

};

void val_register(char* name) {
    factor::name_tmp = std::string(name);
}

void heap_var() {
    factor fa(factor::name_tmp, 0);
    factor::deep_stack[factor::value_deep].emplace_back(factor(fa);
}

void heap_inv() {
    factor fa(factor::name_tmp, 1);
    factor::invoke_stack[factor::value_deep] = fa;
    factor::deep_stack[factor::value_deep].emplace_back(fa);
    factor::value_deep++;
}

void heap_inv_args_inc() {
    factor::invoke_stack[factor::value_deep].args_size++;
}

void heap_value(char* prefix, char* value, char* type) {
    factor::deep_stack[factor::value_deep].emplace_back(factor(std::string(prefix)+std::string(value),std::string(type)));
}

void heap_deep_inc() {factor::value_deep++;}
void heap_deep_dec() {factor::value_deep--;}

void calc_mul() {
    std::vector<factor>& stack_p = factor::deep_stack[factor::value_deep];
    factor& p0 = stack_p[stack_p.size() - 2];
    factor& p1 = stack_p[stack_p.size() - 1];
    
}



