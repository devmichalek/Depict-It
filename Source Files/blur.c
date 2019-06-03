#include "blur.h"
#include "error_diffusion.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int pixalate
(unsigned char** image, unsigned width, unsigned height, int pixel_size)
{
	if (pixel_size < 2)
		return 1;

	unsigned sum_red;
	unsigned sum_green;
	unsigned sum_blue;
	unsigned counter;
	unsigned x, y;
	unsigned a, b;
	unsigned char* pixel = NULL;
	for (y = 0; y < height; y += pixel_size)
		for (x = 0; x < width; x += pixel_size)
		{
			sum_red = sum_green = sum_blue = 0;
			counter = 0;
			for (a = y; a < y + pixel_size; ++a)
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

			// precalculate
			sum_red /= counter;
			sum_green /= counter;
			sum_blue /= counter;

			for (a = y; a < y + pixel_size; ++a)
				for (b = x; b < x + pixel_size; ++b)
				{
					pixel = get_pixel(*image, width, height, b, a);
					if (pixel)
					{
						*red(pixel) = sum_red;
						*green(pixel) = sum_green;
						*blue(pixel) = sum_blue;
					}
				}
		}

	return 0;
}

double* generate_gaussian_kernel
(int n)
{
	double* kernel = (double*)malloc(sizeof(double) * n * n);
	double sigma = 1.0;
	double mean = n / 2;
	double sum = 0.0;
	int x, y;
	for (x = 0; x < n; ++x)
		for (y = 0; y < n; ++y)
		{
			kernel[(y * n) + x] = exp(-0.5 * (pow((x - mean) / sigma, 2.0) + pow((y - mean) / sigma, 2.0)))
				/ (2 * 3.14 * sigma * sigma);

			// Accumulate the kernel values.
			sum += kernel[(y * n) + x];
		}

	// Normalize the kernel.
	int size = n * n;
	for (int i = 0; i < size; ++i)
		kernel[i] /= sum;
	return kernel;
}

int gaussian_blur
(unsigned char** image, unsigned width, unsigned height, int xasis, int yasis)
{
	// Calculate kernel.
	int size = (xasis + 1 + yasis);
	double* kernel = generate_gaussian_kernel(size);

	unsigned sum_red;
	unsigned sum_green;
	unsigned sum_blue;

	int x, y, a, b;
	int asis_x, asis_y;
	int kernel_x, kernel_y;
	unsigned char* pixel = NULL;

	for (x = 0; x < width; ++x)
		for (y = 0; y < height; ++y)
		{
			sum_red = sum_green = sum_blue = 0;
			for (a = x - xasis; a <= (int)x + xasis; ++a)
				for (b = y - yasis; b <= (int)y + yasis; ++b)
				{	// Normalize. Wrapping Up.
					asis_x = a;
					asis_y = b;
					if (asis_x < 0)						{ asis_x = kernel_x = 0; }
					else if (asis_x > (int)width - 1)	{ asis_x = width - 1; kernel_x = xasis + 1; }
					else								{ kernel_x = asis_x - (x - xasis); }

					if (asis_y < 0)						{ asis_y = kernel_y = 0; }
					else if (asis_y > (int)height - 1)	{ asis_y = height - 1; kernel_y = yasis + 1; }
					else								{ kernel_y = asis_y - (y - yasis); }

					// Multiply.
					pixel = get_pixel(*image, width, height, asis_x, asis_y);
					sum_red +=		(unsigned)((double)*red(pixel)		* kernel[(kernel_y * yasis) + kernel_x]);
					sum_green +=	(unsigned)((double)*green(pixel)	* kernel[(kernel_y * yasis) + kernel_x]);
					sum_blue +=		(unsigned)((double)*blue(pixel)		* kernel[(kernel_y * yasis) + kernel_x]);
				}

			// Set new channels to pixel.
			pixel = get_pixel(*image, width, height, x, y);
			*red(pixel) = sum_red;
			*green(pixel) = sum_green;
			*blue(pixel) = sum_blue;
		}

	// Destroy kernel.
	free(kernel);
	return 0;
}

int blur_test
(const char* filename)
{
	char buffer[1024];
	unsigned width, height;
	unsigned char* image = NULL;

	// Gaussian Blur.
	for (int i = 1; i <= 5; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			int xasis = i;
			int yasis = i;
			gaussian_blur(&image, width, height, xasis, yasis);
			sprintf(buffer, "gaussian_blur_x%d_y%d_%s\0", xasis, yasis, filename);
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	// Pixelate.
	/*for (int i = 2; i <= 20; ++i)
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
	}*/

	return 0;
}