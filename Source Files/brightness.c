#include "brightness.h"
#include "error_diffusion.h"
#include "image.h"
#include <stdio.h>

int brightness
(unsigned char** image, unsigned width, unsigned height, int level)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		_image[i] = (unsigned char)truncate((int)_image[i] + level);
		_image[i + 1] = (unsigned char)truncate((int)_image[i + 1] + level);
		_image[i + 2] = (unsigned char)truncate((int)_image[i + 2] + level);
	}

	return 0;
}

int brightness_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;
	char buffer[1024];

	if (!load_image(filename, &image, &width, &height))
	{
		brightness(&image, width, height, 64);
		sprintf(buffer, "brightned_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}
	
	if (!load_image(filename, &image, &width, &height))
	{
		brightness(&image, width, height, -64);
		sprintf(buffer, "darkened_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}