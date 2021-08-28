#include "grammar.h"
#include <string>
#include <string.h>
#include <vector>
#include <exception>
#include <map>
#include "basic_ds.h"
#include "scope.h"

std::string nameTemporary;
smb variable; smb invoking; smb function;

// TODO: scope -> symbol_name -> symbol_info
std::map<std::string, std::map<std::string, smb>> globalDefinedSymbols{{"global", std::map<std::string, smb>()}};
void check(char* name)
{if (strlen(name) == 0) return; printf("! check [ %s ]\n", name);
 if (has_defined(name) == 0) {std::string err; err+=std::string(name)+" already defined"; yyerror(err.c_str());}}
int has_defined(char* name) {
    std::string def(name); std::string sco(std::move(getScope()));
    if (contains(globalDefinedSymbols, sco)
        && contains(globalDefinedSymbols[sco], def)) {
        return 0;
    } else if (contains(globalDefinedSymbols, sco)
        && !contains(globalDefinedSymbols[sco], def)
        && contains(globalDefinedSymbols["global"], def)) {
        return 0;
    } else return 1;
}

void check_keep() {check((char*) nameTemporary.c_str());}
void keep(char* name) {nameTemporary = std::string(name); variable.clear(); function.clear(); invoking.clear();}
void keep_variable() {variable.name = nameTemporary; variable.cls = 1;}
void keep_variable_type(char* type) {variable.type = std::string(type);}
void keep_function() {function.name = nameTemporary; function.cls = 2;}
void keep_function_type(char* type) {function.type = std::string(type);}
void g_function_enter() {function_enter(function.name);}
void g_function_exit() {function_exit();}
void keep_function_sign(char* type) {function.typeSign.emplace_back(std::string(type));}
void keep_invoking() {invoking.name = nameTemporary;}

const smb& give_variable() {return variable;}
const smb& give_invoking() {return invoking;}
const smb& give_function() {return function;}

const smb& query_smb(cstring name) {
    symbol_print();
    printf("query smb name : %s\n", name.c_str());
    std::string sco(std::move(getScope()));
    if (contains(globalDefinedSymbols, sco)
        && contains(globalDefinedSymbols[sco], name)) {
        return globalDefinedSymbols[sco][name];
    } else if (contains(globalDefinedSymbols, sco)
        && !contains(globalDefinedSymbols[sco], name)
        && contains(globalDefinedSymbols["global"], name)) {
        return globalDefinedSymbols["global"][name];
    } else if (contains(globalDefinedSymbols["global"], name)) {
        return globalDefinedSymbols["global"][name];
    } else throw std::runtime_error("undefined " + name);
}

const smb& query_function(cstring name) {
    std::string sco(std::move(getScope()));
    if (contains(globalDefinedSymbols["global"], name)) {
        return globalDefinedSymbols["global"][name];
    } else throw std::runtime_error("undefined " + name);
}

void record_variable() {
    if (has_defined((char *) variable.name.c_str()) == 0) {
        std::string err; err+=variable.name+" already defined";
        yyerror(err.c_str());
    }
    std::string sco(std::move(getScope()));
    if (!contains<std::string>(globalDefinedSymbols, sco)) {
        globalDefinedSymbols[sco] = std::map<std::string, smb>();
    }
    variable.scope = sco;
    globalDefinedSymbols[sco][variable.name] = variable;

//    if (variable.type == "int") {
//        stack4bytes(variable.name, rt(0));
//    }
}
void record_function() {
    std::string sco(std::move(getScope()));
    printf("scope: %s; function: %s\n", sco.c_str(), function.name.c_str());
    if (!contains<std::string>(globalDefinedSymbols, sco)) {
        globalDefinedSymbols[sco] = std::map<std::string, smb>();
    }
    function.scope = sco;
    globalDefinedSymbols[sco][function.name] = function;
}


void symbol_print() {
    debug_printf("** symbols **\n");
    debug_printf("\033[32;1m%-15s%-15s%-15s%-15s\033[0m\n", "Name", "Scene", "type", "sign");
    debug_printf("\033[32;1m%-15s%-15s%-15s%-15s\033[0m\n", "----", "-----", "----", "----");
    std::map<int, std::string> scenes{
        {3, "variable"}, {4, "function declare"}, {5, "function implement"}
    };

    for (auto& sco_sym : globalDefinedSymbols) {
        debug_printf("[scope] %s\n", sco_sym.first.c_str());
        for (auto& sym : sco_sym.second) {
            std::string type_r = sym.second.type.empty() ? "void" : sym.second.type;
            if (sym.second.cls == 2) {
                debug_printf("%-15s%-15s%-15s%-15s\n",
                             sym.first.c_str(),
                             "function",
                             type_r.c_str(),
                             join(",", sym.second.typeSign).c_str()
                             );
            } else {
                debug_printf("%-15s%-15s%-15s%-15s\n",
                             sym.first.c_str(),
                             "variable",
                             type_r.c_str(),
                             ""
                             );
            }
        }
    }
}


