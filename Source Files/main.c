#include "parse.h"
#include "semantic.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	while (!gInterpreter.exitState)
		parse();

	printf("Press enter to continue...\n");
	char enter = 0;
	while (enter != '\r' && enter != '\n')
		enter = getchar();

	return 0;
}