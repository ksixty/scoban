#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// converts C array into a cons list
Cell* list(int values[], size_t valsize)
{
  Cell* c = NULL;
  size_t count = valsize / sizeof(int) - 1;
  for (int i=count; i >= 0; i--) {
    c = cons(values[i], c);
  }
  return c;
}

void put_list(Cell* list)
{
  printf("%d ", list->car);
  if (list->cdr != NULL) {
    put_list(list->cdr);
  } else {
    puts("<list>");
  }
}

void append_digit(int* num, int digit)
{
  *num = (*num * 10) + digit;
}

int next_char(char** c)
{
  *c = *c + sizeof(char);
  return **c;
}
