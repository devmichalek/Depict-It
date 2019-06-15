#include "semantic.h"
#include <string.h>

#include "blur.h"
#include "brightness.h"
#include "color_reduction.h"
#include "contrast.h"
#include "error_diffusion.h"
#include "gamma_correction.h"
#include "grayscale.h"
#include "inversion.h"
#include "solarisation.h"

void initInterpreter()
{
	gInterpreter.input[0] = 0;
	gInterpreter.output[0] = 0;
	gInterpreter.bOutput = 0;
	gInterpreter.tree = NULL;
}

int setInputFilename(char* ptr)
{
	unsigned length = strlen(ptr);
	if (length > 2048)
	{
		printf("Error: Filename %s is too long for buffer\n", ptr);
		return 1;
	}

	strcpy(gInterpreter.input, ptr);
	return 0;
}

int setOutputFilename(char* ptr)
{
	unsigned length = strlen(ptr);
	if (length > 2048)
	{
		printf("Error: Filename %s is too long for buffer\n", ptr);
		return 1;
	}

	gInterpreter.bOutput = 1;
	strcpy(gInterpreter.output, ptr);
	return 0;
}

int pushStructToInterpreter(int index, int count, ...)
{
	Node** current = &gInterpreter.tree;
	while (*current)
		*current = &(*current)->next;


}