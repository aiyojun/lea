//
// Created by root on 2021/8/9.
//
#include "../include/SymbolTable.h"
#include <iomanip>

SymbolTable::SymbolTable() {}

void SymbolTable::addFunc(char* name, FunctionAction action) {
    std::string n(name);
    Symbol symbol;
    symbol.name = n;
    symbol.type = SymbolType::Function;
    symbol.action = action;
    symbols[n] = symbol;
}

void SymbolTable::addSymbol(char* name, SymbolType type) {
    std::string n(name);
    addSymbol(n, type);
}

void SymbolTable::addSymbol(char* name, SymbolType type, char* value) {
    std::string n(name);
    std::string v(value);
    addSymbol(n, type, v);
}

void SymbolTable::addSymbol(const std::string& name, const SymbolType& type) {
    Symbol symbol;
    symbol.name = name;
    symbol.type = type;
    symbols[name] = symbol;
}

void SymbolTable::addSymbol(const std::string& name, const SymbolType& type, const std::string& value) {
    Symbol symbol;
    symbol.name = name;
    symbol.type = type;
    symbol.value = value;
    symbol.hasValue = true;
    symbols[name] = symbol;
}

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
    std::cout << "********** SYMBOLS **********" << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << std::setw(15) << std::left << "symbol"
              << std::setw(15) << std::left << "type"
              << std::setw(15) << std::left << "value"
              << std::setw(15) << std::left << "action"
              << std::endl;
    std::cout << std::setw(15) << std::left << "----"
    << std::setw(15) << std::left << "----"
    << std::setw(15) << std::left << "----"
    << std::setw(15) << std::left << "----"
    << std::endl;
    for (const auto& each : symbols) {
        std::cout << std::setw(15) << std::left << each.first
                  << std::setw(15) << std::left << toSymbolTypeString(each.second.type)
                  << std::setw(15) << std::left << each.second.value
                  << std::setw(15) << std::left << toFunctionActionString(each.second.action)
                  << std::endl;
    }
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