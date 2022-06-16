#ifndef __LEA_H__
#define __LEA_H__

#include <map>
#include <vector>
#include <string>
typedef const std::string& cstring;
#include "json.hpp"

namespace lea {


std::string join(const std::vector<std::string>& v, std::string s);

template<typename T>
std::string join(std::function<std::string (T)> lambda, const std::vector<T>& seq, cstring d) {
    size_t len = seq.size();
    std::string _r;
    for (int i = 0; i < len; i++) {
        if (i != len - 1) {
            _r += lambda(seq[i]) + d;
        } else {
            _r += lambda(seq[i]);
        }
    }
    return _r;
}


class LValue;
class LxInt;
class LxChar;
class LxBool;
class LxFloat;
class LxString;
class MdValue;
class SmValue;

class LType;
class LVoid;
class LInt;
class LChar;
class LBool;
class LFloat;
class LString;
class ClassType;
class LambdaType;

class ScopeNode;
class LSymbol;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------- Grammar node definition ----------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename Type>
class Node {
public:
    Node(Type v): value(v), parent(nullptr), children() { }
    inline Type getValue() { return value; }
    inline void setParent(Node<Type>* p) { parent = p; }
    inline void addChild(Node<Type>* p) { children.emplace_back(p); }
    inline void addChild(const std::vector<Node<Type>*>& nodes)
    { children.insert(children.end(), nodes.begin(), nodes.end()); }

    Type value;
    Node<Type>* parent;
    std::vector<Node<Type>*> children;
};

template<typename Type>
void GBind(Node<Type>* p, const std::vector<Node<Type>*>& children) {
    if (p == nullptr) throw std::runtime_error("Node parent nullptr!");
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == nullptr) 
            throw std::runtime_error("Node parent nullptr!");
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
protected:
    std::vector<Node<Type>*> stack;
};

class MultiCounter {
public:
    std::vector<int> multiCounter;

    inline void GInit(){ multiCounter.emplace_back(0); }
    inline void GOnce() 
    { int back = multiCounter.back();
      multiCounter[multiCounter.size() - 1] = back + 1;}
    inline int GReset()
    { int _r = multiCounter.back();
      multiCounter.pop_back(); return _r;}
    inline int GGet() {return multiCounter.back();}
};

/// Lexer
enum ValueType {
    TByte, TChar, TBool, 
    TInt, TFloat, TString,
    /** For middle value */
    TSymbol, TMiddle,
    /** For type system */
    TClass, TLambda, TVoid, TFunction
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
    static SmValue* buildSymbol(cstring symbol, ScopeNode* scope);
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
    std::string toString();
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

LValue* LSadd(LValue *p);
LValue* LSsub(LValue *p);
LValue* LPsub(LValue *p);

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
    SmValue(): v(""), scope(nullptr) {setType(TSymbol);}
    inline void set(cstring s) { v = s; }
    inline std::string get() { return v; }
    inline void setScope(ScopeNode* p) { scope = p; }
    inline ScopeNode* getScope() { return scope; }
private:
    std::string v;
    ScopeNode* scope;
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
    bool isLambdaType();
    TypeEnum getType();
    ClassType* getClassType();
    LambdaType* getLambdaType();
    void setAlias(cstring s);
    std::string toString();
    /** Provide search service */
    static LType* search(cstring signature);
    static void printTable();
    /// LType factory
    static LType*      build(cstring s);
    static LVoid*      getVoid();
    static LBool*      getBool();
    static LChar*      getChar();
    static LInt*       getInt();
    static LFloat*     getFloat();
    static LString*    getString();
    static ClassType*   buildClass(cstring s);
    static LambdaType* buildLambda();
private:
    TypeEnum te;
    std::vector<std::string> alias;
protected:
    static std::map<std::string, LType*> table;
};

class ClassType : public LType {
private:
    ClassType(cstring s);
public:
    std::string get();
    static ClassType* build(cstring s);
private:
    std::string signature;
    /// TODO: members define
    std::map<std::string, LSymbol*> members;
};

class LambdaType : public LType {
public:
    LambdaType() {setType(TLambda);}
    void mount(Node<LType*>* p) { self = p; }
    std::string get();
private:
    Node<LType*>* self;
};

class FunctionType : public LType {
public:
    FunctionType() {setType(TFunction);}
private:
    std::string name;
    // 1. return type
    // 2. parameters type list
    Node<LType*>* self; 
};

#define DEF_LANG_TYPE(Type) class L##Type : public LType \
{public: static L##Type* getInstance(); private: L##Type(); static L##Type* self;};

DEF_LANG_TYPE(Void)
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
    LSymbol(cstring s, LType *t, ScopeNode* p);
    std::string get();
    LType* getType();
    /** prepared for symbol construction */
    static LSymbol* build(cstring s, LType *type, ScopeNode* p);
    /** prepared for symbol query */
    static bool has(cstring s, ScopeNode* p);
    static LSymbol* search(cstring s, ScopeNode* p);
    static void printTable();
    static LSymbol* getSymbol(SmValue *p);
private:
    std::string id;
    LType* type;
    ScopeNode* scope;
    static std::map<std::string, std::map<std::string, LSymbol*>> scopeTable;
};

class SymbolAnalysis : public Collector<LType*> {
public:
    void GDef(cstring name, LType* type);
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

    DEF_LEA_OPERATOR(Sadd);
    DEF_LEA_OPERATOR(Ssub);
    DEF_LEA_OPERATOR(Psub);

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

    void GInvoke(int argc=0);
    void GCast();
    void GArray();
    void GAccess();

    void newArgsSpace();
    void addOneArg();
    int releaseArgsSpace();
private:
    std::vector<int> invokingArgs;
public:
    void GPrint(cstring sign="Tree");
    nlohmann::json GLoopUp(RightValueNode* node, int depth=0);
};

typedef Node<LType*> LTypeNode;

class LTypeAnalysis : public Collector<LType*>, public MultiCounter {
public:
    void GLambda(int argc = 0);
public:
    void GPrint(cstring sign="Tree");
    nlohmann::json GLoopUp(LTypeNode* node, int depth=0);
};

///
class ScopeNode {
private:
    ScopeNode(cstring n) {
        parent = nullptr;
        name = n;
        id = (++ScopeNode::uuid);
        ScopeNode::record(name, this);
    }
public:
    inline void setParent(ScopeNode* p) { parent = p; }
    inline std::string getName() { return name; }
    inline std::string getScopeStr() { return name + "$" + std::to_string(id); }
    inline std::string getScopeChain() {
        std::vector<std::string> _r;
        ScopeNode* p = this;
        do {
            _r.emplace_back(p->getScopeStr());
        } while ((p = p->parent) != nullptr);
        return std::move(join(_r, "."));
    }
    static inline ScopeNode* build(cstring name) 
    { return new ScopeNode(name); }
    static inline ScopeNode* search(cstring name) {
        if (ScopeNode::table.find(name) != ScopeNode::table.end()) 
            throw std::runtime_error("No such " + name + " in the scope table.");
        return ScopeNode::table[name];
    }
private:
    static void record(cstring name, ScopeNode* p) {ScopeNode::table[name] = p;}
    static int uuid;
    static std::map<std::string, ScopeNode*> table;
    int id;
    std::string name;
    ScopeNode* parent;
};

class ScopeMaker : public Collector<ScopeNode*> {
public:
    inline void GEnter(cstring s) {
        GPush(ScopeNode::build(s));
        if (stack.size() > 1) 
            GBack()->setParent(stack[stack.size() - 2]);
    }
    inline ScopeNode* GExit() { return GPop()->getValue(); }
    inline ScopeNode* GGet() { return GBack()->getValue(); }
};


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------- Compiler control -----------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void LPrepare();
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------- Instance creation ----------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
extern RightValue *RV;
extern ScopeMaker *SP;
extern LTypeAnalysis *TP;

} // ending of namespace lea

#endif/*__LEA_H__*/