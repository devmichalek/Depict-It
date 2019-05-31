#include "contrast.h"
#include "error_diffusion.h"
#include "image.h"
#include <stdio.h>

int contrast
(unsigned char** image, unsigned width, unsigned height, int level)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	float factor;
	int r, g, b;
	for (; i < size * 4; i += 4)
	{
		factor = (float)((259 * ((float)level + 0xFF)) / (0xFF * (259 - (float)level)));
		r = _image[i]; g = _image[i + 1]; b = _image[i + 2];
		r = (int)(factor * (float)r - 128) + 128;
		g = (int)(factor * (float)g - 128) + 128;
		b = (int)(factor * (float)b - 128) + 128;
		_image[i] = (unsigned char)truncate(r);
		_image[i + 1] = (unsigned char)truncate(g);
		_image[i + 2] = (unsigned char)truncate(b);
	}

	return 0;
}

int contrast_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;
	char buffer[1024];

	// Plus.
	if (!load_image(filename, &image, &width, &height))
	{
		contrast(&image, width, height, 128);
		sprintf(buffer, "contrast_plus_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}
	

	// Minus.
	if (!load_image(filename, &image, &width, &height))
	{
		contrast(&image, width, height, -128);
		sprintf(buffer, "contrast_minus_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}