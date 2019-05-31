#include "inversion.h"
#include "image.h"
#include <stdio.h>

int inversion
(unsigned char** image, unsigned width, unsigned height)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		_image[i] = 0xFF - _image[i];
		_image[i + 1] = 0xFF - _image[i + 1];
		_image[i + 2] = 0xFF - _image[i + 2];
	}

	return 0;
}

int inversion_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	load_image(filename, &image, &width, &height);
	inversion(&image, width, height);
	char buffer[1024];
	sprintf(buffer, "inverted_%s\0", filename);
	save_image(buffer, image, width, height);
	destroy_image(&image);

	return 0;
}