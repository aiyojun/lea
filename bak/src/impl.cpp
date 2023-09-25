#include "lea.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace lea {

std::string join(const std::vector<std::string>& v, std::string s) {
    std::string _r;
    for (int i = 0; i < v.size(); i++) {
        if (i != 0) _r += s; 
        _r += v[i];
    }
    return std::move(_r);
}

std::vector<std::string> merge(const std::vector<std::string>& v0, const std::vector<std::string>& v1) {
    std::vector<std::string> _r(v0.size() + v1.size());
    _r.insert(_r.end(), v0.begin(), v0.end());
    _r.insert(_r.end(), v1.begin(), v1.end());
    return std::move(_r);
}




SmValue::SmValue(): v(), scope() {setType(TSymbol);}
void SmValue::set(cstring s) {v = s;}
void SmValue::setScope(const std::vector<std::string>& sco) {scope = sco;}
std::vector<std::string>& SmValue::getScope() {return scope;}
std::string SmValue::get() {return join(merge(scope, {v}), ".");}


int MdValue::uuid = 0;
MdValue::MdValue(): v("Middle$" + std::to_string(++uuid)) {setType(TMiddle);}
void MdValue::setTypeSign(cstring sign) {typeSign = sign;}
std::string MdValue::get() {return v + "@" + typeSign;}


int LxString::uuid = 0;
std::map<int, std::string> LxString::constPool;
LxString::LxString(): index(-1) {setType(TString);}
void LxString::set(cstring s) {
    index = (++uuid);
    LxString::constPool[index] = s.substr(1, s.length() - 2);
}
void LxString::setV(std::string s) {
    index = (++uuid);
    LxString::constPool[index] = std::move(s);
}
std::string LxString::get() {
    return LxString::constPool[index];
}
std::string LxString::getAlias() {
    return "String$" + index;
}



#define IMP_LX_VALUE(clazz, T, VT, setter) \
clazz::clazz() {setType(VT);}\
void clazz::set(cstring s) {setter;}\
void clazz::setV(T x) {v = x;}\
T clazz::get() {return v;}

IMP_LX_VALUE(LxInt, int, TInt, v = std::stoi(s))
IMP_LX_VALUE(LxChar, char, TChar, v = s[1])
IMP_LX_VALUE(LxBool, bool, TBool, v = s == "true")
IMP_LX_VALUE(LxFloat, double, TFloat, v = std::stod(s))




void LValue::setType(ValueType vt) {type = vt;}
ValueType LValue::getType() { return type; }
std::string LValue::getTypeStr() {
    switch (type) {
        case ValueType::TByte  : return "byte";
        case ValueType::TChar  : return "char";
        case ValueType::TBool  : return "bool";
        case ValueType::TInt   : return "int";
        case ValueType::TFloat : return "float";
        case ValueType::TString: return "string";
        case ValueType::TSymbol: return "symbol";
        case ValueType::TMiddle: return "middle";
    }
    throw std::runtime_error("unknown type");
}
LValue* LValue::build(ValueType vt, cstring va) {
    LValue *pVal;
    switch (vt) {
        case ValueType::TChar  :
            pVal = new LxChar();
            reinterpret_cast<LxChar*>(pVal)->set(va);
            break;
        case ValueType::TBool  :
            pVal = new LxBool();
            reinterpret_cast<LxBool*>(pVal)->set(va);
            break;
        case ValueType::TInt   :
            pVal = new LxInt();
            reinterpret_cast<LxInt*>(pVal)->set(va);
            break;
        case ValueType::TFloat :
            pVal = new LxFloat();
            reinterpret_cast<LxFloat*>(pVal)->set(va);
            break;
        case ValueType::TString:
            pVal = new LxString();
            reinterpret_cast<LxString*>(pVal)->set(va);
            break;
        default: throw std::runtime_error("unknown type");
    }
    return pVal;
}

#define IMPL_BUILD_TYPE(K, T) \
Lx##K *LValue::build##K(T x) {\
    Lx##K *p = new Lx##K();\
    p->setV(x);\
    return p;\
}

IMPL_BUILD_TYPE(Int, int)
IMPL_BUILD_TYPE(Char, char)
IMPL_BUILD_TYPE(Bool, bool)
IMPL_BUILD_TYPE(Float, double)
IMPL_BUILD_TYPE(String, std::string)

MdValue* LValue::buildMiddle(cstring type) {
    MdValue* p = new MdValue();
    p->setTypeSign(type);
    return p;
}
SmValue* LValue::buildSymbol(cstring symbol, const std::vector<std::string>& scope) {
    SmValue* p = new SmValue();
    p->set(symbol);
    p->setScope(scope);
    return p;
}
bool LValue::isLxChar() {return getType() == TChar;}
bool LValue::isLxString() {return getType() == TString;}
bool LValue::isLxInt() {return getType() == TInt;}
bool LValue::isLxBoolean() 
{return getType() == TBool || getType() == TInt || getType() == TFloat;}
bool LValue::getLxBoolean() {
    switch (getType()) {
        case TBool : return getLxBool()->get();
        case TInt  : return getLxInt()->get() != 0;
        case TFloat: return getLxFloat()->get() != .0;
    }
    throw std::runtime_error(getTypeStr() + " is non boolean!");
}
bool LValue::isLxNumber() 
{return getType() == TInt || getType() == TFloat;}
double LValue::getLxNumber() {
    if (getType() == TInt) return getLxInt()->get();
    if (getType() == TFloat) return getLxFloat()->get();
    throw std::runtime_error(getTypeStr() + " can't getLxNumber!");
}
bool LValue::isLxCharSeq() 
{return getType() == TChar || getType() == TString;}
std::string LValue::getLxCharSeq() {
    if (getType() == TChar) return "" + getLxChar()->get();
    if (getType() == TString) return getLxString()->get();
    throw std::runtime_error(getTypeStr() + " can't getLxCharSeq!");
}
bool LValue::isRef()
{return getType() == TMiddle || getType() == TSymbol;}

#define IMPL_GET_REAL_VALUE(clazz, vt) \
clazz* LValue::get##clazz() {\
    if (getType() != vt) throw std::runtime_error("Wrong type");\
    return reinterpret_cast<clazz*>(this);\
}

IMPL_GET_REAL_VALUE(LxInt, TInt)
IMPL_GET_REAL_VALUE(LxChar, TChar)
IMPL_GET_REAL_VALUE(LxBool, TBool)
IMPL_GET_REAL_VALUE(LxFloat, TFloat)
IMPL_GET_REAL_VALUE(LxString, TString)
IMPL_GET_REAL_VALUE(MdValue, TMiddle)
IMPL_GET_REAL_VALUE(SmValue, TSymbol)

bool isLxType(LValue *p) {return p->getType() >= TByte && p->getType() <= TString;}

LValue* LAdd(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt()->get() + p1->getLxInt()->get());
    }
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() + p1->getLxNumber());
    }
    if (p0->isLxCharSeq() && p1->isLxCharSeq()) {
        return LValue::buildString(p0->getLxCharSeq() + p1->getLxCharSeq());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported + between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LSub(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt()->get() - p1->getLxInt()->get());
    }
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() - p1->getLxNumber());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported - between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LMul(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() * p1->getLxNumber());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported * between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LDiv(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt()->get() / p1->getLxInt()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported / between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LMod(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt()->get() / p1->getLxInt()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported % between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LNot(LValue *p) {
    if (p->isLxBoolean()) {
        return LValue::buildBool(!p->getLxBoolean());
    }
    if (p->isRef()) {
        /// TODO:
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported ! for " + p->getTypeStr());
}

LValue* LAnd(LValue *p0, LValue *p1) {
    if (p0->isLxBoolean() && p1->isLxBoolean()) {
        return LValue::buildBool(p0->getLxBoolean() && p1->getLxBoolean());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO:
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported && between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LOr(LValue *p0, LValue *p1) {
    if (p0->isLxBoolean() && p1->isLxBoolean()) {
        return LValue::buildBool(p0->getLxBoolean() || p1->getLxBoolean());
    }
    if (p0->isRef() || p1->isRef()) {
        /// TODO:
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported || between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LEq(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildBool(p0->getLxInt()->get() == p1->getLxInt()->get());
    }
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() == p1->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() == p1->getLxChar()->get());
    }
    if (p0->isLxString() && p1->isLxString()) {
        return LValue::buildBool(p0->getLxString()->get() == p1->getLxString()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported == between " 
    + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LNe(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildBool(p0->getLxInt()->get() != p1->getLxInt()->get());
    }
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() != p0->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() != p0->getLxChar()->get());
    }
    if (p0->isLxString() && p1->isLxString()) {
        return LValue::buildBool(p0->getLxString()->get() != p0->getLxString()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported != between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LGt(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() > p0->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() > p0->getLxChar()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported > between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LGe(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() >= p0->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() >= p0->getLxChar()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported >= between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LLt(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() < p0->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() < p0->getLxChar()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported < between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}

LValue* LLe(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildBool(p0->getLxNumber() <= p0->getLxNumber());
    }
    if (p0->isLxChar() && p1->isLxChar()) {
        return LValue::buildBool(p0->getLxChar()->get() <= p0->getLxChar()->get());
    }
    if (p0->isRef() || p1->isRef()) {
        return LValue::buildBool(true);
    }
    throw std::runtime_error("Unsupported <= between " 
        + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LXor(LValue *p0, LValue *p1) {
    throw std::runtime_error("unimplemented");
}
LValue* LBor(LValue *p0, LValue *p1) {
    throw std::runtime_error("unimplemented");
}
LValue* LBand(LValue *p0, LValue *p1) {
    throw std::runtime_error("unimplemented");
}
LValue* LAnti(LValue *p) {
    throw std::runtime_error("unimplemented");
}
LValue* LLshift(LValue *p0, LValue *p1) {
    throw std::runtime_error("unimplemented");
}
LValue* LRshift(LValue *p0, LValue *p1) {
    throw std::runtime_error("unimplemented");
}

LValue* LInvoke(LValue *p, const std::vector<LValue*>& args) {
    return LValue::buildMiddle("???");
}

LValue* LCast(cstring type, LValue *p) {
    return LValue::buildMiddle("???");
}

LValue* LAccess(LValue *p0, LValue *p1) {
    return LValue::buildMiddle("???");
}

LValue* LArray(LValue *p0, LValue *p1) {
    return LValue::buildMiddle("???");
}





#define IMP_LANG_TYPE(Type) L##Type* L##Type::self = nullptr;\
L##Type* L##Type::getInstance()\
{if (L##Type::self == nullptr) L##Type::self = new L##Type(); return L##Type::self;}\
L##Type::L##Type() {setType(T##Type);}

IMP_LANG_TYPE(Bool)
IMP_LANG_TYPE(Char)
IMP_LANG_TYPE(Int)
IMP_LANG_TYPE(Float)
IMP_LANG_TYPE(String)


void LType::setType(TypeEnum t) { te = t; }
TypeEnum LType::getType() { return te; }
std::string LType::getTypeStr() {
    switch (te) {
        case TBool  : return "bool";
        case TChar  : return "char";
        case TInt   : return "int";
        case TFloat : return "float";
        case TString: return "string";
        case TFlex  : return std::move(getFlexType()->getTypeStr());
        case TLambda: return std::move(getLambdaType()->getTypeStr());
    }
    throw std::runtime_error("Type system error!");
}
bool LType::isBuildinType() {return te >= TBool && te <= TString;}
FlexType* LType::getFlexType() {
    if (te == TFlex) return reinterpret_cast<FlexType*>(this);
    throw std::runtime_error("Non FlexType!");
}
LambdaType* LType::getLambdaType() {
    if (te == TLambda) return reinterpret_cast<LambdaType*>(this);
    throw std::runtime_error("Non LambdaType!");
}
std::map<std::string, LType*> LType::table {
    {"int" ,  LInt::getInstance()}, {"float", LFloat::getInstance()},
    {"char", LChar::getInstance()}, {"bool" ,  LBool::getInstance()},
    {"string", LString::getInstance()}
};
LType* LType::search(cstring s) {
    if (LType::table.find(s) == LType::table.end()) 
        throw std::runtime_error("No such type " + s + " in FlexType table.");
    return LType::table[s];
}
void LType::printTable() {
    std::cout << "\rType table:\n";
    std::cout << "\r---------------------------------" << std::endl;
    std::cout << "\r" << std::setw(20) << "class" << " | " 
        << "LType" << std::endl;
    std::cout << "\r---------------------------------" << std::endl;
    for (auto& kv : LType::table) {
        std::cout << "\r" << std::setw(20) << kv.first << " | " 
            << kv.second << std::endl;
    }
    std::cout << "\r---------------------------------" << std::endl;
}
void LType::setAlias(cstring s) {LType::table[s] = this;alias.emplace_back(s);}

#define IMP_GET_TYPE(Type) \
L##Type* LType::get##Type() {\
    static L##Type* p##Type = nullptr;\
    if (p##Type == nullptr) {p##Type = L##Type::getInstance();}\
    return p##Type;\
}

IMP_GET_TYPE(Bool)
IMP_GET_TYPE(Char)
IMP_GET_TYPE(Int)
IMP_GET_TYPE(Float)
IMP_GET_TYPE(String)

FlexType* LType::buildFlex(cstring s) {
    FlexType* p = new FlexType();
    p->setSignature(s);
    return p;
}
LambdaType* LType::buildLambda() {
    LambdaType* p = new LambdaType();
    return p;
}

FlexType::FlexType() {setType(TFlex);}
std::string FlexType::getTypeStr() {return signature;}
void FlexType::setSignature(cstring s) {signature = s; LType::table[s] = this;}
LambdaType::LambdaType() {setType(TLambda);}
std::string LambdaType::getTypeStr() {return "lambda";/** TODO: */}




LSymbol::LSymbol(cstring s, LType *t) {
    id = s; type = t;
    LSymbol::table[s] = this;
}
std::string LSymbol::get() {return id;}
LType* LSymbol::getType() {return type;}
std::map<std::string, LSymbol*> LSymbol::table;
LSymbol* LSymbol::build(cstring s, LType *t) {return new LSymbol(s, t);}
bool LSymbol::has(cstring s) {
    return table.find(s) != table.end();
}
LSymbol* LSymbol::search(cstring s) {
    if (table.find(s) == table.end()) 
        throw std::runtime_error("No such " + s + " in symbol table.");
    return table[s];
}
void LSymbol::printTable() {
    std::cout << "\rSymbol table:\n";
    std::cout << "\r--------------------------------------------" << std::endl;
    std::cout << "\r" << std::setw(15) << "symbol" << " | " 
        << std::setw(15) << "type" << " | " 
        << std::setw(8) << "buildin" 
        << std::endl;
    std::cout << "\r--------------------------------------------" << std::endl;
    for (auto& kv : LSymbol::table) {
        std::cout << "\r" << std::setw(15) << kv.first << " | " 
            << std::setw(15) << kv.second->getType()->getTypeStr() << " | " 
            << std::setw(8) << (kv.second->getType()->isBuildinType() ? "true" : "false") 
            << std::endl;
    }
    std::cout << "\r--------------------------------------------" << std::endl;
}


#define IMP_LEA_OPERATOR(OP)         \
void RightValue::G##OP() {           \
    RightValueNode* node = GPop();   \
    GPush(L##OP(node->getValue()));  \
    GBind<LValue*>(GBack(), {node}); \
}

#define IMP_LEA_OPERATOR_PAIR(OP) \
void RightValue::G##OP() {\
    std::vector<RightValueNode*> nodes = GPop(2);\
    GPush(L##OP(nodes[0]->getValue(), nodes[1]->getValue()));\
    GBind<LValue*>(GBack(), nodes);\
}

IMP_LEA_OPERATOR_PAIR(Add)
IMP_LEA_OPERATOR_PAIR(Sub)
IMP_LEA_OPERATOR_PAIR(Mul)
IMP_LEA_OPERATOR_PAIR(Div)
IMP_LEA_OPERATOR_PAIR(Mod)

IMP_LEA_OPERATOR(Not)
IMP_LEA_OPERATOR_PAIR(And)
IMP_LEA_OPERATOR_PAIR(Or)
IMP_LEA_OPERATOR_PAIR(Eq)
IMP_LEA_OPERATOR_PAIR(Ne)
IMP_LEA_OPERATOR_PAIR(Gt)
IMP_LEA_OPERATOR_PAIR(Ge)
IMP_LEA_OPERATOR_PAIR(Lt)
IMP_LEA_OPERATOR_PAIR(Le)

IMP_LEA_OPERATOR(Anti)
IMP_LEA_OPERATOR_PAIR(Xor)
IMP_LEA_OPERATOR_PAIR(Bor)
IMP_LEA_OPERATOR_PAIR(Band)
IMP_LEA_OPERATOR_PAIR(Lshift)
IMP_LEA_OPERATOR_PAIR(Rshift)


}