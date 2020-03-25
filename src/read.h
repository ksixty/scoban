#pragma once
#define ARBITRARY_NUMBER 1024

int read_isnum(char s); // [0-9] or -
int read_isboo(char s); // #
int read_isstr(char s); // (
int read_islst(char s); // "

Atom read_boo(char** c);
Atom read_num(char** c);
Atom read_sym(char** c);
Atom read_str(char** c);
Atom read_lst(char** c);

Atom* read(char* input);
