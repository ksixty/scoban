#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "atom.h"
#include "cons.h"
#include "read.h"

int read_isnum(char s)
{
  return (s == '-') || isdigit(s);
}

int read_isstr(char s)
{
  return (s == '"');
}

int read_islst(char s)
{
  return (s == '(');
}

int read_isboo(char s)
{
  return (s == '#');
}

Atom* read(char* input) {
  Atom* v = malloc(sizeof(Atom) * ARBITRARY_NUMBER);
  char* c = input;
  do {
    v->type = T_NUL;
    if (isspace(*c)) {
      ;
    } else
    if (read_isnum(*c)) {
      read_num(&c);
      break;
    } else
    if (isalnum(*c)) {
      read_sym(&c);
      break;
    } else
    if (read_isstr(*c)) {
      read_str(&c);
      break;
    } else
    if (read_islst(*c)) {
      read_lst(&c);
    } else
    if (read_isboo(*c)) {
      read_boo(&c);
    }else {
      printf("Error: unexpected token `%c`\n", *c);
      break;
    }
    if (v->type != T_NUL) {
      v = v + sizeof(Atom);
    }
  } while (next_char(&c));
  
  return v;
}

Atom read_boo(char** c)
{
  Atom* a = malloc(sizeof(Atom));
  char val = next_char(c);
  a->type = T_NUL;
  if (isspace(next_char(c))) {
    if (val == 't') { 
      a->type = T_BOO;
      a->val.boo = true;
      printf("#%c\n", val);
    } else if (val == 'f') {
      a->type = T_BOO;
      a->val.boo = false;
      printf("#%c\n", val);	
    } else {
      printf("Error: unexpected boolean value.\n");
    }
  }
  return *a;
}

Atom read_num(char** c)
{
  Atom* a = malloc(sizeof(Atom));
  bool negative = false;
  int val;
  
  if (**c == '-') {
    negative = true;
  }
  
  val = atoi(*c);

  a->type = T_NUM;
  a->val.num = negative ? -val : val;
  printf("%d\n", val);
  return *a;
}

Atom read_sym(char** c)
{
  Atom* a = malloc(sizeof(Atom));
  char buffer[ARBITRARY_NUMBER];
  int i = 0;
  
  do { 
    if (i >= ARBITRARY_NUMBER || read_isstr(**c)) {
      printf("Error: illegal symbol\n");
      break;
    }
    if (isspace(**c)) {
      break;
    }
    buffer[i] = **c;
    i++;
  } while(next_char(c));

  size_t strsize = i++ * sizeof(char);

  a->type = T_STR;
  a->val.str = malloc(strsize);
  memcpy(a->val.str, buffer, strsize);
  printf("%s\n", a->val.str);
  return *a;
}

Atom read_str(char** c)
{
  Atom* a = malloc(sizeof(Atom));
  char buffer[ARBITRARY_NUMBER];
  int i = 0;
  bool closed = false;
  
  while (next_char(c)) {
    if (i >= ARBITRARY_NUMBER || read_isstr(**c)) {
      closed = true;
      break;
    }
    buffer[i] = **c;
    i++;
  }
  if (i == 1) {
    printf("Error: zero-length string\n");
    a->type = T_NUL;
    return *a;
  }
  if (!closed) {
    printf("Error: no `\"` to match\n");
    return *a;
  }
  buffer[i] = '\0';
  size_t strsize = i++ * sizeof(char);

  a->type = T_STR;
  a->val.str = malloc(strsize);
  memcpy(a->val.str, buffer, strsize);
  printf("\"%s\"\n", a->val.str);
  return *a;
}

Atom read_lst(char** c)
{
  printf("lst %c\n", **c);
  return *(Atom*)(malloc(sizeof(Atom)));
}
