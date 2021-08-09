//
// Created by Mr.Jun on 2021/8/6.
//

#ifndef __grammar_h__
#define __grammar_h__

#ifdef __cplusplus
#  define __export_c       extern "C"
#  define __export_c_begin extern "C" {
#  define __export_c_end   }
/**
 * Inner use for cpp
 */
void declare(const char* _identifier);
void declare(const char* _identifier, const char* context);
#else
#  define __export_c
#  define __export_c_begin
#  define __export_c_end
#endif

/**
 * Prepared for 'lea.y'
 */
#define _p_lex printf_empty
#define _p_yacc printf_empty

extern long lea_line;

__export_c void printf_empty(const char *__restrict __format, ...);

__export_c void _lea(char *name);
__export_c void _line_inc();

__export_c void _push(char *s);
__export_c void _pull(char *s);

__export_c void _open_mc();
__export_c void _close_mc();

__export_c void _scope_ano(long line);
__export_c void _scope_begin(char *scope);
__export_c void _scope_end(char *scope);

__export_c void _if();
__export_c void _elif();
__export_c void _else();
__export_c void _for();
__export_c void _match();
__export_c void _case();
__export_c void _def(char* fun_name);
__export_c void _block();
__export_c void _block_();
__export_c void _add_arg();
__export_c void _call(int args);
__export_c void _var_def(char* var_name);
__export_c void _var_ass(char* var_name);
__export_c void _var_def_ass(char* var_name);

__export_c void clean();
__export_c void complete();

#endif//__grammar_h__