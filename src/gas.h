#ifndef __gas_h__
#define __gas_h__

#include <string>
#include <map>
#include <vector>

typedef const std::string& cstring;

class gas {
public:
    static std::vector<std::string> g_text;
    static std::vector<std::string> g_data;
    static std::vector<std::string> g_ro_data;
    static std::vector<std::string> arg_reg;
    static int allocate_ro_data;
    static int xmm_i;
    static int arg_i;
    static int g_branch_i;
    static int bp_i;
    static std::map<std::string, int> stack_i;
    static std::map<std::string, std::string> data_g;
    static std::map<std::string, std::string> bss_g;
};

// gas.cpp
/** assemble instruction generation */
std::string ptr(cstring label);
std::string ptr_ip(cstring label);
std::string rt(int i);  // right number
std::string st(int i);  // stack space
std::string r1(cstring r);  //  low 8 bits / 1 byte
std::string rh(cstring r);  // high 8 bits
std::string r4(cstring r);  // 4 bytes => integer
std::string r8(cstring r);  // 8 bytes => long/double/pointer
std::string rx4(int r);  // 8 bytes => long/double/pointer
std::string rx8(int r);  // 8 bytes => long/double/pointer
std::string xmm(int r);
std::string declare_ro_data(cstring type, cstring v);

void g_stack_clear();
bool g_stack_has(cstring name); // ask_for
int g_stack_address(cstring name);
void stack4bytes(cstring name, cstring src);
void stack8bytes(cstring name, cstring src);
void stack_double(cstring name, cstring src);

void double2stack(cstring ro_, int i);
void ptr2stack(cstring ro_, int i);
void int2stack(int x, int i);
void byte2stack(int x, int i);
void args_clear();
void mov2xmm(cstring src);
void mov2xmm(cstring src, int i);
void mov2xmm0(cstring src);
void xmm0mov(cstring dest);
void mov4byte(cstring src, cstring dest);
void mov8byte(cstring src, cstring dest);
void mov4byte2arg(cstring src);
void mov8byte2arg(cstring src);

void function_enter(cstring);
void function_exit();
void function_call(cstring);
void gas_cmd(cstring cmd);
void gas_add4bytes(cstring src, cstring dest);
void gas_add8bytes(cstring src, cstring dest);
void gas_sub4bytes(cstring src, cstring dest);
void gas_sub8bytes(cstring src, cstring dest);
void gas_mul4bytes(cstring src, cstring dest);
void gas_mul8bytes(cstring src, cstring dest);
void gas_div4bytes(cstring src);
void gas_div8bytes(cstring src);
void gas_cmp4bytes(cstring src, cstring dest);

void sse_add_sd(cstring src, cstring dest);
void sse_cvtsi2_sd(cstring src, int i);

std::string format_gas(cstring stmt);
std::string generate_gas();

#endif//__gas_h__