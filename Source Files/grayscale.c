#include "grayscale.h"
#include "image.h"
#include <stdio.h>

int grayscale_averaging
(unsigned char** image, unsigned width, unsigned height, float average)
{
	unsigned char* _image = *image;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Make an average of read, green and blue.
		gray = (_image[i] + _image[i + 1] + _image[i + 2]) / average;
		_image[i] = (unsigned char)gray;
		_image[i + 1] = (unsigned char)gray;
		_image[i + 2] = (unsigned char)gray;
	}
	return 0;
}

int grayscale_luminance
(unsigned char** image, unsigned width, unsigned height, float ar, float ag, float ab)
{
	unsigned char* _image = *image;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Treat each channel separately.
		gray = ((_image[i] * ar) + (_image[i + 1] * ag) + (_image[i + 2] * ab));
		_image[i] = (unsigned char)gray;
		_image[i + 1] = (unsigned char)gray;
		_image[i + 2] = (unsigned char)gray;
	}
	return 0;
}

unsigned char minRGB
(unsigned char* rgb)
{
	unsigned char* ptr = rgb;
	unsigned char smallest = 0xFF;
	for (unsigned i = 0; i < 3; ++i, ++ptr)
		if (*ptr < smallest)
			smallest = *ptr;
	return smallest;
}

unsigned char maxRGB
(unsigned char* rgb)
{
	unsigned char* ptr = rgb;
	unsigned char greatest = 0x00;
	for (unsigned i = 0; i < 3; ++i, ++ptr)
		if (*ptr > greatest)
			greatest = *ptr;
	return greatest;
}

int grayscale_desaturation
(unsigned char** image, unsigned width, unsigned height)
{
	unsigned char* _image = *image;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Convert RGB to HSL and force the saturation to 0.
		gray = (minRGB(&_image[i]) + maxRGB(&_image[i])) / 2.0f;
		_image[i] = (unsigned char)gray;
		_image[i + 1] = (unsigned char)gray;
		_image[i + 2] = (unsigned char)gray;
	}
	return 0;
}

int grayscale_decomposition
(unsigned char** image, unsigned width, unsigned height, unsigned char(*fun)(unsigned char*))
{
	unsigned char* _image = *image;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Decomposition. Simplified desaturation.
		gray = fun(&_image[i]);
		_image[i] = (unsigned char)gray;
		_image[i + 1] = (unsigned char)gray;
		_image[i + 2] = (unsigned char)gray;
	}
	return 0;
}

int grayscale_single_channel
(unsigned char** image, unsigned width, unsigned height, unsigned char n)
{
	n %= 4;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Single Channel Method.
		(*image)[i] = (*image)[i + n];
		(*image)[i + 1] = (*image)[i + n];
		(*image)[i + 2] = (*image)[i + n];
	}
	return 0;
}

int grayscale_shades
(unsigned char** image, unsigned width, unsigned height, unsigned char n)
{
	if (n < 2)
		n = 2;
	float factor = (float)(0xFF / n);
	float average;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{
		average = ((*image)[i] + (*image)[i + 1] + (*image)[i + 2]) / 3.0f;
		gray = ((int)((average / factor) + 0.5)) * factor;
		(*image)[i] = (unsigned char)gray;
		(*image)[i + 1] = (unsigned char)gray;
		(*image)[i + 2] = (unsigned char)gray;
	}
	return 0;
}

int grayscale_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Grayscale Average.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_averaging(&image, width, height, 3.0f);
		save_image("average.png", image, width, height);
		destroy_image(&image);
	}

	// Grayscale Luminance.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_luminance(&image, width, height, 0.3f, 0.59f, 0.11f);
		save_image("luminance.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_luminance(&image, width, height, 0.2126f, 0.7152f, 0.0722f);
		save_image("luminance_ITU-R.png", image, width, height);
		destroy_image(&image);
	}

	// Grayscale Desaturation.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_desaturation(&image, width, height);
		save_image("desaturation.png", image, width, height);
		destroy_image(&image);
	}

	// Grayscale Decomposition.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_decomposition(&image, width, height, minRGB);
		save_image("decomposition_min.png", image, width, height);
		destroy_image(&image);
	}
	
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_decomposition(&image, width, height, maxRGB);
		save_image("decomposition_max.png", image, width, height);
		destroy_image(&image);
	}

	// Grayscale Single Channel.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_single_channel(&image, width, height, 0);
		save_image("single_channel_red.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_single_channel(&image, width, height, 1);
		save_image("single_channel_green.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_single_channel(&image, width, height, 2);
		save_image("single_channel_blue.png", image, width, height);
		destroy_image(&image);
	}

	// Grayscale Shades.
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_shades(&image, width, height, 4);
		save_image("shades_4.png", image, width, height);
		destroy_image(&image);
	}
	
	if (!load_image(filename, &image, &width, &height))
	{
		grayscale_shades(&image, width, height, 16);
		save_image("shades_16.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}