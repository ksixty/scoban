#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "read.h"
#include "utils.h"

char peek(FILE* i)
{
	char c = getc(i);
	ungetc(c, i);
	return c;
}

Atom* read(FILE* i)
{
	char c;
	char* b = malloc(sizeof(char) * ARBITRARY_NUMBER);
	Atom* a = malloc(sizeof(Atom));

	while (1) {
		char c = getc(i);
		if (isspace(c)) {
			continue;
		} else if (c == '#') {
			a = read_boo(i);
		} else if (isdigit(c) || c == '-') {
			ungetc(c, i);
			a = read_num(i);
		} else if (isalnum(c)) {
			ungetc(c, i);
			a = read_sym(i);
		} else if (c == '"') {
			a = read_str(i);
		} else if (c == '[') {
			a = read_lst(i);
		} else if (c == ']') {
			continue; // TODO: do something about it
		} else if (c == '\'') {
			a = read_quo(i);
	        } else if (c == EOF) {
			return NULL;
		} else {
			error(E_INV);
		}
	}
}

Atom* read_boo(FILE* i)
{
	char val = getc(i);
	if (strchr(BOO_VALS, val) && isblank(peek(i)))
	{
		Atom* a = malloc(sizeof(Atom));
		a->type = T_BOO;
		a->val.boo = (val == 't');
		return a;
	} else {
		return NULL;
	}
}

Atom* read_num(FILE* i)
{
	bool neg = false;
	int val;
	char c = getc(i);
	if (c == '-' && isdigit(peek(i))) {
		neg = true;
		c = getc(i);
	} else {
		return NULL;
	}
	while (isdigit(c)) {
		val = val * 10 + (c - '0');
		c = getc(i);
	}
	Atom* a = malloc(sizeof(Atom));
	a->type = T_NUM;
	a->val.num = neg ? -val : val;
	return a;
}

Atom* read_sym(FILE* i)
{
	char val[ARBITRARY_NUMBER];
	int pos = 0;
	char c = getc(i);
	while (strchr(SYM_VALS, c) || isalnum(c)) {
		val[pos] = c;
		pos++;
		c = getc(i);
	}
	Atom* a = malloc(sizeof(Atom));
	a->type = T_SYM;
	a->val.sym = strndup(val, sizeof(char) * pos);
	return a;
}

Atom* read_str(FILE* i)
{
	char val[ARBITRARY_NUMBER];
	int pos = 0;
	char c = getc(i);
	while (c != EOF) {
		if (c == '"') {
			break;
		}
		if (c == '\\') { // TODO: put into a function
			c = getc(i);
			char tmp;
			switch(c) {
			case 'n':
				tmp = '\n';
				break;
			case '"':
				tmp = '\"';
				break;
			default:
				error(E_TOK);
				break;
			}
		}
		if (pos > ARBITRARY_NUMBER) {
			error(E_LEN);
		}
		val[pos] = c;
		pos++;
		c = getc(i);
	}
	Atom* a = malloc(sizeof(Atom));
	a->type = T_STR;
	a->val.str = strndup(val, sizeof(char) * pos);
	return a;
}

Atom* read_lst(FILE* i)
{
        while (peek(i) != ')') {
		;
	}
	return NULL;
}

Atom* read_quo(FILE* i)
{
	// return a list: (quote read(i))
	Atom* val = read(i);
	if (val == NULL) {
		return NULL;
	}
	Atom* q = malloc(sizeof(Atom));
	q->type = T_SYM;
	q->val.sym = "quote";
	Atom* a = malloc(sizeof(Atom));
	a->type = T_LST;
	a->val.lst = cons(q, cons(val, nil));
	return NULL;
}
