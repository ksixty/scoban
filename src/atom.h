#pragma once
#include "utils.h"

typedef struct Atom Atom;
typedef enum at_types at_type;

enum at_types { T_BOO, T_NUM, T_SYM, T_STR, T_LST, T_NUL };

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
