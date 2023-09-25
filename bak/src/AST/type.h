#ifndef __type_h__
#define __type_h__

#include <string>
#include <vector>
typedef const std::string& cstring;

class lea_var {
public:
    std::string scope;
    std::string prefix;
    std::string name;
    std::string type;
    std::string lea_var_type;
    bool assigned = false;
    void clear() {scope="";prefix="";name="";type="";lea_var_type="";assigned=false;}
};

class lea_fun {
public:
    std::string scope;
    std::string prefix;
    std::string name;
    std::string return_type;
    std::vector<std::string> args_type;
    bool implemented = false;
    std::string scene;
    void clear() {scope="";prefix="";name="";return_type="";args_type.clear(); implemented=false;scene="";}
};

class lea_cls {
public:
    std::string name;
    std::vector<lea_var> memberVariables;
    std::vector<lea_fun> memberFunctions;
    void clear() {name="";memberVariables.clear();memberFunctions.clear();}
};

class lea_ctx {
public:
    std::vector<std::string> globalImports;
    std::vector<lea_var> globalVariables;
    std::vector<lea_fun> globalFunctions;
    std::vector<lea_cls> globalClasses;
};


/** type index */
class lea_mo {
public:

}

#endif//__type_h__