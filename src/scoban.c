#include "data.h"
#include "utils.h"
#include "read.h"
#include <stdio.h>
#include <assert.h>

#define SKOBAN_VERSION "0.006"
// 0.1 -- parser
// 0.2 -- primitives
// 0.3 -- evaluator
// 0.5 -- fully working REPL

int main(int argc, char* argv[])
{
	printf("SCOBAN v%s\n", SKOBAN_VERSION);
	read(stdin);
	return 0;
}
