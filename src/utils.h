#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef enum Errors Error;

enum Errors {
	E_HNL = -1,// хнуль
	E_NUL, // null
	E_EOS, // unexpected end of stream
	E_PAR, // unbalanced parentheses
	E_TOK, // invalid token
	E_LEN, // length exceeded
	E_INV // invalid input
};

Cell* list(int val[], size_t valsize);
void put_list(Cell* list);

void append_digit(int* num, int digit);
int next_char(char** c);

void error(Error e);
