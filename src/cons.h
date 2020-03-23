#pragma once

typedef struct Cell Cell;

struct Cell {
  int car; // would be a void* one day
  Cell* cdr;
};

Cell* cons(int x, void* y);
Cell* cons_copy(Cell* x);
Cell* cons_join(Cell*x, Cell*y);
