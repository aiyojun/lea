#include "memory.h"

#include "grammar.h"

stack::stack() {
    base_ptr = 0; stack_ptr = 0; i_ptr = 0;
}
void stack::reserve1byte(cstring name) {
    i_ptr += 1;
    recording[name] = i_ptr;
}
void stack::reserve4bytes(cstring name) {
    i_ptr += 4;
    recording[name] = i_ptr;
}
void stack::reserve8bytes(cstring name) {
    i_ptr += 8;
    recording[name] = i_ptr;
}
void stack::declare_int(cstring name, cstring value) {
    i_ptr += 4;
    mov4byte(rt(atoi(value.c_str())), st(i_ptr));
    recording[name] = i_ptr;
}
void stack::declare_double(cstring name, cstring value) {
    i_ptr += 8;
    std::string ro_label;
    std::string val = double_sci(value);
    if (contains(ro_double_poo, val)) {
        ro_label = ro_double_poo[val];
    } else {
        ro_label = declare_ro_data("double", val);
    }
    mov8byte(ptr(ro_label), xmm(0));
    mov8byte(xmm(0), st(i_ptr));
    recording[name] = i_ptr;
}
void stack::declare_char(cstring name, cstring value) {
    i_ptr += 1;
    std::string val = un_quote(value);
    mov4byte(rt((int) val[0]), st(i_ptr));
}
void stack::declare_string(cstring name, cstring value) {
    i_ptr += 8;
    std::string ro_label;
    std::string val = un_quote(value);
    if (contains(ro_string_poo, val)) {
        ro_label = ro_double_poo[val];
    } else {
        ro_label = declare_ro_data("string", val);
    }
    mov8byte(ptr(ro_label), st(i_ptr));
    recording[name] = i_ptr;
}

bool stack::has(cstring name) {
    return contains(recording, name);
}

int stack::locate(cstring name) {
    if (!has(name)) throw std::runtime_error("stack::locate error");
    return recording[name];
}

//int section_ro_data::allocate_ro_data_i = 0;
//
//std::string section_ro_data::declare_ro_data(cstring type, cstring value) {
//    std::string label = ".LC"+std::to_string(++section_ro_data::allocate_ro_data_i);
//    gas::g_ro_data.emplace_back(label+":");
//    if (type == "double") gas::g_ro_data.emplace_back(".double "+value);
//    else if (type == "string") gas::g_ro_data.emplace_back(".string "+ quote(value));
//    else yyerror(".rodata allocate error!");
//    return label;
//}