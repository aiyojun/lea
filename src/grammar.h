// export variables and functions
#ifndef __grammar_h__
#define __grammar_h__

/** grammar.h prepared for lex&yacc files */
#define debug_printf printf
#define __export_c
#define _p_lex printf_empty
#define leaprintf printf

extern int lealine;

__export_c void yyerror(const char* s);
__export_c void printf_empty(const char *__restrict, ...);

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
__export_c void tree_analysis(int usage);

__export_c void get_expects_back(int i, char buf[]);
__export_c void expects_push(char* token);

///** a way to create life circle for helping parse yacc file*/
//#define __opt
//#define __abs
//// def func (x: int) : void {}
//__abs void after_def();
//__abs void after_fun(char*);
//__opt void after_each_arg(char*);
//__opt void after_each_arg_type(char*);
//__opt void after_ret_type(char*);
//__opt void after_fun_begin();
//__abs void after_fun_end();
//// if (^)^ {} else if (^)^ {} else {}
//__abs void after_if();
//__abs void after_if_cdt();
//__opt void after_elif();
//__opt void after_elif_cdt();
//__opt void after_else();
//__abs void after_endif();

#include "gas.h"
#include "branch.h"
#include "runtime.h"
#include "tree.h"
#include "value.h"

#endif//__grammar_h__