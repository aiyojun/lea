#ifndef __core_h__
#define __core_h__

#include <iostream>
#include <algorithm>
#include <string>
typedef const std::string& cstring;
#include <map>
#include <deque>
#include <vector>
#include "json.hpp"

#include "lea.h"

std::string join(const std::deque<std::string>& seq, cstring d);
std::string join(const std::vector<std::string>& seq, cstring d);
void print(const char* s);
void println(cstring s);
void println(const char* s);
extern std::deque<std::string> seq;

class LClazz;
class LFunction;
class LDependency;
class LImport;
class LVariable;
class TypeHelper;
class LType;
class LLambdaType;
class LLambda;

union MValue {
    int intVal;
    long longVal;
    float floatVal;
    double doubleVal;
    char charVal;
    bool boolVal;
};

enum MType {
    MT_NONE,
    MT_RETURN,
    MT_SYMBOL,
    MT_ARRAY,
    MT_BOOL, 
    MT_INT, 
    MT_LONG, 
    MT_FLOAT, 
    MT_STRING,
    MT_DOUBLE, 
    MT_CHAR, 
    MT_BYTE,
    MT_NULL
};


class AstNode {
public:
    std::string type;
    std::string text;
    AstNode* parent;
    std::vector<AstNode*> children;

    void assign(cstring type, cstring text, AstNode* parent);
    void append(AstNode* child);
    std::string toString();

    /** Version 2022.06.12 */
    MValue mValue;
    MType  mType = MType::MT_NONE;
    // std::string tempSpace;
    /// Function invoking
    std::string mScope;
    std::string mSymbol;
    std::string mReturn;
    std::string imArray;
    // std::string mFunction;

};

class AstTree {
public:
    AstNode *root;
    AstNode *ptr;
    std::vector<AstNode*> stack;

    AstTree();
    void init();
    void merge(cstring nodeSign, int n=2);
    void pushStack(cstring type, cstring text);
    AstNode* popStack();

    void print();
    nlohmann::json loopUp(AstNode* node, int depth=0);
};

/** Base class, prepared for other functionality class. */

class LCounter {
public:
    int counter;

    void GInit();
    void GOnce();
    int GReset();
    int GGet();
};

class LMultiCounter {
public:
    std::vector<int> multiCounter;

    void GInit();
    void GOnce();
    int GReset();
    int GGet();
};

class LCollector {
public:
    std::vector<AstNode*> stack;

    void GPush(cstring type, cstring text="");
    AstNode* GPop();
    void GMerge(cstring nodeSign, int n=2);
    void GReplace(cstring type, cstring text);

    void GPrint(cstring sign="Tree");
    nlohmann::json GLoopUp(AstNode* node, int depth=0);
};

/** ---------------------------------------------------- */

class TheImport : public LCollector {
public:
    LCounter oneDepth;
    LCounter dependencies;

    // std::vector<LImport *> imports;

    void GMergePackage(int n);
    void GMergeDependency(int n);

    // void print();


    // int deps;
    // int depth;

    // void initDepth();
    // void addDepth();
    // int resetDepth();

    // void init();
    // void recordOne();
    // int resetAll();
};

class RightValue : public LCollector {
public:
    std::vector<int> invokingArgs;
    void newArgsSpace();
    void addOneArg();
    int releaseArgsSpace();

    /** Version 2022.06.12 */
    void GMerge(cstring sign, int n = 2);

    void GAdd();
    void GSub();
    void GMul();
    void GDiv();
    void GMod();
    void GAnd();
    void GOr();
    void GEq();
    void GNe();
    void GGt();
    void GGe();
    void GLt();
    void GLe();
    void GXor();
    void GBor();
    void GBand();
    void GAnti();
    void GLshift();
    void GRshift();
    void GCast();
    void GInvoke();
    void GArray();
    void GDot();

    std::string buildWithScope(AstNode* p);
    std::string getArray (AstNode* p);
    std::string getReturn(AstNode* p);
    std::string getSymbol(AstNode* p);
    std::string multiEvaluate(AstNode* p);


    /** Version 2022.06.15 */
    
};

class TheSymbol : public LCollector, public LMultiCounter {
public:
    // int number;
    std::vector<AstNode*> symbols;

    std::vector<int> scopeCount;
    void newScope();
    void addOne();
    int releaseScope();

    TheSymbol();
    // void add();
    // int reset();

    // void merge(cstring nodeSign, int n=2);
    // void pushStack(cstring type, cstring text);
    // AstNode* popStack();

    // void print();
    // nlohmann::json loopUp(AstNode* node, int depth=0);


    /**  Version 2022.06.08 New version of TheSymbol */
    LClazz* clazz;
    void GEnterClazz(cstring name);
    void GExitClazz(int n);
    void GMergeClazzSymbol(cstring qualifier);

    void GMergeGlobalSymbol(int n);

    /** Version 2022.06.09 */
    void GMergeSymbol(int n);
    void GCheck();
    void GCheckVariableWithType();
    void GCheckMethod(int args, int r);
    LMultiCounter argsList;
};



class LContext {
public:
    std::vector<LImport*  > imports;
    std::vector<LFunction*> functions;
    std::vector<LVariable*> variables;
    std::vector<LClazz*   > clazzes;
    std::vector<std::string> commands;

    void GPrint();
};

class LClazz {
public:
    std::string name;
    std::string qualifier;
    std::map<std::string, LVariable*> vars;
    std::map<std::string, LFunction*> funs;

    std::string toString();
};

class LFunction {
public:
    std::string qualifier;
    std::string def;
    std::string name;
    std::string toString();
};

class LVariable {
public:
    std::string qualifier;
    std::string def;
    std::string name;
    std::string toString();
};

class LDependency {
public:
    std::vector<LImport> imports;
};

class LImport {
public:
    std::vector<std::string> pack;
    void append(cstring);
    std::string toString();
};

class TypeHelper : public LMultiCounter, public LCollector {
public:
    LCounter lambdaCounter;

    LType* GBasicType(cstring type);
    LLambdaType* GLambdaType();
    bool isBasicType(LType* p);
    bool isLambdaType(LType* p);

    void GMergeReturn();
    void GMergeTypeList(int n);
    void GMergeLambda(int n);

    // std::vector<LType *> stack;
    // void GPush(cstring type, cstring text);
    // LType* GPop();
    // void GMerge(cstring nodeSign, int n=2);

    // void GPrint(cstring sign="Tree");
    // nlohmann::json GLoopUp(LType* node, int depth=0);    
};

class LType {
public:
    std::string meta;
    std::string name;
};

class LLambdaType : public LType {
public:
    LType *returnType;
    std::vector<LType*> typeList;

    void append(LType* type);
    void setRetureType(LType* type);
};


class LambdaType : public LCounter, public LCollector {
public:
    
};

class LLambda {
public:

};


class LScope : public LMultiCounter, public LCollector {
public:
    void GEnter(cstring type, cstring name);
    void GExit();
    std::string GGet();
};


class LExecution : public LCollector, public LMultiCounter {
public:
    static int uniqueCode;
    std::string GAllocate();
};


extern AstTree* astTree;
extern RightValue *rightValue;
extern RightValue *VA;
extern TheImport *MO;
extern TheSymbol *symbolCollector, *SM;
extern TypeHelper* typeHelper, *TP;
extern LContext *CT;
extern LScope *SP;
extern LExecution *EX, *CX;

void prepareCompiler();
void releaseCompiler();


extern long __LEA_LINE__;
extern long __LEA_CHAR__;


#endif/*__core_h__*/