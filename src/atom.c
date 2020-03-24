#include <stdlib.h>
#include <stdio.h>
#include "atom.h"

Atom * atom_new(at_type type, void * val)
{
  Atom * a = malloc(sizeof(Atom));
  a->type = type;
  switch(type){
  case (T_BOO):
    a->val.boo = *(bool *)val;
    break;
  case (T_NUM):
    a->val.num = *(int *)val;
    break;
  case (T_SYM):
    a->val.sym = (char *)val;
    break;
  }
  return a;
}

void * atom_get(Atom * a)
{
  switch(a->type) {
  case (T_BOO):
    return &(a->val.boo);
    break;
  case (T_NUM):
    return &(a->val.num);
        break;
  case (T_SYM):
    return a->val.sym;
    break;
  }
}
