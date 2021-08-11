// export variables and functions

#ifndef __syntax_h__
#define __syntax_h__

#ifdef __cplusplus
#  define __export_c       extern "C"
#  define __export_c_begin extern "C" {
#  define __export_c_end   }
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

extern int lealine;

__export_c void printf_empty(const char *__restrict __format, ...);

#endif//__syntax_h__