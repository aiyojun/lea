#include <iostream>
#include <iomanip>
#include <string>
typedef const std::string& cstring;
#include "lea.h"
#include <vector>
using namespace lea;

int symbolCounter = 0;
void printSymbol(cstring type, cstring name) {
    std::cout << "\r[" << std::setw(3) << ++symbolCounter << "] " << std::setw(8) << type << ", " << name << "\n";
}

int main(int argc, char** argv) {
    LValue* pVal;
    std::vector<LValue *> values {
        LValue::build(TInt, "12"), 
        LValue::build(TChar, "'y'"), 
        LValue::build(TBool, "true"), 
        LValue::build(TFloat, "23.45"),
        LValue::build(TString, "\"This is Text!\""),
        LValue::buildMiddle("int"),
        LValue::buildSymbol("Field0"),
        LValue::build(TFloat, "0"),
        LValue::build(TInt, "0"),
    };

    for (int i = 0; i < values.size(); i++) {
        pVal = values[i];
        switch (pVal->getType()) {
            case ValueType::TInt  : 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getLxInt()->get() << "\n";
                break;
            case ValueType::TChar : 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getLxChar()->get() << "\n";
                break;
            case ValueType::TBool : 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getLxBool()->get() << "\n";
                break;
            case ValueType::TFloat: 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getLxFloat()->get() << "\n";
                break;
            case ValueType::TString: 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getLxString()->get() << "\n";
                break;
            case ValueType::TMiddle: 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getMdValue()->get() << "\n";
                break;
            case ValueType::TSymbol: 
                std::cout << "\r[" << std::setw(3) << i << "] " << std::setw(8) << pVal->getTypeStr() << " | " << pVal->getSmValue()->get() << "\n";
                break;
        }
    }

    // calculation testing
    LValue *p0, *p1, *p3;
    try {
        p0 = values[0]; p1 = values[3]; 
        p3 = LAdd(p0, p1);
        std::cout << p0->getLxNumber() << " + " << p1->getLxNumber() << " = " << p3->getLxNumber() << " " << p3->getTypeStr() << std::endl;
        p3 = LEq(p0, p1);
        std::cout << p0->getLxNumber() << " + " << p1->getLxNumber() << " == " << (p3->getLxBoolean() == 1 ? "true" : "false") << " " << p3->getTypeStr() << std::endl;

        p0 = values[0]; p1 = values[0]; 
        p3 = LAdd(p0, p1);
        std::cout << p0->getLxNumber() << " + " << p1->getLxNumber() << " = " << p3->getLxNumber() << " " << p3->getTypeStr() << std::endl;
        p3 = LEq(p0, p1);
        std::cout << p0->getLxNumber() << " + " << p1->getLxNumber() << " == " << (p3->getLxBoolean() == 1 ? "true" : "false") << " " << p3->getTypeStr() << std::endl;

        p0 = values[8]; p1 = values[7]; 
        p3 = LEq(p0, p1);
        std::cout << p0->getLxNumber() << " + " << p1->getLxNumber() << " == " << (p3->getLxBoolean() == 1 ? "true" : "false") << " " << p3->getTypeStr() << std::endl;
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    // type system testing
    LType* pType;
    std::vector<LType *> types {
        LType::getInt(), 
        LType::getChar(), 
        LType::getBool(), 
        LType::getFloat(),
        LType::getString(),
        LType::buildFlex("MainDemo"),
        LType::buildFlex("StringBuilder"),
        LType::buildLambda()
    };
    for (int i = 0; i < types.size(); i++) {
        std::cout << "Type: " << types[i]->getTypeStr() << std::endl;
    }
    LType::printTable();

    // symbol table testing

    LSymbol* pSymbol;
    std::vector<LSymbol *> symbols {
        LSymbol::build("age", LType::getInt()),
        LSymbol::build("name", LType::getString()),
        LSymbol::build("money", LType::getFloat()),
        LSymbol::build("instance", LType::search("MainDemo"))
    };
    LSymbol::printTable();


    return 0;
}