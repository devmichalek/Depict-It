#include "semantic.h"
#include "process.h"
#include "image.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void initInterpreter()
{
	gInterpreter.width = 0;
	gInterpreter.height = 0;
	gInterpreter.image = NULL;
	gInterpreter.input = NULL;
	gInterpreter.output = NULL;
	gInterpreter.inputAsOutput = 0;
	gInterpreter.exitState = 0;
	gInterpreter.tree = NULL;
}

int setInputFilename(char* ptr)
{
	gInterpreter.input = ptr;
	return 0;
}

int setOutputFilename(char* ptr)
{
	gInterpreter.output = ptr;
	if (!strcmp(gInterpreter.input, gInterpreter.output))
		gInterpreter.inputAsOutput = 1;
	return 0;
}

int pushToInterpreter(int index, int count, ...)
{
	// Go to the end of the list.
	Node** current = &gInterpreter.tree;
	while (*current)
		current = &((*current)->next);

	// Prepare current.
	*current = (Node*)malloc(sizeof(Node));
	(*current)->next = NULL;
	(*current)->ptrToStruct = NULL;
	(*current)->index = index;

	va_list ap;
	va_start(ap, count);
	switch (index)
	{
		case COMMAND_AVERAGE_INDEX:
			break;
		case COMMAND_BLUR_INDEX:
			(*current)->ptrToStruct = (Blur*)malloc(sizeof(Blur));
			((Blur*)(*current)->ptrToStruct)->asis = va_arg(ap, unsigned);
			break;
		case COMMAND_BRIGHTEN_INDEX:
			(*current)->ptrToStruct = (Brighten*)malloc(sizeof(Brighten));
			((Brighten*)(*current)->ptrToStruct)->level = va_arg(ap, int);
			break;
		case COMMAND_CONTRAST_INDEX:
			(*current)->ptrToStruct = (Contrast*)malloc(sizeof(Contrast));
			((Contrast*)(*current)->ptrToStruct)->level = va_arg(ap, int);
			break;
		case COMMAND_DECOMPOSE_INDEX:
			(*current)->ptrToStruct = (Decompose*)malloc(sizeof(Decompose));
			((Decompose*)(*current)->ptrToStruct)->fname = va_arg(ap, char*);
			break;
		case COMMAND_DESATURATE_INDEX:
			break;
		case COMMAND_DIFFUSE_INDEX:
			(*current)->ptrToStruct = (Diffuse*)malloc(sizeof(Diffuse));
			((Diffuse*)(*current)->ptrToStruct)->count = va_arg(ap, unsigned);
			break;
		case COMMAND_GAMMA_INDEX:
			(*current)->ptrToStruct = (Gamma*)malloc(sizeof(Gamma));
			((Gamma*)(*current)->ptrToStruct)->ratio = va_arg(ap, double);
			break;
		case COMMAND_GRAYSHADE_INDEX:
			(*current)->ptrToStruct = (GrayShade*)malloc(sizeof(GrayShade));
			((GrayShade*)(*current)->ptrToStruct)->count = va_arg(ap, unsigned);
			break;
		case COMMAND_INVERT_INDEX:
			break;
		case COMMAND_LUMINANCE_INDEX:
			(*current)->ptrToStruct = (Luminance*)malloc(sizeof(Luminance));
			((Luminance*)(*current)->ptrToStruct)->red_ratio = (float)va_arg(ap, double);
			((Luminance*)(*current)->ptrToStruct)->green_ratio = (float)va_arg(ap, double);
			((Luminance*)(*current)->ptrToStruct)->blue_ratio = (float)va_arg(ap, double);
			break;
		case COMMAND_PIXELATE_INDEX:
			(*current)->ptrToStruct = (Pixelate*)malloc(sizeof(Pixelate));
			((Pixelate*)(*current)->ptrToStruct)->pixel_size = va_arg(ap, unsigned);
			break;
		case COMMAND_REDUCE_INDEX:
			(*current)->ptrToStruct = (Reduce*)malloc(sizeof(Reduce));
			((Reduce*)(*current)->ptrToStruct)->count = va_arg(ap, unsigned);
			break;
		case COMMAND_SINGLECHANNEL_INDEX:
			(*current)->ptrToStruct = (SingleChannel*)malloc(sizeof(SingleChannel));
			((SingleChannel*)(*current)->ptrToStruct)->channel = va_arg(ap, char);
			break;
		case COMMAND_SOLARISE_INDEX:
			(*current)->ptrToStruct = (Solarise*)malloc(sizeof(Solarise));
			((Solarise*)(*current)->ptrToStruct)->threshold = va_arg(ap, unsigned);
			((Solarise*)(*current)->ptrToStruct)->fname = va_arg(ap, char*);
			break;
		default:
			va_end(ap);
			printf("Error: Unknown error occured - process semantic\n");
			return 1;
	}

	va_end(ap);
	return 0;
}

int popFromInterpreter(Node** node)
{
	switch ((*node)->index)
	{
		case COMMAND_AVERAGE_INDEX:
			if (LibCommands.average(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height))
			{
				printf("Error: Average algorithm failed...\n");
				return 1;
			}
			break;

		case COMMAND_BLUR_INDEX:
			if (LibCommands.blur(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Blur*)(*node)->ptrToStruct)->asis))
			{
				printf("Error: Blur algorithm failed...\n");
				return 1;
			}
			free((Blur*)(*node)->ptrToStruct);
			break;

		case COMMAND_BRIGHTEN_INDEX:
			if (LibCommands.brighten(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Brighten*)(*node)->ptrToStruct)->level))
			{
				printf("Error: Brighten algorithm failed...\n");
				return 1;
			}
			free((Brighten*)(*node)->ptrToStruct);
			break;

		case COMMAND_CONTRAST_INDEX:
			if (LibCommands.contrast(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Contrast*)(*node)->ptrToStruct)->level))
			{
				printf("Error: Contrast algorithm failed...\n");
				return 1;
			}
			free((Contrast*)(*node)->ptrToStruct);
			break;

		case COMMAND_DECOMPOSE_INDEX:
			if (LibCommands.decompose(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Decompose*)(*node)->ptrToStruct)->fname))
			{
				printf("Error: Decompose algorithm failed...\n");
				return 1;
			}
			free(((Decompose*)(*node)->ptrToStruct)->fname);
			free((Decompose*)(*node)->ptrToStruct);
			break;

		case COMMAND_DESATURATE_INDEX:
			if (LibCommands.desaturate(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height))
			{
				printf("Error: Desaturate algorithm failed...\n");
				return 1;
			}
			break;

		case COMMAND_DIFFUSE_INDEX:
			if (LibCommands.diffuse(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Diffuse*)(*node)->ptrToStruct)->count))
			{
				printf("Error: Diffuse algorithm failed...\n");
				return 1;
			}
			free((Diffuse*)(*node)->ptrToStruct);
			break;

		case COMMAND_GAMMA_INDEX:
			if (LibCommands.__gamma(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Gamma*)(*node)->ptrToStruct)->ratio))
			{
				printf("Error: Gamma algorithm failed...\n");
				return 1;
			}
			free((Gamma*)(*node)->ptrToStruct);
			break;

		case COMMAND_GRAYSHADE_INDEX:
			if (LibCommands.grayshade(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((GrayShade*)(*node)->ptrToStruct)->count))
			{
				printf("Error: Grayshade algorithm failed...\n");
				return 1;
			}
			free((GrayShade*)(*node)->ptrToStruct);
			break;

		case COMMAND_INVERT_INDEX:
			if (LibCommands.invert(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height))
			{
				printf("Error: Invert algorithm failed...\n");
				return 1;
			}
			break;

		case COMMAND_LUMINANCE_INDEX:
			if (LibCommands.luminance(	&gInterpreter.image,
							gInterpreter.width,
							gInterpreter.height,
							((Luminance*)(*node)->ptrToStruct)->red_ratio,
							((Luminance*)(*node)->ptrToStruct)->green_ratio,
							((Luminance*)(*node)->ptrToStruct)->blue_ratio))
			{
				printf("Error: Luminance algorithm failed...\n");
				return 1;
			}
			free((Luminance*)(*node)->ptrToStruct);
			break;

		case COMMAND_PIXELATE_INDEX:
			if (LibCommands.pixelate(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Pixelate*)(*node)->ptrToStruct)->pixel_size))
			{
				printf("Error: Pixelate algorithm failed...\n");
				return 1;
			}
			free((Pixelate*)(*node)->ptrToStruct);
			break;

		case COMMAND_REDUCE_INDEX:
			if (LibCommands.reduce(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((Reduce*)(*node)->ptrToStruct)->count))
			{
				printf("Error: Reduce algorithm failed...\n");
				return 1;
			}
			free((Reduce*)(*node)->ptrToStruct);
			break;

		case COMMAND_SINGLECHANNEL_INDEX:
			if (LibCommands.singlechannel(&gInterpreter.image,
				gInterpreter.width,
				gInterpreter.height,
				((SingleChannel*)(*node)->ptrToStruct)->channel))
			{
				printf("Error: Singlechannel algorithm failed...\n");
				return 1;
			}
			free((SingleChannel*)(*node)->ptrToStruct);
			break;

		case COMMAND_SOLARISE_INDEX:
			if (LibCommands.solarise(	&gInterpreter.image,
							gInterpreter.width,
							gInterpreter.height,
							((Solarise*)(*node)->ptrToStruct)->threshold,
							((Solarise*)(*node)->ptrToStruct)->fname))
			{
				printf("Error: Solarise algorithm failed...\n");
				return 1;
			}
			free(((Solarise*)(*node)->ptrToStruct)->fname);
			free((Solarise*)(*node)->ptrToStruct);
			break;
	}

	free(*node);
	*node = NULL;
	return 0;
}

void escapeFromInterpreter(Node** node)
{
	switch ((*node)->index)
	{
		//case COMMAND_AVERAGE_INDEX:
		case COMMAND_BLUR_INDEX:
			free((Blur*)(*node)->ptrToStruct);
			break;
		case COMMAND_BRIGHTEN_INDEX:
			free((Brighten*)(*node)->ptrToStruct);
			break;
		case COMMAND_CONTRAST_INDEX:
			free((Contrast*)(*node)->ptrToStruct);
			break;
		case COMMAND_DECOMPOSE_INDEX:
			free(((Decompose*)(*node)->ptrToStruct)->fname);
			free((Decompose*)(*node)->ptrToStruct);
			break;
		//case COMMAND_DESATURATE_INDEX:
		case COMMAND_DIFFUSE_INDEX:
			free((Diffuse*)(*node)->ptrToStruct);
			break;
		case COMMAND_GAMMA_INDEX:
			free((Gamma*)(*node)->ptrToStruct);
			break;
		case COMMAND_GRAYSHADE_INDEX:
			free((GrayShade*)(*node)->ptrToStruct);
			break;
		//case COMMAND_INVERT_INDEX:
		case COMMAND_LUMINANCE_INDEX:
			free((Luminance*)(*node)->ptrToStruct);
			break;
		case COMMAND_PIXELATE_INDEX:
			free((Pixelate*)(*node)->ptrToStruct);
			break;
		case COMMAND_REDUCE_INDEX:
			free((Reduce*)(*node)->ptrToStruct);
			break;
		case COMMAND_SINGLECHANNEL_INDEX:
			free((SingleChannel*)(*node)->ptrToStruct);
			break;
		case COMMAND_SOLARISE_INDEX:
			free(((Solarise*)(*node)->ptrToStruct)->fname);
			free((Solarise*)(*node)->ptrToStruct);
			break;
	}

	free(*node);
	*node = NULL;
}

int runInterpreter()
{
	int escape = 0;

	// Opening file...
	if (load_image(	gInterpreter.input,
					&gInterpreter.image,
					&gInterpreter.width,
					&gInterpreter.height))
		escape = 1;

	Node* ptr = gInterpreter.tree;
	if (!escape)
	{
		if (!ptr)
			escape = 1;
		else
			while (ptr)
			{
				Node* nextPtr = ptr->next;
				if (popFromInterpreter(&ptr))
				{
					printf("Error: Killing interpreter state...\n");
					escape = 1;
					break;
				}
				ptr = nextPtr;
			}
	}

	if (escape)
	{
		while (ptr)
		{
			Node* nextPtr = ptr->next;
			escapeFromInterpreter(&ptr);
			ptr = nextPtr;
		}
	}
	else
	{
		if (save_image(gInterpreter.output,
			gInterpreter.image,
			gInterpreter.width,
			gInterpreter.height))
			printf("Error: Process of saving image failed...\n");
	}

	destroy_image(&gInterpreter.image);
	free(gInterpreter.input);
	if (!gInterpreter.inputAsOutput)
		free(gInterpreter.output);

	gInterpreter.width = 0;
	gInterpreter.height = 0;
	gInterpreter.image = NULL;
	gInterpreter.input = NULL;
	gInterpreter.output = NULL;
	gInterpreter.inputAsOutput = 0;
	gInterpreter.exitState = 0;
	gInterpreter.tree = NULL;
	return escape;
}