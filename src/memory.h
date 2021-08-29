#ifndef __memory_h__
#define __memory_h__

#include <map>
#include <vector>
#include <string>

#include "gas.h"
#include "basic_ds.h"



class stack { // unique stack
public:
    stack();
    void reserve1byte(cstring name);
    void reserve4bytes(cstring name);
    void reserve8bytes(cstring name);
    void declare_int(cstring name, cstring value);
    void declare_double(cstring name, cstring value);
    void declare_char(cstring name, cstring value);
    void declare_string(cstring name, cstring value);
    bool has(cstring name);
    int locate(cstring name);
private:
    std::vector<int> record_usage;
    std::map<std::string, int> recording;
    std::map<std::string, std::string> ro_string_poo;
    std::map<std::string, std::string> ro_double_poo;
    int base_ptr;
    int stack_ptr;
    int i_ptr;
};

//class section_ro_data {
//public:
//    static std::string declare_ro_data(cstring type, cstring value);
//    static int allocate_ro_data_i;
//};

#endif//__memory_h__