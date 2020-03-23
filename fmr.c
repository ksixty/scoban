#include <stdio.h>
#include <stdlib.h>

typedef struct Cells
{
  int car; // would be a void* one day
  struct Cells* cdr;
} Cell;

Cell* cons(int x, void* y)
{
  Cell* c = malloc(sizeof(Cell));
  c->car = x;
  c->cdr = y;
  return c;
}

Cell* list(int values[], size_t valsize)
{
  Cell* c = NULL;
  size_t count = valsize / sizeof(int) - 1;
  for (int i=count; i >= 0; i--) {
    c = cons(values[i], c);
  }
  return c;
}

Cell* joinl(Cell* x, Cell* y)
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

Cell* copyl(Cell* x)
{
  if (x->cdr == NULL) {
    return x;
  }
  Cell* cu_x = x;
  Cell* cu_y = cons(cu_x->car, NULL);
  Cell* y = cu_y;    
  Cell* nx_y;
  
  do {
    cu_x = cu_x->cdr;
    nx_y = cons(cu_x->car, NULL);
    cu_y->cdr = nx_y;
    cu_y = nx_y;
  } while (cu_x->cdr != NULL);
  
  return y;    
}

void putl(Cell* list)
{
  printf("%d ", list->car);
  if (list->cdr != NULL) {
    putl(list->cdr);
  } else {
    puts("<list>");
  }
}

int main(int argc, char* argv[])
{
  int a[] = {0, 1, 2, 3, 4, 5, 6};
  Cell* al = list(a, sizeof(a));
  Cell* bl = copyl(al);
  putl(bl);
  putl(joinl(al,bl));
  return 0;
}
