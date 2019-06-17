#include "semantic.h"
#include "process.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void initInterpreter()
{
	gInterpreter.width = 0;
	gInterpreter.height = 0;
	gInterpreter.image = NULL;
	gInterpreter.input[0] = 0;
	gInterpreter.output[0] = 0;
	gInterpreter.tree = NULL;
}

int setInputFilename(char* ptr)
{
	size_t length = strlen(ptr);
	if (length > 2048)
	{
		printf("Error: Input filename %s is too long for buffer\n", ptr);
		return 1;
	}

	strcpy(gInterpreter.input, ptr);
	return 0;
}

int setOutputFilename(char* ptr)
{
	size_t length = strlen(ptr);
	if (length > 2048)
	{
		printf("Error: Output filename %s is too long for buffer\n", ptr);
		return 1;
	}

	strcpy(gInterpreter.output, ptr);
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
		//case COMMAND_AVERAGE_INDEX:
		case COMMAND_BLUR_INDEX:
			(*current)->ptrToStruct = (Blur*)malloc(sizeof(Blur));
			((Blur*)(*current)->ptrToStruct)->size = va_arg(ap, int);
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
			((Decompose*)(*current)->ptrToStruct)->functionName = va_arg(ap, unsigned char*);
			break;
		//case COMMAND_DESATURATE_INDEX:
		case COMMAND_DIFFUSE_INDEX:
			(*current)->ptrToStruct = (Diffuse*)malloc(sizeof(Diffuse));
			((Diffuse*)(*current)->ptrToStruct)->level = va_arg(ap, int);
			break;
		case COMMAND_GAMMA_INDEX:
			(*current)->ptrToStruct = (Gamma*)malloc(sizeof(Gamma));
			((Gamma*)(*current)->ptrToStruct)->ratio = va_arg(ap, double);
			break;
		case COMMAND_GRAYSHADE_INDEX:
			(*current)->ptrToStruct = (GrayShade*)malloc(sizeof(GrayShade));
			((GrayShade*)(*current)->ptrToStruct)->shades = va_arg(ap, unsigned char);
			break;
		//case COMMAND_INVERT_INDEX:
		case COMMAND_LUMINANCE_INDEX:
			(*current)->ptrToStruct = (Luminance*)malloc(sizeof(Luminance));
			((Luminance*)(*current)->ptrToStruct)->redRatio = va_arg(ap, float);
			((Luminance*)(*current)->ptrToStruct)->greenRatio = va_arg(ap, float);
			((Luminance*)(*current)->ptrToStruct)->blueRatio = va_arg(ap, float);
			break;
		case COMMAND_PIXELATE_INDEX:
			(*current)->ptrToStruct = (Pixelate*)malloc(sizeof(Pixelate));
			((Pixelate*)(*current)->ptrToStruct)->size = va_arg(ap, int);
			break;
		case COMMAND_REDUCE_INDEX:
			(*current)->ptrToStruct = (Reduce*)malloc(sizeof(Reduce));
			((Reduce*)(*current)->ptrToStruct)->level = va_arg(ap, int);
			break;
		case COMMAND_SINGLECHANNEL_INDEX:
			(*current)->ptrToStruct = (SingleChannel*)malloc(sizeof(SingleChannel));
			((SingleChannel*)(*current)->ptrToStruct)->channel = va_arg(ap, unsigned char);
			break;
		case COMMAND_SOLARISE_INDEX:
			(*current)->ptrToStruct = (Solarise*)malloc(sizeof(Solarise));
			((Solarise*)(*current)->ptrToStruct)->functionName = va_arg(ap, unsigned char*);
			((Solarise*)(*current)->ptrToStruct)->threshold = va_arg(ap, unsigned char);
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
			average(&gInterpreter.image, gInterpreter.width, gInterpreter.height);
			break;
		case COMMAND_BLUR_INDEX:
			(*current)->ptrToStruct = (Blur*)malloc(sizeof(Blur));
			((Blur*)(*current)->ptrToStruct)->size = va_arg(ap, int);
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
		((Decompose*)(*current)->ptrToStruct)->functionName = va_arg(ap, unsigned char*);
		break;
		//case COMMAND_DESATURATE_INDEX:
	case COMMAND_DIFFUSE_INDEX:
		(*current)->ptrToStruct = (Diffuse*)malloc(sizeof(Diffuse));
		((Diffuse*)(*current)->ptrToStruct)->level = va_arg(ap, int);
		break;
	case COMMAND_GAMMA_INDEX:
		(*current)->ptrToStruct = (Gamma*)malloc(sizeof(Gamma));
		((Gamma*)(*current)->ptrToStruct)->ratio = va_arg(ap, double);
		break;
	case COMMAND_GRAYSHADE_INDEX:
		(*current)->ptrToStruct = (GrayShade*)malloc(sizeof(GrayShade));
		((GrayShade*)(*current)->ptrToStruct)->shades = va_arg(ap, unsigned char);
		break;
		//case COMMAND_INVERT_INDEX:
	case COMMAND_LUMINANCE_INDEX:
		(*current)->ptrToStruct = (Luminance*)malloc(sizeof(Luminance));
		((Luminance*)(*current)->ptrToStruct)->redRatio = va_arg(ap, float);
		((Luminance*)(*current)->ptrToStruct)->greenRatio = va_arg(ap, float);
		((Luminance*)(*current)->ptrToStruct)->blueRatio = va_arg(ap, float);
		break;
	case COMMAND_PIXELATE_INDEX:
		(*current)->ptrToStruct = (Pixelate*)malloc(sizeof(Pixelate));
		((Pixelate*)(*current)->ptrToStruct)->size = va_arg(ap, int);
		break;
	case COMMAND_REDUCE_INDEX:
		(*current)->ptrToStruct = (Reduce*)malloc(sizeof(Reduce));
		((Reduce*)(*current)->ptrToStruct)->level = va_arg(ap, int);
		break;
	case COMMAND_SINGLECHANNEL_INDEX:
		(*current)->ptrToStruct = (SingleChannel*)malloc(sizeof(SingleChannel));
		((SingleChannel*)(*current)->ptrToStruct)->channel = va_arg(ap, unsigned char);
		break;
	case COMMAND_SOLARISE_INDEX:
		(*current)->ptrToStruct = (Solarise*)malloc(sizeof(Solarise));
		((Solarise*)(*current)->ptrToStruct)->functionName = va_arg(ap, unsigned char*);
		((Solarise*)(*current)->ptrToStruct)->threshold = va_arg(ap, unsigned char);
		break;
	}

	free(*node);
	return 0;
}