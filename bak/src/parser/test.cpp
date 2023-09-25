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

    return 0;
}