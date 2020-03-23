#include "cons.h"
#include "utils.h"


int main(int argc, char* argv[])
{
  int a[] = {0, 1, 2, 3, 4, 5, 6};
  Cell* al = list(a, sizeof(a));
  Cell* bl = cons_copy(al);
  put_list(bl);
  put_list(cons_join(al,bl));
  return 0;
}
