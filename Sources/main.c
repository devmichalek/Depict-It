#include "lodepng.h"
#include <stdio.h>
#include <stdlib.h>

int load_image(const char* filename, unsigned char** image, unsigned* width, unsigned* height)
{
	size_t pngsize;
	unsigned char* png = NULL;
	unsigned error = lodepng_load_file(&png, &pngsize, filename);

	if (!error)
		error = lodepng_decode32(image, width, height, png, pngsize);

	if (png)
		free(png);

	if (error)
	{
		printf("Error: %s\n", lodepng_error_text(error));
		return -1;
	}

	return 0;
}

int destroy_image(unsigned char** image)
{
	if (*image)
	{
		free(*image);
		return 0;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	
	return 0;
}