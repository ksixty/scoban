#pragma once

typedef struct Atom Atom;
typedef enum at_types at_type;
typedef struct Cell Cell;
typedef enum bools bool;

enum bools { false = 0, true = 1};

enum at_types { T_BOO, T_NUM, T_SYM, T_STR, T_LST };

struct Atom {
  at_type type;
  union {
    bool  boo;
    long  num;
    char* sym;
    char* str;
    Cell* lst;
  } val;
};

struct Cell {
  Atom* car;
  Cell* cdr;
};

Cell* cons(Atom* x, Cell* y);
Cell* cons_copy(Cell* x);
Cell* cons_join(Cell*x, Cell*y);
