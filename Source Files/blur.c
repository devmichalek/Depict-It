#include "blur.h"
#include "error_diffusion.h"
#include "image.h"
#include <stdio.h>

int pixalate
(unsigned char** image, unsigned width, unsigned height, int pixel_size)
{
	if (pixel_size < 2)
		return 1;

	unsigned sum_red;
	unsigned sum_green;
	unsigned sum_blue;
	unsigned counter;
	int x, y;
	int a, b;
	unsigned char* pixel = NULL;
	for (y = 0; y < height; y += pixel_size)
	{
		for (x = 0; x < width; x += pixel_size)
		{
			sum_red = sum_green = sum_blue = 0;
			counter = 0;
			for (a = y; a < y + pixel_size; ++a)
			{
				for (b = x; b < x + pixel_size; ++b)
				{
					pixel = get_pixel(*image, width, height, b, a);
					if (pixel)
					{
						sum_red += *red(pixel);
						sum_green += *green(pixel);
						sum_blue += *blue(pixel);
						++counter;
					}
				}
			}

			for (a = y; a < y + pixel_size; ++a)
			{
				for (b = x; b < x + pixel_size; ++b)
				{
					pixel = get_pixel(*image, width, height, b, a);
					if (pixel)
					{
						*red(pixel) = sum_red / counter;
						*green(pixel) = sum_green / counter;
						*blue(pixel) = sum_blue / counter;
					}
				}
			}
		}
	}

	return 0;
}

int gaussian_blur
(unsigned char** image, unsigned width, unsigned height, int xasis, int yasis)
{
	

	return 0;
}

int blur_test
(const char* filename)
{
	char buffer[1024];
	unsigned width, height;
	unsigned char* image = NULL;

	// Pixelate.
	for (int i = 2; i <= 20; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			pixalate(&image, width, height, i);
			sprintf(buffer, "pixelate_%d_%s\0", i, filename);
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	// Gaussian Blur.
	if (!load_image(filename, &image, &width, &height))
	{
		gaussian_blur(&image, width, height, 1, 1);
		sprintf(buffer, "gaussian_blur_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}