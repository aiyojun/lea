//
// Created by root on 2021/8/9.
//

#ifndef LEA_SYMBOLTABLE_H
#define LEA_SYMBOLTABLE_H

#include <map>
#include <string>
#include <iostream>

enum SymbolType {
    Unknown = -1, Variable = 0, Function = 1
};

enum FunctionAction {
    Def = 0, Call
};

struct Symbol {
    std::string name;
    SymbolType  type;
    std::string value;
    bool hasValue = false;
    FunctionAction action;
};

class SymbolTable {
public:
    SymbolTable();
    void addFunc(char* name, FunctionAction action);
    void addSymbol(char* name, SymbolType type);
    void addSymbol(char* name, SymbolType type, char* value);
    void addSymbol(const std::string& name, const SymbolType& type);
    void addSymbol(const std::string& name, const SymbolType& type, const std::string& value);
    std::string toString();
    void show();
private:
    std::string toSymbolTypeString(const SymbolType& type);
    std::string toFunctionActionString(const FunctionAction& type);

    std::map<std::string, Symbol> symbols;
};


#endif //LEA_SYMBOLTABLE_H
