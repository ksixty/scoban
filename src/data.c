#include <stdlib.h>
#include "data.h"

// makes a cons
Cell* cons(Atom* x, Cell* y)
{
  Cell* c = malloc(sizeof(Cell));
  c->car = x;
  c->cdr = y;
  return c;
}

// copies a full list
Cell* cons_copy(Cell* x)
{
  if (x->cdr == NULL) {
    return x;
  }
  Cell* cu_x = x;
  Cell* cu_y = cons(cu_x->car, NULL);
  Cell* y = cu_y;
  Cell* nx_y; // next yu

  do {
    cu_x = cu_x->cdr;
    nx_y = cons(cu_x->car, NULL);
    cu_y->cdr = nx_y;
    cu_y = nx_y;
  } while (cu_x->cdr != NULL);

  
  return y;
}

// mutates x, y into a joint list
Cell* cons_join(Cell* x, Cell* y)
{
  if (x != y) {
    Cell* cu_x = x;
    while (cu_x->cdr != NULL) {
      cu_x = cu_x->cdr;
    }
    cu_x->cdr = y;
  }
  return x;
}
