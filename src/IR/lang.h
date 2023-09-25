#ifndef LEA_LANG_H
#define LEA_LANG_H

#include <string>
#include <vector>
#include <map>


// --------------------------------------------------------------------
// prefix class declarations
class IValue;
class VString;
class VChar;
class VTure;
class VFalse;
class VDouble;
class VInteger;
class Evaluation;

// --------------------------------------------------------------------

class Nameable {
public:
    void setName(const std::string& name) { this->_name = name; }
    const std::string& name() { return _name; }
private:
    std::string _name;
};
// ---------------------------------------------------------------------
// Type system
enum LangType {
    VOID, INT8, INT16, INT32, INT64,
    UINT8, UINT16, UINT32, UINT64,
    FLOAT, DOUBLE, CHAR, BOOLEAN,
    ARRAY, REFERENCE
};

class IType {
public:
    static IType *typeVoid;
    static IType *typeInt8;
    static IType *typeInt16;
    static IType *typeInt32;
    static IType *typeInt64;
    static IType *typeUInt8;
    static IType *typeUInt16;
    static IType *typeUInt32;
    static IType *typeUInt64;
    static IType *typeFloat;
    static IType *typeDouble;
    static IType *typeChar;
    static IType *typeBoolean;
protected:
    explicit IType(LangType langType) {_typeIndex = langType;}
    LangType _typeIndex;
};

class IObjectType : public IType, public Nameable {
private:

};


class IArrayType : public IType {
private:
    IType *_elementType;
};
// ---------------------------------------------------------------------
// Value system
class IValue {};

class VString : public IValue {
public:
    static VString *build(const std::string& s);
    void setValue(std::string s) {_value = std::move(s);}
    const std::string& value() {return _value;}
private:
    explicit VString(std::string s) {_value = std::move(s);};
private:
    std::string _value;
    friend class Runtime;
};

class VChar : public IValue {
public:
    static VChar *build(char c) { return new VChar(c); }
    void setValue(char c) {_value = c;}
    char value() {return _value;}
private:
    VChar(char c) {_value = c;}
private:
    char _value;
};

//class VNumber {
//private:
//};

class VTure : public IValue {
public:
    static VTure *self() { if (VTure::_self == nullptr) VTure::_self = new VTure; return VTure::_self; }
private:
    VTure() = default;
    static VTure *_self;
};
class VFalse: public IValue {
public:
    static VFalse *self() { if (VFalse::_self == nullptr) VFalse::_self = new VFalse; return VFalse::_self; }
private:
    VFalse() = default;
    static VFalse *_self;
};

class VInteger : public IValue {
public:
    static VInteger *build(int i) { return new VInteger(i); }
    void setValue(int i) {_value = i;}
    int value() {return _value;}
private:
    VInteger(int i) {_value = i;}
private:
    int _value;
};

class VDouble : public IValue {
public:
    static VDouble *build(double d) { return new VDouble(d); }
    void setValue(double d) {_value = d;}
    double value() {return _value;}
private:
    VDouble(double d) {_value = d;}
private:
    double _value;
};

class Evaluation : public IValue {
public:

private:
    IType *_datatype;
};

// ---------------------------------------------------------------------
class IArg {
public:
    static IArg* build(const std::string& type, const std::string& name);
private:
    std::string _formalParameterName;
    IType *_datatype;
};

class IClass : public Nameable {

};

class IFunction : public Nameable {
public:
    static IFunction* build();
    void addArgument(const IArg* arg) {_argumentList.emplace_back(arg);}
    size_t argumentNumber() {return _argumentList.size();}
    const IArg* argument(size_t i) {return _argumentList[i];}
private:
    std::vector<IArg *> _argumentList;
};

class IStatement {
public:

private:
};

class IAccessible {
protected:
    IType *_datatype;
};

class IVariable : public IAccessible, public Nameable {
private:
    IType *_datatype;
};

class IArrayAccess : public IAccessible {
public:

private:
};

class IClassMemberAccess : public IAccessible {
public:

private:
};

class IAssignment : public IStatement {
public:

private:
    IAccessible *_accessibleObject;
    Evaluation *_evaluation;
};

class IVariableDeclaration : public IStatement {
public:

private:
    std::string _variableName;
    IType *_variableType;
};

class IBlock {
public:
    void addStatement(IStatement* statement) {_statements.emplace_back(statement);}
    size_t getStatementNumber() {return _statements.size();}
    IStatement *statement(size_t i) {return _statements[i];}
private:
    std::vector<IStatement *> _statements;
};


// -----------------------------------------------------------------------------------
class Runtime {
public:
    static Runtime *self() { if (Runtime::_self == nullptr) Runtime::_self = new Runtime; return Runtime::_self; }
    VString *getConstantString(const std::string& s);
private:
    static Runtime *_self;
private:
    Runtime() = default;
private:
    std::map<std::string, IType *> _allTypes;
    std::map<std::string, IVariable *> _globalVariables;
    std::map<std::string, VString *> _constantStringPool;
};

#endif //LEA_LANG_H
