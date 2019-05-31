#include "solarisation.h"
#include "image.h"
#include <stdio.h>

int solarise_below
(unsigned char* channel, unsigned char* threshold)
{
	return *channel < *threshold;
}

int solarise_above
(unsigned char* channel, unsigned char* threshold)
{
	return *channel > *threshold;
}

int solarisation
(unsigned char** image, unsigned width, unsigned height, unsigned char threshold, int(*fun)(unsigned char*, unsigned char*))
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		if (fun(&_image[i], &threshold))		_image[i] = 0xFF - _image[i];
		if (fun(&_image[i + 1], &threshold))	_image[i + 1] = 0xFF - _image[i + 1];
		if (fun(&_image[i + 2], &threshold))	_image[i + 2] = 0xFF - _image[i + 2];
	}

	return 0;
}

int solarisation_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;
	char buffer[1024];

	// Solarise below.
	load_image(filename, &image, &width, &height);
	solarisation(&image, width, height, 0xFF / 2, solarise_below);
	sprintf(buffer, "solarised_below_%s\0", filename);
	save_image(buffer, image, width, height);
	destroy_image(&image);

	// Solarise above.
	load_image(filename, &image, &width, &height);
	solarisation(&image, width, height, 0xFF / 2, solarise_above);
	sprintf(buffer, "solarised_above_%s\0", filename);
	save_image(buffer, image, width, height);
	destroy_image(&image);

	return 0;
}