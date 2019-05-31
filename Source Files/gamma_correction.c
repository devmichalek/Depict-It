#include "gamma_correction.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

int gamma_correction
(unsigned char** image, unsigned width, unsigned height, double level)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		_image[i] = (unsigned char)(0xFF * pow(((float)_image[i] / 0xFF), level));
		_image[i + 1] = (unsigned char)(0xFF * pow(((float)_image[i + 1] / 0xFF), level));
		_image[i + 1] = (unsigned char)(0xFF * pow(((float)_image[i + 1] / 0xFF), level));
	}

	return 0;
}

int gamma_correction_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		gamma_correction(&image, width, height, 0.25);
		char buffer[1024];
		sprintf(buffer, "gamma_0_25%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		gamma_correction(&image, width, height, 2.0);
		char buffer[1024];
		sprintf(buffer, "gamma_2_00_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}