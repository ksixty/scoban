#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "utils.h"

void put_list(Cell* list)
{
  printf("<Atom/%d>", list->car->type);
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
  ++(*c);
  return **c;
}
