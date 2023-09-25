#ifndef __value_h__
#define __value_h__

class smb {
public:
    int cls;          // classify: variable/function
    std::string name; //
    std::string type; // int double char string bool
    std::vector<std::string> typeSign; // args type list

    std::string scope;

    void clear() {cls = 0; name = ""; type = ""; scope = ""; typeSign.clear();}
};
extern std::string nameTemporary;
extern smb variable;
extern smb invoking;
extern smb function;
const smb& give_variable();
const smb& give_invoking();
const smb& give_function();
const smb& query_smb(cstring name);

#endif//__value_h__