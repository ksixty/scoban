#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "atom.h"
#include "cons.h"
#include "read.h"

Atom read_boo(bool val)
{
  Atom* a = malloc(sizeof(Atom));
  a->type = T_BOO;
  a->val.boo = val;
  return *a;
}

Atom read_num(int val)
{
  Atom* a = malloc(sizeof(Atom));
  a->type = T_NUM;
  a->val.num = val;
  return *a;
}

Atom* read(char* input) {
  Atom* values = malloc(sizeof(Atom) * ARBITRARY_NUMBER);
  void* current;

  enum read_state state = 0;
  int nest = 0;
  int vali = 0;
  int curi = 0;

  char* c = input;  

  do {
    if (state == S_BASE) {
      if (isdigit(*c)) {
	current = calloc(1, sizeof(int));
	state = S_NUM;
      } else if (*c == MINUS) {
	state = S_NNUM;
      }
      else if (*c == BOO_PREFIX) {
	if (next_char(&c))
	  state = S_BOO;
      }
      else if (*c == STR_DELIM) {
	state = S_STR;
      }
      else if (*c == SEXP_START) {
	//state = S_LST;
      }
      else if (isblank(*c)) {
	;
      }
    }

    printf("%c", *c);
    
    if (state == S_BOO) {
      values[vali] = read_boo((*c = BOO_T));
      vali++;
      state = S_BASE;
    }
    
    if (state == S_NUM || state == S_NNUM) {
      if (isblank(*c)) {
	if (state == S_NNUM) {
	  *(int*)current = -(*(int*)current);
	}
	values[vali] = read_num(*(int*)current);
	printf("#<number %d>", *(int*)current);
	state = S_BASE;
	free(current);
      } else if (isdigit(*c)) {
	if(*(int*)current) {
	  append_digit((int*)current, atoi(c));
	} else {
	  *(int*)current = atoi(c);
	}
      } else {}
      
    }
    next_char(&c);
  } while(*c);
  return values;
}
