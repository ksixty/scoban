#pragma once
#include "data.h"
#define ARBITRARY_NUMBER 1024

#define STR_DELIM "\""
#define SYM_DELIM "\t\n\v\f\r \0"
#define SEXP_END ")"

int read_isnum(char s); // [0-9] or -
int read_isboo(char s); // #
int read_isstr(char s); // (
int read_islst(char s); // "

int read_isend(char* c); // token must end with whitespace

Atom* read_boo(char* c);
Atom* read_num(char* c);
Atom* read_sym(char* c);
Atom* read_str(char* c);
Atom* read_lst(char* c);

Atom* read(char* input);
