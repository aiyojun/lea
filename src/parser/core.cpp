#include "core.h"

#include <iostream>

void print(const char* s)
{
  std::cout << "\r" << s;
}
void println(cstring s)
{
  std::cout << "\r" << s << std::endl;
}
// void println(const char* s)
// {
//   std::cout << s << std::endl;
// }

void checkpoint(cstring s) {
    std::cout << s << std::endl;
}

std::string join(const std::deque<std::string>& seq, cstring d) {
    size_t len = seq.size();
    std::string _r;
    for (int i = 0; i < len; i++) {
        if (i != len - 1) {
            _r += seq[i] + d;
        } else {
            _r += seq[i];
        }
    }
    return _r;
}

std::string join(const std::vector<std::string>& seq, cstring d) {
    size_t len = seq.size();
    std::string _r;
    for (int i = 0; i < len; i++) {
        if (i != len - 1) {
            _r += seq[i] + d;
        } else {
            _r += seq[i];
        }
    }
    return _r;
}

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

AstTree* astTree;
RightValue *rightValue;
RightValue *VA;
TheImport *MO;
TheSymbol* symbolCollector, *SM;
LContext *CT;
TypeHelper* typeHelper, *TP;
LScope *SP;
LExecution *EX;

void AstNode::assign(cstring type, cstring text, AstNode* parent) {
    this->type = type; this->text = text; this->parent = parent;
    if (parent != nullptr)
        parent->append(this);
}

void AstNode::append(AstNode* child) {
    this->children.emplace_back(child);
}

std::string AstNode::toString() {
    return "AstNode { Type[" + this->type + "]," 
        + "Text[" + this->text 
        + "],Children[" + std::to_string(this->children.size()) + "] }";
}

AstTree::AstTree()
: root(nullptr), ptr(nullptr), stack() {

}

void AstTree::init() {
    this->root = new AstNode();
    this->root->assign("START", "", nullptr);
    this->ptr = this->root;
}

void AstTree::merge(cstring nodeSign, int n) {
    //std::cout << "[E] Type(" << nodeSign << "), Depth(" << n << ")\n";
    AstNode* p = new AstNode();
    for (int i = 0; i < n; i++) {
        p->append(this->stack[this->stack.size() - (n - i)]);
    }
    for (int i = 0; i < n; i++) {
        this->popStack();
    }
    p->assign(nodeSign, "", nullptr);
    this->stack.emplace_back(p);
}

void AstTree::pushStack(cstring type, cstring text) {
    AstNode* p = new AstNode();
    p->assign(type, text, nullptr);
    this->stack.emplace_back(p);
}

AstNode* AstTree::popStack() {
    AstNode* back = this->stack.back();
    this->stack.pop_back();
    return back;
}

nlohmann::json AstTree::loopUp(AstNode* node, int depth)
{
    if (node == nullptr) return nullptr;
    nlohmann::json _r;
    _r["name"] = node->text == "" ? node->type : node->type + ":" + node->text;
    std::vector<nlohmann::json> children;
    for (auto child : node->children) {
        children.emplace_back(loopUp(child, depth + 1));
    }
    _r["children"] = nlohmann::json(children);
    return _r;
}

void AstTree::print() {
    if (this->stack.size() != 1) {
        std::cout << "start size : " << this->stack.size() << std::endl;
        for (int i = 0; i < this->stack.size(); i++) {
            std::cout << "The " << i << " tree:\n";
            std::cout << this->loopUp(this->stack[i]) << std::endl;
            std::cout << "over\n\n";
        }
    } else {
        std::cout << "Tree:" << std::endl;
        std::cout << this->loopUp(this->stack[0]) << std::endl;
    }
}

/** LCounter LCollector */
void LCounter::GInit() {
    this->counter = 0;
}

void LCounter::GOnce() {
    this->counter++;
}

int LCounter::GReset() {
    int _r = this->counter;
    this->counter = 0;
    return _r;
}

int LCounter::GGet() {
    return this->counter;
}

void LMultiCounter::GInit() {
    this->multiCounter.emplace_back(0);
}

void LMultiCounter::GOnce() {
    int back = this->multiCounter.back();
    this->multiCounter[this->multiCounter.size() - 1] = back + 1;
}

int LMultiCounter::GReset() {
    int _r = this->multiCounter.back();
    this->multiCounter.pop_back();
    return _r;
}

int LMultiCounter::GGet() {
    return this->multiCounter.back();
}

/**  */
void LCollector::GPush(cstring type, cstring text) {
    AstNode* p = new AstNode();
    p->assign(type, text, nullptr);
    this->stack.emplace_back(p);
}

AstNode* LCollector::GPop() {
    AstNode* back = this->stack.back();
    this->stack.pop_back();
    return back;
}

void LCollector::GMerge(cstring nodeSign, int n) {
    AstNode* p = new AstNode();
    for (int i = 0; i < n; i++) {
        p->append(this->stack[this->stack.size() - (n - i)]);
    }
    for (int i = 0; i < n; i++) {
        this->GPop();
    }
    p->assign(nodeSign, "", nullptr);
    this->stack.emplace_back(p);
}

void LCollector::GPrint(cstring sign) {
    std::cout << "\r[ " << sign << " sub-tree:" << this->stack.size() << " ]" << std::endl;
    std::cout << ">>>" << std::endl;
    // std::cout << "--- " << sign << " ---" << std::endl;
    if (this->stack.size() != 1) {
        // std::cout << "Tree number : " << this->stack.size() << std::endl;
        for (int i = 0; i < this->stack.size(); i++) {
            std::cout << std::setw(4) << i << ": ";
            std::cout << this->GLoopUp(this->stack[i]) << std::endl;
        }
    } else {
        // std::cout << "Json Tree:" << std::endl;
        std::cout << this->GLoopUp(this->stack[0]) << std::endl;
    }
    std::cout << "<<<" << sign << std::endl;
    // std::cout << "--- " << sign << " --- over" << std::endl;
}

nlohmann::json LCollector::GLoopUp(AstNode* node, int depth) {
    if (node == nullptr) return nullptr;
    nlohmann::json _r;
    _r["name"] = node->text == "" ? node->type : node->type + ":" + node->text;
    std::vector<nlohmann::json> children;
    for (auto child : node->children) {
        children.emplace_back(GLoopUp(child, depth + 1));
    }
    _r["children"] = nlohmann::json(children);
    return _r;
}


/** The import */
void TheImport::GMergePackage(int n) {
    // std::cout << "merge package : " << n << "\n";
    this->GMerge("PACKAGE", n);
    AstNode* p = this->stack.back();
    LImport *oneImport = new LImport();
    for (auto& childPtr : p->children) {
        oneImport->append(childPtr->text);
        //std::cout << "xxx: " << childPtr->text << "|" << childPtr->type << std::endl;
    }
    CT->imports.emplace_back(oneImport);
}

void TheImport::GMergeDependency(int n) {
    this->GMerge("IMPORT", n);
        /// TODO: Do nothing!
}

// void TheImport::print() {

// }

// void TheImport::initDepth() {
//     this->depth = 0;
// }

// void TheImport::addDepth() {
//     this->depth++;
// }

// int TheImport::resetDepth() {
//     int _r = this->depth;
//     this->depth = 0;
//     return _r;
// }

// void TheImport::init() {
//     this->deps = 0;
//     this->depth = 0;
// }

// void TheImport::recordOne() {
//     this->deps++;
// }

// int TheImport::resetAll() {
//     int _r = this->deps;
//     this->deps = 0;
//     return _r;
// }

/** Right value */

void RightValue::newArgsSpace() {
    this->invokingArgs.emplace_back(0);
}

void RightValue::addOneArg() {
    int back = this->invokingArgs.back();
    this->invokingArgs[this->invokingArgs.size() - 1] = back + 1;
}

int RightValue::releaseArgsSpace() {
    int _r = this->invokingArgs.back();
    this->invokingArgs.pop_back();
    return _r;
}


/**  */

TheSymbol::TheSymbol()
// :symbols(), scopeCount() 
{
    scopeCount.emplace_back(0);
}

void TheSymbol::newScope() {
    this->scopeCount.emplace_back(0);
}

void TheSymbol::addOne() {
    int back = this->scopeCount.back();
    this->scopeCount[this->scopeCount.size() - 1] = back + 1;
}

int TheSymbol::releaseScope() {
    int _r = this->scopeCount.back();
    this->scopeCount.pop_back();
    //std::cout << ">> release scope : " << _r << ", rest : " << this->scopeCount.size() << "\n";
    return _r;
}

// void TheSymbol::add() {
//     this->number++;
// }

// int TheSymbol::reset() {
//     int _r = this->number;
//     this->number = 0;
//     return _r;
// }

// void TheSymbol::merge(cstring nodeSign, int n) {
//     //std::cout << "[E] Type(" << nodeSign << "), Depth(" << n << ")\n";
//     AstNode* p = new AstNode();
//     for (int i = 0; i < n; i++) {
//         p->append(this->symbols[this->symbols.size() - (n - i)]);
//     }
//     for (int i = 0; i < n; i++) {
//         this->popStack();
//     }
//     p->assign(nodeSign, "", nullptr);
//     this->symbols.emplace_back(p);
// }

// void TheSymbol::pushStack(cstring type, cstring text) {
//     AstNode* p = new AstNode();
//     p->assign(type, text, nullptr);
//     this->symbols.emplace_back(p);
// }

// AstNode* TheSymbol::popStack() {
//     AstNode* back = this->symbols.back();
//     this->symbols.pop_back();
//     return back;
// }

// nlohmann::json TheSymbol::loopUp(AstNode* node, int depth)
// {
//     if (node == nullptr) return nullptr;
//     nlohmann::json _r;
//     _r["name"] = node->text == "" ? node->type : node->type + ":" + node->text;
//     std::vector<nlohmann::json> children;
//     for (auto child : node->children) {
//         children.emplace_back(loopUp(child, depth + 1));
//     }
//     _r["children"] = nlohmann::json(children);
//     return _r;
// }

// void TheSymbol::print() {
//     if (this->symbols.size() != 1) {
//         std::cout << "start size : " << this->symbols.size() << std::endl;
//         for (int i = 0; i < this->symbols.size(); i++) {
//             std::cout << "The " << i << " tree:\n";
//             std::cout << this->loopUp(this->symbols[i]) << std::endl;
//             std::cout << "over\n\n";
//         }
//     } else {
//         std::cout << "Tree:" << std::endl;
//         std::cout << this->loopUp(this->symbols[0]) << std::endl;
//     }
// }

void TheSymbol::GEnterClazz(cstring name) {
    this->clazz = new LClazz();
    this->clazz->name = name;
}

void TheSymbol::GExitClazz(int n) {
    // checkpoint("xxxx exit clazz : " + this->clazz->name);
    this->GMerge("CLASS:" + this->clazz->name, n);
    CT->clazzes.emplace_back(this->clazz);
    this->clazz = nullptr;
}

void TheSymbol::GMergeClazzSymbol(cstring qualifier) {
    // std::cout << "GMergeClazzSymbol\n";
    //this->GMerge("QUALIFIER:" + qualifier, 1);
    AstNode* p  = this->stack.back();
    // std::cout << "GMergeClazzSymbol : " << p->toString() << "\n";
    AstNode* def = p->children[0];
    AstNode* sym = p->children[1];
    if (def->text == "def") {
        LFunction *fun = new LFunction();
        fun->qualifier = qualifier;
        fun->def       = def->text;
        fun->name      = sym->text;
        this->clazz->funs[fun->name] = fun;
    } else {
        LVariable *var = new LVariable();
        var->qualifier = qualifier;
        var->def       = def->text;
        var->name      = sym->text;
        this->clazz->vars[var->name] = var;
    }
    // std::cout << "GMergeClazzSymbol over\n";
}

void TheSymbol::GMergeGlobalSymbol(int n) {
    this->GMerge("GLOBAL", n);
    AstNode* p = this->stack.back();
    for (auto& childPtr : p->children) {
        AstNode* def = childPtr->children[0];
        AstNode* sym = childPtr->children[1];
        if (def->text == "def") {
            LFunction *fun = new LFunction();
            fun->def       = def->text;
            fun->name      = sym->text;
            CT->functions.emplace_back(fun);
        } else if (def->text == "var" || def->text == "val") {
            LVariable *var = new LVariable();
            var->def       = def->text;
            var->name      = sym->text;
            CT->variables.emplace_back(var);
        }
    }
}

void AstSymbol(AstNode *p) {
    AstNode *qualifier = nullptr, *def, *sym;
    if (p->children.size() == 2) {
        def = p->children[0];
        sym = p->children[1];
    } else if (p->children.size() == 3) {
        qualifier = p->children[0];
        def = p->children[1];
        sym = p->children[2];
    }
    // println("Enter " + def->text + " " + p->children[1]->text);
}

void TheSymbol::GMergeSymbol(int n) {
    this->GMerge("SYMBOL", n);
    AstSymbol(this->stack.back());
}

void TheSymbol::GCheck() {
    AstNode *qualifier = nullptr, *def, *sym;
    if (SM->stack.back()->children.size() == 2) {
        def = SM->stack.back()->children[0];
        sym = SM->stack.back()->children[1];
    } else if (SM->stack.back()->children.size() == 3) {
        qualifier = SM->stack.back()->children[0];
        def = SM->stack.back()->children[1];
        sym = SM->stack.back()->children[2];
    }
}

void TheSymbol::GCheckVariableWithType() {
    AstNode *qualifier = nullptr, *def, *sym;
    if (SM->stack.back()->children.size() == 2) {
        def = SM->stack.back()->children[0];
        sym = SM->stack.back()->children[1];
    } else if (SM->stack.back()->children.size() == 3) {
        qualifier = SM->stack.back()->children[0];
        def = SM->stack.back()->children[1];
        sym = SM->stack.back()->children[2];
    }
    std::vector<std::string> VarDefs{"var", "val"};
    if (std::find(std::begin(VarDefs), std::end(VarDefs), def->text) == std::end(VarDefs)) {
        // println(sym->text + " is not a variable!");
        return;
    }

    std::cout << "\r"
        << "[VAR] " << sym->text
        << ": " << TP->stack.back()->type << " " << TP->stack.back()->text
        << "\n"
    ;
}

void TheSymbol::GCheckMethod(int args, int r) {
    AstNode *qualifier = nullptr, *def, *sym;
    if (SM->stack.back()->children.size() == 2) {
        def = SM->stack.back()->children[0];
        sym = SM->stack.back()->children[1];
    } else if (SM->stack.back()->children.size() == 3) {
        qualifier = SM->stack.back()->children[0];
        def = SM->stack.back()->children[1];
        sym = SM->stack.back()->children[2];
    }
    if (def->text != "def") {
        // println(sym->text + " is not a variable!");
        return;
    }
    std::cout << "\r"
        << "[FUN] " << sym->text
        << ": " << args << " => " << r
        << "\n"
    ;
    for (int i = 0; i < args; i++) {
        AstNode *p = TP->stack[TP->stack.size() - (args - i) - r];
        std::cout << "\r   Arg-" << i << " " << p->type << ":" << p->text << "\n";
    }
    if (r > 0) {
        AstNode *p = TP->stack[TP->stack.size() - 1];
        std::cout << "\r  Return " << p->type << (p->text == "" ? "" : ":" + p->text) << "\n";
    }
}


/** Type processing */
LType* TypeHelper::GBasicType(cstring type) {
    LType *p = new LType();
    p->name = type;
    p->meta = "TYPE";
    return p;
}

LLambdaType* TypeHelper::GLambdaType() {
    LLambdaType *p = new LLambdaType();
    p->meta = "LAMBDA";
    return p;
}

bool TypeHelper::isBasicType(LType* p) {
    return p->meta == "TYPE";
}

bool TypeHelper::isLambdaType(LType* p) {
    return p->meta == "LAMBDA";
}

void TypeHelper::GMergeReturn() {
    this->GMerge("LAMBDA_RETURN", 1);
}

void TypeHelper::GMergeTypeList(int n) {
    this->GMerge("TYPE_LIST", n);
}

void TypeHelper::GMergeLambda(int n) {
    this->GMerge("LAMBDA", n);
    // AstNode* p = this->stack.back();
    // LLambdaType* ptr = this->GLambdaType();
    // if (p->children.size() == 1) {
    //     ptr->setRetureType(p->children[0]);
    // } else if (p->children.size() == 2) {
    // }
}

// void TypeHelper::GPush(cstring type, cstring text) {
//     AstNode* p = new AstNode();
//     p->assign(type, text, nullptr);
//     this->stack.emplace_back(p);
// }

// LType* TypeHelper::GPop() {
//     AstNode* back = this->stack.back();
//     this->stack.pop_back();
//     return back;
// }

// void TypeHelper::GMerge(cstring nodeSign, int n) {
//     AstNode* p = new AstNode();
//     for (int i = 0; i < n; i++) {
//         p->append(this->stack[this->stack.size() - (n - i)]);
//     }
//     for (int i = 0; i < n; i++) {
//         this->GPop();
//     }
//     p->assign(nodeSign, "", nullptr);
//     this->stack.emplace_back(p);
// }

// void TypeHelper::GPrint(cstring sign) {
//     std::cout << "--- " << sign << " ---" << std::endl;
//     if (this->stack.size() != 1) {
//         std::cout << "Tree number : " << this->stack.size() << std::endl;
//         for (int i = 0; i < this->stack.size(); i++) {
//             std::cout << i << ": ";
//             std::cout << this->GLoopUp(this->stack[i]) << std::endl;
//         }
//     } else {
//         std::cout << "Json Tree:" << std::endl;
//         std::cout << this->GLoopUp(this->stack[0]) << std::endl;
//     }
//     std::cout << "--- " << sign << " --- over" << std::endl;
// }

// nlohmann::json TypeHelper::GLoopUp(LType* node, int depth) {
//     if (node == nullptr) return nullptr;
//     nlohmann::json _r;
//     _r["name"] = node->text == "" ? node->type : node->type + ":" + node->text;
//     std::vector<nlohmann::json> children;
//     for (auto child : node->children) {
//         children.emplace_back(GLoopUp(child, depth + 1));
//     }
//     _r["children"] = nlohmann::json(children);
//     return _r;
// }


void LLambdaType::append(LType* type) {
    this->typeList.emplace_back(type);
}

void LLambdaType::setRetureType(LType* type) {
    this->returnType = type;
}


/**  */
void LScope::GEnter(cstring type, cstring name) {
    this->GPush(type, name);
    std::cout << "\r  scope: " << join<AstNode*>([](AstNode *p) {return p->text;}, this->stack, ".") << std::endl;;
}

void LScope::GExit() {
    this->GPop();
}


/**  */


void prepareCompiler() {
    astTree = new AstTree();
    rightValue = new RightValue();
    VA = new RightValue();
    MO = new TheImport();
    // symbolCollector = new TheSymbol();
    SM = new TheSymbol();

    // symbolCollector->GPush("GLOBAL", "");
    SM->GInit();
    CT = new LContext();
    typeHelper = new TypeHelper();
    TP = new TypeHelper();
    SP = new LScope();
    EX = new LExecution();

    astTree->init();
}

void releaseCompiler() {
    delete rightValue;
    delete astTree;
}

/// --------------------
/// --------------------
/// --------------------
void LContext::GPrint() {
    std::cout << "\nimport: {\n";
    for (auto& im : this->imports) {
        std::cout << "    " << im->toString() << std::endl;
    }
    std::cout << "}\n";
    // for (auto& clazz : this->clazzes) {
    //     std::cout << clazz->toString() << std::endl;
    // }
    // std::vector<std::string> _functions;
    // for (auto fun : this->functions) {
    //     _functions.emplace_back(fun->toString());
    // }
    // std::cout << "function [" << this->functions.size() <<"] {\n    ";
    // std::cout << join(_functions, "\n    ");
    // std::cout << "\n}\n";
    // std::vector<std::string> _variables;
    // for (auto var : this->variables) {
    //     _variables.emplace_back(var->toString());
    // }
    // std::cout << "variable [" << this->variables.size() <<"] {\n    ";
    // std::cout << join(_variables, "\n    ");
    // std::cout << "\n}\n";
}

std::string LFunction::toString() {
    return this->qualifier == "" 
        ? this->def + " " + this->name 
        : this->qualifier + " " + this->def + " " + this->name;
}

std::string LVariable::toString() {
    return this->qualifier == "" 
        ? this->def + " " + this->name 
        : this->qualifier + " " + this->def + " " + this->name;
}


std::string LClazz::toString() {
    std::string _r = "class " + this->name + " {\n";
    std::vector<std::string> functions;
    for (auto item : this->funs) {
        LFunction *fun = item.second;
        functions.emplace_back(fun->toString());
    }
    _r += "    " + join(functions, ";\n    ");
    _r += ";\n";
    std::vector<std::string> variables;
    for (auto item : this->vars) {
        LVariable *var = item.second;
        variables.emplace_back(var->toString());
    }
    _r += "    " + join(variables, ";\n    ");
    _r += ";\n";
    _r += "}";
    return _r;
}

/** LImport */
void LImport::append(cstring level) {
    this->pack.emplace_back(level);
}

std::string LImport::toString() {
    return join(this->pack, ".");
}
