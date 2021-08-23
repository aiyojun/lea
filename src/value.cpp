#include "grammar.h"
#include <string>
#include <vector>
#include <exception>
#include <map>

std::string join(cstring c, const std::vector<std::string>& v)
{std::string _r;for(int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}

template<typename T, typename _>
bool contains(std::map<T, _> map, T key)
{return map.find(key) != map.end();}


class smb {
public:
    int cls;          // class: variable/function
    std::string name;
    std::string type; // int double char string bool
    std::vector<std::string> typeSign; // args type list
}
;
std::string nameTemporary;
smb variable; smb invoking; smb function;

std::vector<std::string> scopeStack;
/** Prepared for yacc */
void enter_scope() {scopeStack.emplace_back(function.name);};
void exit_scope() {scopeStack.pop_back();}
/** Prepared for C++ */
std::string getScope() {return join(".", scopeStack);}

// TODO: scope -> symbol_name -> symbol_info
std::map<std::string, std::map<std::string, smb>> globalDefinedSymbols;
void check(char* name) {if (has_defined(name) == 0) {std::string err; err+=std::string(name)+" already defined"; yyerror(err.c_str());}}
int has_defined(char* name)
{std::string def(name); std::string sco(std::move(getScope()));
 return contains(globalDefinedSymbols, sco) && contains(globalDefinedSymbols[sco], def) ? 0 : 1;}

void keep(char* name) {nameTemporary = std::string(nameTemporary);}
void keep_variable() {variable.name = nameTemporary;}
void keep_variable_type(char* type) {variable.type = std::string(type);}
void keep_function() {function.name = nameTemporary;}
void keep_function_type(char* type) {function.type = std::string(type);}
void keep_function_sign(char* type) {function.typeSign.emplace_back(std::string(type));}
void keep_invoking() {invoking.name = nameTemporary;}

void record_variable() {
    if (has_defined((char *) variable.name.c_str()) == 0) {
        std::string err; err+=variable.name+" already defined";
        yyerror(err.c_str());
    }
    std::string sco(std::move(getScope()));
    if (!contains<std::string>(globalDefinedSymbols, sco)) {
        globalDefinedSymbols[sco] = std::map<std::string, smb>();
    }
    globalDefinedSymbols[sco][variable.name] = variable;
}
void record_function() {
    std::string sco(std::move(getScope()));
    if (!contains<std::string>(globalDefinedSymbols, sco)) {
        globalDefinedSymbols[sco] = std::map<std::string, smb>();
    }
    globalDefinedSymbols[sco][function.name] = function;
}



class factor {
public:
    factor() {}
    factor(cstring n, int t) {usage=1;name=n;}
    factor(cstring v, cstring t) {usage=2;value=v;type=t;}
    int usage = -1;

    std::string name;  // variable/function name

    std::string type;  // int,double,char,string
    std::string value; //
    std::vector<std::string> args_sign;

    static std::string name_tmp2;

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

//int factor::value_deep = 0;
//std::string factor::name_tmp;
std::string factor::name_tmp2;
//std::map<int, factor> factor::invoke_stack;
//std::map<int, std::vector<factor>> factor::deep_stack;
std::vector<std::string> factor::scope_stack{"global"};
std::map<std::string, std::map<std::string, factor>>
factor::symbols{{"global", std::map<std::string, factor>()}};
factor factor::variable;
factor factor::invoking;
factor factor::function;


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

void val_register2(char* name) {
    factor::name_tmp2 = std::string(name);
}

void variable_register(int mode) {
//    factor::variable.usage = 3;
//    factor::variable.mode = mode;
//    factor::variable.name = factor::name_tmp2;
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
//    factor& fa = factor::deep_stack[factor::value_deep][0];
//    if (fa.usage==2&&fa.type=="int") {
//        mov4byte(rt(atoi(fa.value.c_str())), r4("a"));
//    } else if (fa.usage==2&&fa.type=="string") {
//        mov8byte(ptr(declare_ro_data("string", fa.value)), r8("a"));
//    } else if (fa.usage==2&&fa.type=="char") {
//        mov8byte(rt((int) fa.value[0]), r4("a"));
//    } else {
//        yyerror("unimplemented");
//    }
}
void g_function_over() {function_exit();}

void function_push_args_type(char* type) {
    factor::function.args_sign.emplace_back(std::string(type));
}

void function_return(char* type) {
    factor::function.type = std::string(type);
}
