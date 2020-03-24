#pragma once
#include <stdlib.h>
#include "cons.h"

enum bools {
  false = 0,
  true = 1
};

typedef enum bools bool;

Cell * list(int val[], size_t valsize);
void put_list(Cell * list);
