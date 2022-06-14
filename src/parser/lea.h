#ifndef __LEA_H__
#define __LEA_H__

#include <map>
#include <vector>
#include <string>
typedef const std::string& cstring;
#include <stdexcept>

namespace lea {

class LValue;
class LxInt;
class LxChar;
class LxBool;
class LxFloat;
class LxString;
class MdValue;
class SmValue;

/// Lexer
enum ValueType {
    TByte, TChar, TBool, 
    TInt, TFloat, TString,
    /** For middle value */
    TSymbol, TMiddle
};

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

class LValue {
public:
    void setType(ValueType vt);
    ValueType getType();
    std::string getTypeStr();
    static LValue* build(ValueType vt, cstring va);
    static LxInt* buildInt(int i);
    static LxChar* buildChar(char c);
    static LxBool* buildBool(bool b);
    static LxFloat* buildFloat(double f);
    static LxString* buildString(std::string s);
    static MdValue* buildMiddle(cstring type);
    static SmValue* buildSymbol(cstring symbol, const std::vector<std::string>& scope = {});
    bool isLxInt();
    bool isLxNumber();
    double getLxNumber();
    bool isLxCharSeq();
    std::string getLxCharSeq();
    bool isRef();
    LxInt* getLxInt();
    LxChar* getLxChar();
    LxBool* getLxBool();
    LxFloat* getLxFloat();
    LxString* getLxString();
    MdValue* getMdValue();
    SmValue* getSmValue();
private:
    ValueType type;
};

bool isLxType(LValue *p);
LValue* LAdd(LValue *p0, LValue *p1);
LValue* LSub(LValue *p0, LValue *p1);
LValue* LMul(LValue *p0, LValue *p1);
LValue* LDiv(LValue *p0, LValue *p1);
LValue* LMod(LValue *p0, LValue *p1);
// LValue* LInvoke(LValue *p, const std::vector<LValue*>& args);
// LValue* LCast(LValue *p);


class LxValue : public LValue {}; /** Lexer word value */
class SmValue : public LValue {
public:
    SmValue();
    void set(cstring s);
    void setScope(const std::vector<std::string>& sco);
    std::vector<std::string>& getScope();
    std::string get();
private:
    std::string v;
    std::vector<std::string> scope;
};
#ifndef SmValueImpl
#define SmValueImpl
SmValue::SmValue(): v(), scope() {setType(TSymbol);}
void SmValue::set(cstring s) {v = s;}
void SmValue::setScope(const std::vector<std::string>& sco) {scope = sco;}
std::vector<std::string>& SmValue::getScope() {return scope;}
std::string SmValue::get() {return join(merge(scope, {v}), ".");}
#endif
class MdValue : public LValue {
public:
    MdValue();
    void setTypeSign(cstring sign);
    std::string get();
private:
    static int uuid;
    std::string v;
    std::string typeSign;
}; /** Middle value */

#ifndef MdValueImpl
#define MdValueImpl
int MdValue::uuid = 0;
MdValue::MdValue(): v("Middle$" + std::to_string(++uuid)) {setType(TMiddle);}
void MdValue::setTypeSign(cstring sign) {typeSign = sign;}
std::string MdValue::get() {return v + "@" + typeSign;}
#endif

class LxString : public LxValue {
public:
    LxString();
    void set(cstring s);
    void setV(std::string s);
    std::string get();
    std::string getAlias();
private:
    int index;
    static std::map<int, std::string> constPool;
    static int uuid;
};

#ifndef LxStringImpl
#define LxStringImpl
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
#endif


#define DEF_LX_VALUE(clazz, T) \
class clazz : public LxValue {\
public:\
    clazz();\
    void set(cstring s);\
    void setV(T x);\
    T get();\
private:\
    T v = 0;\
};

#define IMP_LX_VALUE(clazz, T, VT, setter) \
clazz::clazz() {setType(VT);}\
void clazz::set(cstring s) {setter;}\
void clazz::setV(T x) {v = x;}\
T clazz::get() {return v;}

#ifndef LxIntImpl
#define LxIntImpl
DEF_LX_VALUE(LxInt, int)
IMP_LX_VALUE(LxInt, int, TInt, v = std::stoi(s))
#endif

#ifndef LxCharImpl
#define LxCharImpl
DEF_LX_VALUE(LxChar, char)
IMP_LX_VALUE(LxChar, char, TChar, v = s[1])
#endif

#ifndef LxBoolImpl
#define LxBoolImpl
DEF_LX_VALUE(LxBool, bool)
IMP_LX_VALUE(LxBool, bool, TBool, v = s == "true")
#endif

#ifndef LxFloatImpl
#define LxFloatImpl
DEF_LX_VALUE(LxFloat, double)
IMP_LX_VALUE(LxFloat, double, TFloat, v = std::stod(s))
#endif


#ifndef BasicValueImpl
#define BasicValueImpl
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
bool LValue::isLxInt() {
    return getType() == TInt;
}
bool LValue::isLxNumber() {
    return getType() == TInt || getType() == TFloat;
}
double LValue::getLxNumber() {
    if (getType() == TInt) return getLxInt()->get();
    if (getType() == TFloat) return getLxFloat()->get();
    throw std::runtime_error(getTypeStr() + " can't getLxNumber!");
}
bool LValue::isLxCharSeq() {
    return getType() == TChar || getType() == TString;
}
std::string LValue::getLxCharSeq() {
    if (getType() == TChar) return "" + getLxChar()->get();
    if (getType() == TString) return getLxString()->get();
    throw std::runtime_error(getTypeStr() + " can't getLxCharSeq!");
}
bool LValue::isRef() {
    return getType() == TMiddle || getType() == TSymbol;
}

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
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() + p1->getLxNumber());
    } else if (p0->isLxCharSeq() && p1->isLxCharSeq()) {
        return LValue::buildString(p0->getLxCharSeq() + p1->getLxCharSeq());
    } else if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported + between " + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LSub(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() - p1->getLxNumber());
    } else if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported - between " + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LMul(LValue *p0, LValue *p1) {
    if (p0->isLxNumber() && p1->isLxNumber()) {
        return LValue::buildFloat(p0->getLxNumber() * p1->getLxNumber());
    } else if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported * between " + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LDiv(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt() / p1->getLxInt());
    } else if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported / between " + p0->getTypeStr() + " and " + p1->getTypeStr());
}
LValue* LMod(LValue *p0, LValue *p1) {
    if (p0->isLxInt() && p1->isLxInt()) {
        return LValue::buildInt(p0->getLxInt() / p1->getLxInt());
    } else if (p0->isRef() || p1->isRef()) {
        /// TODO: 1. Query symbol table 
        ///       2. Type validation (Type system)
        ///       3. LR code generation
        return LValue::buildMiddle("???");
    }
    throw std::runtime_error("Unsupported % between " + p0->getTypeStr() + " and " + p1->getTypeStr());
}

#endif

}



#endif/*__LEA_H__*/