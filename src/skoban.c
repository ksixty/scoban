#include "utils.h"
#include "atom.h"
#include "cons.h"
#include "read.h"

int main(int argc, char* argv[])
{
  read("(car 1 2 3)");
  return 0;
}
