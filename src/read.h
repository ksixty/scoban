#pragma once
#include <stdio.h>
#include "data.h"
#define ARBITRARY_NUMBER 1024
#define BOO_VALS "tf"
#define SYM_VALS "+=_-)(*&^%$#@!~<>\\|/~"

char peek(FILE* i);

Atom* read_boo(FILE* i);
Atom* read_num(FILE* i);
Atom* read_sym(FILE* i);
Atom* read_str(FILE* i);
Atom* read_lst(FILE* i);
Atom* read_quo(FILE* i);

Atom* read(FILE* i);
