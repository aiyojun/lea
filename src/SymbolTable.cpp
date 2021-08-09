//
// Created by Mr.Jun on 2021/8/9.
//
#include "../include/lang/SymbolTable.h"
#include <iomanip>
#include <vector>

SymbolTable::SymbolTable() {}

void SymbolTable::addVar(long line, const std::string& scope, char* name, char* value) {
    std::string n(name);
    Symbol symbol;
    symbol.name = n;
    symbol.lineNo = line;
    symbol.scope = scope;
    symbol.type = SymbolType::Variable;
    symbol.value = value;
    std::string key = n + "::" + scope + "::" + std::to_string(line);
    symbols[key] = symbol;
    keys.emplace_back(key);
}

void SymbolTable::addFunc(long line, const std::string& scope, char* name, FunctionAction action) {
    std::string n(name);
    Symbol symbol;
    symbol.name = n;
    symbol.lineNo = line;
    symbol.scope = scope;
    symbol.type = SymbolType::Function;
    symbol.action = action;
    std::string key = n + "::" + scope + "::" + std::to_string(line);
    symbols[key] = symbol;
    keys.emplace_back(key);
}

//void SymbolTable::addSymbol(char* name, SymbolType type) {
//    std::string n(name);
//    addSymbol(n, type);
//}
//
//void SymbolTable::addSymbol(char* name, SymbolType type, char* value) {
//    std::string n(name);
//    std::string v(value);
//    addSymbol(n, type, v);
//}
//
//void SymbolTable::addSymbol(const std::string& name, const SymbolType& type) {
//    Symbol symbol;
//    symbol.name = name;
//    symbol.type = type;
//    symbols[name] = symbol;
//}
//
//void SymbolTable::addSymbol(const std::string& name, const SymbolType& type, const std::string& value) {
//    Symbol symbol;
//    symbol.name = name;
//    symbol.type = type;
//    symbol.value = value;
//    symbol.hasValue = true;
//    symbols[name] = symbol;
//}

std::string SymbolTable::toString() {
    std::string _r = "** symbol **\nsymbol    type    value\n";
    for (const auto& each : symbols) {
        _r.append(each.first).append("    ")
        .append(toSymbolTypeString(each.second.type)).append("    ")
        .append(each.second.value).append("\n");
    }
    return std::move(_r);
}

void SymbolTable::show() {
    std::cout << "*****************************" << std::endl;
    std::cout << "LEA scope: " << (leaFile.empty() ? "global" : leaFile) << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << "********** SYMBOLS **********" << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << std::setw(15) << std::left << "symbol"
              << std::setw(15) << std::left << "line"
              << std::setw(15) << std::left << "scope"
              << std::setw(15) << std::left << "type"
              << std::setw(15) << std::left << "value"
              << std::setw(15) << std::left << "action"
              << std::endl;
    std::cout << std::setw(15) << std::left << "----"
              << std::setw(15) << std::left << "----"
              << std::setw(15) << std::left << "----"
              << std::setw(15) << std::left << "----"
              << std::setw(15) << std::left << "----"
              << std::setw(15) << std::left << "----"
              << std::endl;
    for (const auto& key : keys) {
        auto& symbol = symbols[key];
        std::cout << std::setw(15) << std::left << symbol.name
        << std::setw(15) << std::left << symbol.lineNo
        << std::setw(15) << std::left << symbol.scope
        << std::setw(15) << std::left << toSymbolTypeString(symbol.type)
        << std::setw(15) << std::left << symbol.value
        << std::setw(15) << std::left << toFunctionActionString(symbol.action)
        << std::endl;
    }
//    for (const auto& each : symbols) {
//        std::cout << std::setw(15) << std::left << each.second.name
//                  << std::setw(15) << std::left << each.second.lineNo
//                  << std::setw(15) << std::left << each.second.scope
//                  << std::setw(15) << std::left << toSymbolTypeString(each.second.type)
//                  << std::setw(15) << std::left << each.second.value
//                  << std::setw(15) << std::left << toFunctionActionString(each.second.action)
//                  << std::endl;
//    }
//    std::cout << this->toString() << std::endl;
}

std::string SymbolTable::toSymbolTypeString(const SymbolType& type) {
    std::string _r;
    switch (type) {
        case SymbolType::Variable:
            _r = "variable";
            break;
        case SymbolType::Function:
            _r = "function";
            break;
        default:
            _r = "unknown";
            break;
    }
    return std::move(_r);
}

std::string SymbolTable::toFunctionActionString(const FunctionAction& type) {
    std::string _r;
    switch (type) {
        case FunctionAction::Def:
            _r = "define";
            break;
        case FunctionAction::Call:
            _r = "call";
            break;
        default:
            _r = "";
            break;
    }
    return std::move(_r);
}

void SymbolTable::lea(char* s) {
    leaFile = s;
}