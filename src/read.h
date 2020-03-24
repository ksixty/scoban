#pragma once

#define ARBITRARY_NUMBER 1024

#define MINUS       '-'
#define SEXP_START  '('
#define SEXP_END    ')'
#define PAIR_DELIM  '.'
#define STR_DELIM   '"'
#define BOO_PREFIX  '#'
#define BOO_T 't'

enum read_state { S_BASE, S_BOO, S_NUM, S_NNUM,
		  S_SYM, S_STR, S_LST };

Atom read_boo(bool val);
Atom read_num(int val);
Atom read_sym(char* val, size_t valsize);

Atom* read(char* input);
