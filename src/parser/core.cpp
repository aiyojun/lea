#include "core.h"

#include <iostream>

AstTree* astTree;
RightValue *rightValue;
TheImport* importer;
TheSymbol* symbolCollector;

void AstNode::assign(cstring type, cstring text, AstNode* parent) {
    this->type = type; this->text = text; this->parent = parent;
    if (parent != nullptr)
        parent->append(this);
}

void AstNode::append(AstNode* child) {
    this->children.emplace_back(child);
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
    std::cout << "[E] Type(" << nodeSign << "), Depth(" << n << ")\n";
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

/** The import */

void TheImport::initDepth() {
    this->depth = 0;
}

void TheImport::addDepth() {
    this->depth++;
}

int TheImport::resetDepth() {
    int _r = this->depth;
    this->depth = 0;
    return _r;
}

void TheImport::init() {
    this->deps = 0;
    this->depth = 0;
}

void TheImport::recordOne() {
    this->deps++;
}

int TheImport::resetAll() {
    int _r = this->deps;
    this->deps = 0;
    return _r;
}

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
    std::cout << ">> release scope : " << _r << ", rest : " << this->scopeCount.size() << "\n";
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

void TheSymbol::merge(cstring nodeSign, int n) {
    std::cout << "[E] Type(" << nodeSign << "), Depth(" << n << ")\n";
    AstNode* p = new AstNode();
    for (int i = 0; i < n; i++) {
        p->append(this->symbols[this->symbols.size() - (n - i)]);
    }
    for (int i = 0; i < n; i++) {
        this->popStack();
    }
    p->assign(nodeSign, "", nullptr);
    this->symbols.emplace_back(p);
}

void TheSymbol::pushStack(cstring type, cstring text) {
    AstNode* p = new AstNode();
    p->assign(type, text, nullptr);
    this->symbols.emplace_back(p);
}

AstNode* TheSymbol::popStack() {
    AstNode* back = this->symbols.back();
    this->symbols.pop_back();
    return back;
}

nlohmann::json TheSymbol::loopUp(AstNode* node, int depth)
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

void TheSymbol::print() {
    if (this->symbols.size() != 1) {
        std::cout << "start size : " << this->symbols.size() << std::endl;
        for (int i = 0; i < this->symbols.size(); i++) {
            std::cout << "The " << i << " tree:\n";
            std::cout << this->loopUp(this->symbols[i]) << std::endl;
            std::cout << "over\n\n";
        }
    } else {
        std::cout << "Tree:" << std::endl;
        std::cout << this->loopUp(this->symbols[0]) << std::endl;
    }
}

/**  */


void prepareCompiler() {
    astTree = new AstTree();
    rightValue = new RightValue();
    importer = new TheImport();
    symbolCollector = new TheSymbol();
    astTree->init();
}

void releaseCompiler() {
    delete rightValue;
    delete astTree;
}