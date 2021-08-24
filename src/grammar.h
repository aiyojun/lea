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
#include <vector>
#include <string>
#include <fstream>
#include <deque>

#define debug_printf printf

/** assemble instruction generation */
typedef const std::string& cstring;

std::string join(cstring c, const std::vector<std::string>& v);

class file_writer {
public:
    void open(const std::string& s) {ostream.open(s);};
    void write(const std::string& s) {ostream << s;};
    void close() {ostream.close();};
    static std::string out;
private:
    std::ofstream ostream;
};

class runtime {
public:
    static int size_of_expect;
    static std::deque<std::string> expects;
    typedef const std::deque<std::string>& exp_q;
};

runtime::exp_q get_expects();

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
std::string declare_ro_data(cstring type, cstring v);

void g_stack_clear();
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
void mov2xmm0(cstring src);
void xmm0mov(cstring dest);
void mov4byte(cstring src, cstring dest);
void mov8byte(cstring src, cstring dest);
void mov4byte2arg(cstring src);
void mov8byte2arg(cstring src);

void function_enter(cstring);
void function_exit();
void function_call(cstring);

std::string format_gas(cstring stmt);
std::string generate_gas();

/** value.cpp */
std::string getScope();
std::string getScopeBack();

class smb {
public:
    int cls;          // classify: variable/function
    std::string name; //
    std::string type; // int double char string bool
    std::vector<std::string> typeSign; // args type list

    std::string scope;

    void clear() {cls = 0; name = ""; type = ""; scope = ""; typeSign.clear();}
};
const smb& give_variable();
const smb& give_invoking();
const smb& give_function();
const smb& query_smb(cstring name);

// tree
class tree_node;
// tree processing
void recursion_deep(tree_node* node, int depth);
// processing bool expression
bool without_boo(const std::vector<tree_node*>& vec, cstring sym);
void tree_modify_boo(tree_node* node, cstring ops);
void tree_recursion_boo(tree_node* node);
// recollect nodes of the tree
void tree_node_collect(std::vector<tree_node*>& vec, tree_node* node);

#else
#  define __export_c
#  define __export_c_begin
#  define __export_c_end
#endif

#define _p_lex printf_empty
#define leaprintf printf
__export_c void printf_empty(const char *__restrict, ...);

#include <stdio.h>

extern FILE *yyin;
extern int lealine;

__export_c int yylex(void);
__export_c int yyparse(void);
__export_c void yyerror(const char* s);

/** symbols collection */
__export_c void enter_scope();
__export_c void exit_scope();
__export_c void check(char* name);
__export_c int has_defined(char* name);
__export_c void keep(char* name);
__export_c void check_keep();
__export_c void keep_variable();
__export_c void keep_variable_type(char* type);
__export_c void keep_function();
__export_c void keep_function_type(char* type);
__export_c void keep_function_sign(char* type);
__export_c void g_function_enter();
__export_c void g_function_exit();
__export_c void keep_invoking();
__export_c void record_variable();
__export_c void record_function();

__export_c void symbol_print();

/** gas generating */
__export_c void print_gas();

/** tree version */
__export_c void tree_clear();
__export_c void invoking_deep_inc();
__export_c void invoking_deep_dec();
__export_c void heap_register(char* fun);
__export_c void heap_variable();
__export_c void heap_invoking();
__export_c void heap_invoking_args_link();
__export_c void tree_node_create(char* prefix, char* value, char* type);
__export_c void tree_node_link(char* op);

__export_c void tree_node_deep_assign();
__export_c void tree_node_print();
__export_c void tree_node_modify();
__export_c void tree_analysis(int usage);

__export_c void get_expects_back(int i, char buf[]);
__export_c void expects_push(char* token);;


/** a way to create life circle for helping parse yacc file */
#define __opt
#define __abs
// def func (x: int) : void {}
__abs void after_def();
__abs void after_fun(char*);
__opt void after_each_arg(char*);
__opt void after_each_arg_type(char*);
__opt void after_ret_type(char*);
__opt void after_fun_begin();
__abs void after_fun_end();
// if (^)^ {} else if (^)^ {} else {}
__abs void after_if();
__abs void after_if_cdt();
__opt void after_elif();
__opt void after_elif_cdt();
__opt void after_else();
__abs void after_endif();

#endif//__grammar_h__