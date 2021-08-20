// export variables and functions
#ifndef __grammar_h__
#define __grammar_h__

#ifdef __cplusplus
#  define __export_c       extern "C"
#  define __export_c_begin extern "C" {
#  define __export_c_end   }
/**
 * Just prepared for C++!
 */
#include <string>
#include <fstream>

/** assemble instruction generation */
typedef const std::string& cstring;

class file_writer {
public:
    void open(const std::string& s) {ostream.open(s);};
    void write(const std::string& s) {ostream << s;};
    void close() {ostream.close();};
    static std::string out;
private:
    std::ofstream ostream;
};

std::string ptr(cstring label);
std::string rt(int i);  // right number
std::string st(int i);  // stack space
std::string r1(cstring r);  //  low 8 bits / 1 byte
std::string rh(cstring r);  // high 8 bits
std::string r4(cstring r);  // 4 bytes => integer
std::string r8(cstring r);  // 8 bytes => long/double/pointer
std::string rx4(int r);  // 8 bytes => long/double/pointer
std::string rx8(int r);  // 8 bytes => long/double/pointer
std::string declare_ro_data(cstring type, cstring v);
void double2stack(cstring ro_, int i);
void ptr2stack(cstring ro_, int i);
void int2stack(int x, int i);
void byte2stack(int x, int i);
void args_clear();
void mov2xmm(cstring src);
void mov4byte(cstring src, cstring dest);
void mov8byte(cstring src, cstring dest);
void mov4byte2arg(cstring src);
void mov8byte2arg(cstring src);

void function_enter(cstring);
void function_exit();
void function_call(cstring);

std::string format_gas(cstring stmt);
std::string generate_gas();

#else
#  define __export_c
#  define __export_c_begin
#  define __export_c_end
#endif

#define _p_lex printf_empty
#define leaprintf printf
__export_c void printf_empty(const char *__restrict __format, ...);

#include <stdio.h>

extern FILE *yyin;
__export_c int yylex(void);
__export_c int yyparse(void);
__export_c void yyerror(const char* s);

extern int lealine;

__export_c void symbol_print();
__export_c void stack_clear();
__export_c void heap_value(char*, char*, char*);
__export_c void heap_print();
__export_c void heap_var_validate();
__export_c void heap_inv_validate();
__export_c void heap_var();
__export_c void heap_inv();
__export_c void heap_inv2();
__export_c void heap_inv_args_inc();
__export_c void val_register(char*);
__export_c void val_register2(char*);
__export_c void heap_deep_inc();
__export_c void heap_deep_dec();

__export_c void heap_inv_exe();
__export_c void calc_mul();
__export_c void calc_div();
__export_c void calc_add();
__export_c void calc_sub();
__export_c void comp_gt();
__export_c void comp_gte();
__export_c void comp_lt();
__export_c void comp_lte();
__export_c void comp_eq();
__export_c void comp_ne();
__export_c void comp_and();
__export_c void comp_or();
__export_c void comp_not();

__export_c void variable_register(int mode);
__export_c void variable_type(char* type);
__export_c void variable_record();
__export_c void variable_assign_v2();
__export_c void variable_already_exist();

__export_c void function_record();
__export_c void function_name(char*);
__export_c void function_type(int);
__export_c void function_push_args_type(char*);
__export_c void function_return(char*);

__export_c void g_function_imp();
__export_c void g_function_over();
__export_c void g_function_return();
__export_c void print_gas();

__export_c void tree_init();
__export_c void tree_release();
__export_c void tree_append(int);
__export_c void tree_print();
__export_c void bo_deep_inc();
__export_c void bo_deep_dec();

#endif//__grammar_h__