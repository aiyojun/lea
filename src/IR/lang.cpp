#include "lang.h"
#include <algorithm>


IType *IType::typeVoid    = new IType(LangType::VOID);
IType *IType::typeInt8    = new IType(LangType::INT8);
IType *IType::typeInt16   = new IType(LangType::INT16);
IType *IType::typeInt32   = new IType(LangType::INT32);
IType *IType::typeInt64   = new IType(LangType::INT64);
IType *IType::typeUInt8   = new IType(LangType::UINT8);
IType *IType::typeUInt16  = new IType(LangType::UINT16);
IType *IType::typeUInt32  = new IType(LangType::UINT32);
IType *IType::typeUInt64  = new IType(LangType::UINT64);
IType *IType::typeFloat   = new IType(LangType::FLOAT);
IType *IType::typeDouble  = new IType(LangType::DOUBLE);
IType *IType::typeChar    = new IType(LangType::CHAR);
IType *IType::typeBoolean = new IType(LangType::BOOLEAN);

IArg *IArg::build(const std::string &type, const std::string &name)  {
    auto* arg = new IArg;
    arg->_formalParameterName = name;
    return arg;
}

IFunction *IFunction::build() {
    return new IFunction;
}

VString *Runtime::getConstantString(const std::string &s) {
    if (_constantStringPool.find(s) != _constantStringPool.end())
        return _constantStringPool[s];
    auto p = new VString(s);
    _constantStringPool[s] = p;
    return p;
}

VString *VString::build(const std::string &s) {
    return Runtime::self()->getConstantString(s);
}
