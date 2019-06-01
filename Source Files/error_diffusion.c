#include "error_diffusion.h"
#include "color_reduction.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

unsigned char* red(unsigned char* pixel)
{
	return pixel;
}

unsigned char* green(unsigned char* pixel)
{
	return pixel + 1;
}

unsigned char* blue(unsigned char* pixel)
{
	return pixel + 2;
}

int truncate
(int _in)
{
	if (_in > 0xFF)
		return 0xFF;
	if (_in < 0x00)
		return 0x00;
	return _in;
}

unsigned char* get_pixel
(unsigned char* image, unsigned width, unsigned height, unsigned x, unsigned y)
{
	if (x < 0 || x >= width)
		return NULL;
	if (y < 0 || y >= height)
		return NULL;

	return &image[(((y * width) + x) * 4)];
}

int error_diffusion
(unsigned char** image, unsigned width, unsigned height, int count)
{
	unsigned char nearest_red;
	unsigned char nearest_green;
	unsigned char nearest_blue;
	float error_red;
	float error_green;
	float error_blue;
	unsigned x = 0;
	unsigned y = 0;
	unsigned char* pixel = NULL;
	for (y = 0; y < height; ++y)
	{
		for (x = 0; x < width; ++x)
		{	// Find closest color.
			pixel = get_pixel(*image, width, height, x, y);
			nearest_red = *red(pixel);
			nearest_green = *green(pixel);
			nearest_blue = *blue(pixel);
			find_closest_color(&nearest_red, &nearest_green, &nearest_blue, count - 1);

			// Calculate error.
			error_red =		(float)(*red(pixel))	- nearest_red;
			error_green =	(float)(*green(pixel))	- nearest_green;
			error_blue =	(float)(*blue(pixel))	- nearest_blue;

			// Replace pixel.
			*red(pixel) = nearest_red;
			*green(pixel) = nearest_green;
			*blue(pixel) = nearest_blue;

			// Set neighbours.
			pixel = get_pixel(*image, width, height, x + 1, y);
			if (pixel)
			{	// 7 / 16
				*red(pixel)		= truncate((int) ((float)*red(pixel)	+ (0.4375f * error_red)));
				*green(pixel)	= truncate((int) ((float)*green(pixel)	+ (0.4375f * error_green)));
				*blue(pixel)	= truncate((int) ((float)*blue(pixel)	+ (0.4375f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x - 1, y + 1);
			if (pixel)
			{	// 3 / 16
				*red(pixel)		= truncate((int) ((float)*red(pixel)	+ (0.1875f * error_red)));
				*green(pixel)	= truncate((int) ((float)*green(pixel)	+ (0.1875f * error_green)));
				*blue(pixel)	= truncate((int) ((float)*blue(pixel)	+ (0.1875f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x, y + 1);
			if (pixel)
			{	// 5 / 16
				*red(pixel)		= truncate((int) ((float)*red(pixel)	+ (0.3125f * error_red)));
				*green(pixel)	= truncate((int) ((float)*green(pixel)	+ (0.3125f * error_green)));
				*blue(pixel)	= truncate((int) ((float)*blue(pixel)	+ (0.3125f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x + 1, y + 1);
			if (pixel)
			{	// 1 / 16
				*red(pixel)		= truncate((int) ((float)*red(pixel)	+ (0.0625f * error_red)));
				*green(pixel)	= truncate((int) ((float)*green(pixel)	+ (0.0625f * error_green)));
				*blue(pixel)	= truncate((int) ((float)*blue(pixel)	+ (0.0625f * error_blue)));
			}
		}
	}
		
	return 0;
}

int error_diffusion_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Reduce to n to the power of 3 colors with Floyd-Steinberg Error Diffusion.
	char buffer[1024];
	for (int i = 2; i <= 6; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			error_diffusion(&image, width, height, i);
			sprintf(buffer, "%d_colors_e_diff.png\0", (int)pow(i, 3));
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	return 0;
}