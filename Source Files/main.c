#include "parse.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc > 1)
	{	// more arguments
		char** first_arg = argv + 1; // skip current directory
		size_t total_size = 2 + argc - 1;	// \n + \0 + n spaces
		char** ptr = first_arg;
		while (*ptr) {
			total_size += strlen(*ptr);
			++ptr;
		}

		char* huge_str = (char*)malloc(sizeof(char) * total_size);
		char* h = huge_str;
		ptr = first_arg;
		while (*ptr)
		{
			char* c = *ptr;
			while (*c)
			{
				*(h++) = *(c++);
			}
			++ptr;
			if (*ptr)
				*(h++) = ' ';
		}
		*(h++) = '\n';
		*h = '\0';

		start_scanning(huge_str);
		end_scanning();
		free(huge_str);
	}
	else
	{
		while (!gInterpreter.exitState)
			parse();

		printf("Press enter to continue...\n");
		char enter = 0;
		while (enter != '\r' && enter != '\n')
			enter = getchar();
	}

	return 0;
}