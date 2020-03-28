#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "data.h"
#include "read.h"
#include "utils.h"

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

int read_isend(char* c)
{
	do {
		if (*c == '\0') {
			return true;
		}
		if (!isspace(*c)) {
			return false;
		}
	} while (next_char(&c));
	return true;
}

/*
  TODO: make read work with streams

  1. read_stream
  2. don't mutate input -- copy it instead
  3. check if the input is over, otherwise
     fail and re-read()
*/

Atom* read(char* input)
{
	do {
		if (isspace(*input)) {
			;
		} else if (read_isnum(*input)) {
			return read_num(input);
		} else if (isalnum(*input)) {
			return read_sym(input);
		} else if (read_isstr(*input)) {
			return read_str(input);
		} else if (read_islst(*input)) {
			return read_lst(input);
		} else if (read_isboo(*input)) {
			return read_boo(input);
		} else {
			printf("Error: unexpected token `%c`\n", *input);
			return NULL;
		}
	} while (next_char(&input));
	return NULL;
}

Atom* read_boo(char* c)
{
	char val = next_char(&c);
	if (read_isend(++c)) {
		if (val == 't' || val == 'f') {
			Atom* a = malloc(sizeof(Atom));
			a->type = T_BOO;
			a->val.boo = (val == 't');
			printf("#%c\n", val);
			return a;
		} else {
			printf("Error: invalid value for a boolean\n");
		}
	} else {
		printf("Error: unexpected token\n");
	}
	return NULL;
}

Atom* read_num(char* c)
{
	while (*c == '0') {
		// trim leading zeros so strtol
		// won't convert input to base 8
		next_char(&c);
	}
	errno = 0;
	char* end = NULL;
	long val = strtol(c, &end, 0);
	if (read_isend(end) && !errno) {
		Atom* a = malloc(sizeof(Atom));
		a->type = T_NUM;
		a->val.num = val;
		printf("%ld\n", a->val.num);
		return a;
	}
	printf("Error: invalid value for a number\n");
	return NULL;
}

Atom* read_sym(char* c)
{
	char* str = strsep(&c, SYM_DELIM);
	if (c == NULL || read_isend(c))
		if (!strpbrk(str, STR_DELIM)) {
			printf("[%s]\n", str);
			Atom* a = malloc(sizeof(Atom));
			a->type = T_STR;
			a->val.str = strdup(str);
			printf("%s\n", a->val.str);
			return a;
		}
	printf("Error: invalid value for a symbol\n");
	return NULL;
}

Atom* read_str(char* c)
{
	next_char(&c);
	char* start = strsep(&c, STR_DELIM);
	if (c == NULL || read_isend(c)) {
		Atom* a = malloc(sizeof(Atom));
		a->type = T_STR;
		a->val.str = strdup(start);
		printf("\"%s\"\n", a->val.str);
		return a;
	}
	printf("Error: invalid value for a string\n");
	return NULL;
}

Atom* read_lst(char* c)
{
	next_char(&c);
	char* body = strsep(&c, SEXP_END);
	char* input;
	if (c == NULL || read_isend(c)) {
		do {
			input = strsep(&body, SYM_DELIM);
			read(input);
		} while (body);
	}
	return NULL;
}
