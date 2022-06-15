#ifndef __LEA_H__
#define __LEA_H__

#include <map>
#include <vector>
#include <string>
typedef const std::string& cstring;

namespace lea {

class LValue;
class LxInt;
class LxChar;
class LxBool;
class LxFloat;
class LxString;
class MdValue;
class SmValue;

class LType;
class LInt;
class LChar;
class LBool;
class LFloat;
class LString;
class FlexType;
class LambdaType;

/// Lexer
enum ValueType {
    TByte, TChar, TBool, 
    TInt, TFloat, TString,
    /** For middle value */
    TSymbol, TMiddle,
    /** For type system */
    TFlex, TLambda
};

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
    bool isLxChar();
    bool isLxString();
    bool isLxInt();
    bool isLxNumber();
    double getLxNumber();
    bool isLxCharSeq();
    std::string getLxCharSeq();
    bool isRef();
    bool isLxBoolean();
    bool getLxBoolean();
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

/** four calculations */
LValue* LAdd(LValue *p0, LValue *p1);
LValue* LSub(LValue *p0, LValue *p1);
LValue* LMul(LValue *p0, LValue *p1);
LValue* LDiv(LValue *p0, LValue *p1);
LValue* LMod(LValue *p0, LValue *p1);

/** boolean calculation */
LValue* LNot(LValue *p);
LValue* LAnd(LValue *p0, LValue *p1);
LValue* LOr (LValue *p0, LValue *p1);
LValue* LEq (LValue *p0, LValue *p1);
LValue* LNe (LValue *p0, LValue *p1);
LValue* LGt (LValue *p0, LValue *p1);
LValue* LGe (LValue *p0, LValue *p1);
LValue* LLt (LValue *p0, LValue *p1);
LValue* LLe (LValue *p0, LValue *p1);

/** Bit calculation */
LValue* LAnti  (LValue *p);
LValue* LXor   (LValue *p0, LValue *p1);
LValue* LBor   (LValue *p0, LValue *p1);
LValue* LBand  (LValue *p0, LValue *p1);
LValue* LLshift(LValue *p0, LValue *p1);
LValue* LRshift(LValue *p0, LValue *p1);

/** special invoking */
LValue* LCast  (LType *type, LValue *p);
LValue* LArray (LValue *p0, LValue *p1);
LValue* LAccess(LValue *p0, LValue *p1);
LValue* LInvoke(LValue *p, const std::vector<LValue*>& args);

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

DEF_LX_VALUE(LxInt, int)
DEF_LX_VALUE(LxChar, char)
DEF_LX_VALUE(LxBool, bool)
DEF_LX_VALUE(LxFloat, double)

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ------------------------ Type system definition ----------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
typedef ValueType TypeEnum;

class LType {
public:
    void setType(TypeEnum t);
    bool isBuildinType();
    TypeEnum getType();
    std::string getTypeStr();
    FlexType* getFlexType();
    LambdaType* getLambdaType();
    void setAlias(cstring s);
    /** Provide search service */
    static LType* search(cstring signature);
    static void printTable();
    /// LType factory
    static LInt* getInt();
    static LFloat* getFloat();
    static LChar* getChar();
    static LBool* getBool();
    static LString* getString();
    static FlexType* buildFlex(cstring s);
    static LambdaType* buildLambda();
private:
    TypeEnum te;
    std::vector<std::string> alias;
protected:
    static std::map<std::string, LType*> table;
};

class FlexType : public LType {
public:
    FlexType();
    void setSignature(cstring s);
    std::string getTypeStr();
private:
    std::string signature;
};

class LambdaType : public LType {
public:
    LambdaType();
    std::string getTypeStr();
private:
    std::vector<LType*> paramTypeList;
    LType* returnType;
};

#define DEF_LANG_TYPE(Type) class L##Type : public LType \
{public: static L##Type* getInstance(); private: L##Type(); static L##Type* self;};

DEF_LANG_TYPE(Bool)
DEF_LANG_TYPE(Char)
DEF_LANG_TYPE(Int)
DEF_LANG_TYPE(Float)
DEF_LANG_TYPE(String)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------- Symbol table definition ----------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
class LSymbol {
public:
    LSymbol(cstring s, LType *t);
    std::string get();
    LType* getType();
    /** prepared for symbol construction */
    static LSymbol* build(cstring s, LType *type);
    /** prepared for symbol query */
    static bool has(cstring s);
    static LSymbol* search(cstring s);
    static void printTable();
private:
    std::string id;
    LType* type;
    static std::map<std::string, LSymbol*> table;
};


template<typename Type>
class Node {
public:
    Node(Type v): value(v), parent(nullptr), children() { }
    inline Type getValue() { return value; }
    inline void setParent(Node<Type>* p) { parent = p; }
    inline void addChild(Node<Type>* p) { children.emplace_back(p); }
    inline void addChild(const std::vector<Node<Type>*>& nodes)
    { children.insert(children.end(), nodes.begin(), nodes.end()); }
private:
    Type value;
    Node<Type>* parent;
    std::vector<Node<Type>*> children;
};

template<typename Type>
void GBind(Node<Type>* p, const std::vector<Node<Type>*>& children) {
    for (int i = 0; i < children.size(); i++) {
        children[i]->setParent(p);
        p->addChild(children[i]);
    }
}

template<typename Type>
class Collector {
public:
    inline void GPush(Type v) { stack.emplace_back(new Node<Type>(v)); }
    inline Node<Type>* GBack() { return stack.back(); }
    inline Node<Type>* GPop() { Node<Type>* r = stack.back(); stack.pop_back(); return r; }
    std::vector<Node<Type>*> GPop(int n) {
        std::vector<Node<Type>*> r;
        for (int i = 0; i < n; i++) 
            r.emplace_back(stack[stack.size() - (n - i)]);
        for (int i = 0; i < n; i++) 
            stack.pop_back();
        return std::move(r);
    }
private:
    std::vector<Node<Type>*> stack;
};

typedef Node<LValue*> RightValueNode;

#define DEF_LEA_OPERATOR(OP) void G##OP()

class RightValue : public Collector<LValue*> {
public:
    DEF_LEA_OPERATOR(Add);
    DEF_LEA_OPERATOR(Sub);
    DEF_LEA_OPERATOR(Mul);
    DEF_LEA_OPERATOR(Div);
    DEF_LEA_OPERATOR(Mod);

    DEF_LEA_OPERATOR(Not);
    DEF_LEA_OPERATOR(And);
    DEF_LEA_OPERATOR(Or);
    DEF_LEA_OPERATOR(Eq);
    DEF_LEA_OPERATOR(Ne);
    DEF_LEA_OPERATOR(Gt);
    DEF_LEA_OPERATOR(Ge);
    DEF_LEA_OPERATOR(Lt);
    DEF_LEA_OPERATOR(Le);
    
    DEF_LEA_OPERATOR(Anti);
    DEF_LEA_OPERATOR(Xor);
    DEF_LEA_OPERATOR(Bor);
    DEF_LEA_OPERATOR(Band);
    DEF_LEA_OPERATOR(Lshift);
    DEF_LEA_OPERATOR(Rshift);
};

} // ending of namespace lea

#endif/*__LEA_H__*/