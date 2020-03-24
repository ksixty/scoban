#pragma once
#include "utils.h"

typedef struct Atom Atom;
typedef enum at_types at_type;

enum at_types { T_BOO, T_NUM, T_SYM, T_STR, T_LST };

struct Atom {
  at_type type;
  union {
    bool  boo;
    int   num;
    char* sym;
    char* str;
    Atom* lst;
  } val;
};

void* atom_get(Atom* a);
Atom* atom_new(at_type type, void* val);

Atom* atom_str2num(Atom* a);
