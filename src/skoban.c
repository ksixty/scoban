#include "utils.h"
#include "atom.h"
#include "cons.h"
#include "read.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
  char input[ARBITRARY_NUMBER];
  char* line;
  do {
    printf("> ");
    line = fgets(input, ARBITRARY_NUMBER, stdin);
    read(input);
  } while(line != NULL);
  return 0;
}
