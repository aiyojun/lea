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
void g_asm(const std::string& op, EX_ATOM& i, EX_ATOM& j, EX_ATOM& _r);
void g_invoke(const std::string& fun, std::string args[], int size);
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

__export_c void vi_register(char* name);
__export_c void vi_args();
__export_c void vi_end_var();
__export_c void vi_end_inv();

__export_c void ex_close();
__export_c void ex_push_i(int i);
__export_c void ex_push_d(double d);
__export_c void ex_push_c(char c);
__export_c void ex_push_s(char* s);
__export_c void ex_calculate(int n, char *op);
__export_c void ex_invoke(int n, char *fun);
__export_c void ex_show();

#endif//__syntax_h__