// export variables and functions

#ifndef __syntax_h__
#define __syntax_h__

#ifdef __cplusplus
#  define __export_c       extern "C"
#  define __export_c_begin extern "C" {
#  define __export_c_end   }
/**
 * Just prepared for C++!
 */
struct VI_ATOM;
struct EX_ATOM;

#include <string>

void ex_push(EX_ATOM ea);
void ex_push_v(EX_ATOM ea);
void ex_push_vi(const VI_ATOM& vi);

/** assemble instruction generation */
typedef const std::string& cstring;
void as_globl_variable(EX_ATOM var, cstring name, cstring type, cstring value);
void as_globl_function(cstring name);
void as_variable(EX_ATOM var, cstring name, cstring type, cstring value);
void as_invoke();
// void g_data_def(const std::string& label, const std::string& asm_type, const std::string& value);
// void g_asm(const std::string& op, EX_ATOM& i, EX_ATOM& j, EX_ATOM& _r);
// void g_invoke(const std::string& fun, std::string args[], int size);
void g_print();

#else
#  define __export_c
#  define __export_c_begin
#  define __export_c_end
#endif

#define _p_lex printf_empty
#define leaprintf printf

#include <stdio.h>

extern FILE *yyin;
__export_c int yylex(void);
__export_c int yyparse(void);
__export_c void yyerror(const char* s);

extern int lealine;

__export_c void printf_empty(const char *__restrict __format, ...);
// vi: variable invoking
__export_c void vi_register(char* name);
__export_c void vi_args();
__export_c void vi_end_var();
__export_c void vi_end_inv();
// ex: expression
__export_c void ex_clear();
__export_c void ex_close();
__export_c void ex_push_i(int i);
__export_c void ex_push_d(double d);
__export_c void ex_push_c(char c);
__export_c void ex_push_s(char* s);
__export_c void ex_calculate(int n, char *op);
__export_c void ex_invoke(int n, char *fun);
__export_c void ex_show();
// scope
__export_c void scope_enter(char *scope);
__export_c void scope_exit();
__export_c void var_def_end();
__export_c void var_ass_end();
// bs: build symbol
__export_c void bs_function_name(char* name);
__export_c void bs_function_type(int type);
__export_c void bs_function_arg_type(char* type);
__export_c void bs_function_return_type(char* name);
__export_c void bs_function_record();
__export_c void bs_variable_name(char *name);
__export_c void bs_variable_type(int type);
__export_c void bs_variable_type_sign(char *type);
__export_c void bs_variable_type_judge();
__export_c void bs_variable_value();
__export_c void bs_variable_assign();
__export_c void bs_variable_record();
__export_c void print_symbols();

__export_c void invoke();
__export_c void invoke_close();
__export_c void invoke_move();
__export_c void invoke_args_push();

__export_c void check_main();
__export_c void declare_function();

#endif//__syntax_h__