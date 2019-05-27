#include "reduce.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

const float RGB_SQR_TABLE[6] = { 1, 3, 7, 15, 31, 63 };

void find_closest_color
(unsigned char* r, unsigned char* g, unsigned char* b, unsigned dimension)
{
	dimension /= 3;
	float divider = 0xFF / RGB_SQR_TABLE[dimension - 1];
	unsigned char nearest_r, nearest_g, nearest_b;
	int table_r, table_g, table_b;

	// pre calculate ranges
	unsigned r_start = (unsigned)(*r / divider);
	unsigned g_start = (unsigned)(*g / divider);
	unsigned b_start = (unsigned)(*b / divider);
	unsigned r_end = r_start >= RGB_SQR_TABLE[dimension - 1] ? r_start : r_start + 1;
	unsigned g_end = g_start >= RGB_SQR_TABLE[dimension - 1] ? g_start : g_start + 1;
	unsigned b_end = b_start >= RGB_SQR_TABLE[dimension - 1] ? b_start : b_start + 1;

	int distance;
	int smallest = (0xFF * 0xFF) + (0xFF * 0xFF) + (0xFF * 0xFF) + 1;
	int r_diff, g_diff, b_diff;

	for (unsigned i = r_start; i <= r_end; ++i)
	{
		table_r = (int)divider * i;
		for (unsigned j = g_start; j <= g_end; ++j)
		{
			table_g = (int)divider * j;
			for (unsigned h = b_start; h <= b_end; ++h)
			{
				table_b = (int)divider * h;
				
				r_diff = table_r - (*r);
				g_diff = table_g - (*g);
				b_diff = table_b - (*b);

				distance = (r_diff * r_diff) + (g_diff * g_diff) + (b_diff * b_diff);
				if (distance < smallest)
				{
					smallest = distance;
					nearest_r = table_r;
					nearest_g = table_g;
					nearest_b = table_b;
				}
			}
		}
	}

	*r = nearest_r;
	*g = nearest_g;
	*b = nearest_b;
}

void find_closest_even_color
(unsigned char* r, unsigned char* g, unsigned char* b, unsigned dimension)
{
	dimension /= 4;
	float divider = 0xFF / (RGB_SQR_TABLE[dimension - 1] + 1);
	unsigned char nearest_r, nearest_g, nearest_b;
	int table_r, table_g, table_b;

	// pre calculate ranges
	unsigned r_start = (unsigned)(*r / divider);
	unsigned g_start = (unsigned)(*g / divider);
	unsigned b_start = (unsigned)(*b / divider);
	unsigned r_end = r_start >= (RGB_SQR_TABLE[dimension - 1] + 1) ? r_start : r_start + 1;
	unsigned g_end = g_start >= (RGB_SQR_TABLE[dimension - 1] + 1) ? g_start : g_start + 1;
	unsigned b_end = b_start >= (RGB_SQR_TABLE[dimension - 1] + 1) ? b_start : b_start + 1;

	int distance;
	int smallest = (0xFF * 0xFF) + (0xFF * 0xFF) + (0xFF * 0xFF) + 1;
	int r_diff, g_diff, b_diff;

	for (unsigned i = r_start; i <= r_end; ++i)
	{
		table_r = (int)divider * i;
		for (unsigned j = g_start; j <= g_end; ++j)
		{
			table_g = (int)divider * j;
			for (unsigned h = b_start; h <= b_end; ++h)
			{
				table_b = (int)divider * h;

				r_diff = table_r - (*r);
				g_diff = table_g - (*g);
				b_diff = table_b - (*b);

				distance = (r_diff * r_diff) + (g_diff * g_diff) + (b_diff * b_diff);
				if (distance < smallest)
				{
					smallest = distance;
					nearest_r = table_r;
					nearest_g = table_g;
					nearest_b = table_b;
				}
			}
		}
	}

	*r = nearest_r;
	*g = nearest_g;
	*b = nearest_b;
}

int reduce_to_n_colors
(unsigned char** image, unsigned width, unsigned height, int n)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
		find_closest_color(&_image[i], &_image[i + 1], &_image[i + 2], n);
	return 0;
}

int reduce_to_n_even_colors
(unsigned char** image, unsigned width, unsigned height, int n)
{
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
		find_closest_even_color(&_image[i], &_image[i + 1], &_image[i + 2], n);
	return 0;
}

int reduce_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Reduce to 2 to the power of 3 colors (8).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 3);
	save_image("3bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 4 colors (16).
	load_image(filename, &image, &width, &height);
	reduce_to_n_even_colors(&image, width, height, 4);
	save_image("4bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 6 colors (64).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 6);
	save_image("6bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 8 colors (128).
	load_image(filename, &image, &width, &height);
	reduce_to_n_even_colors(&image, width, height, 8);
	save_image("8bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 9 colors (512).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 9);
	save_image("9bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 12 colors (4096).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 12);
	save_image("12bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 15 colors (32768).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 15);
	save_image("15bit_rgb.png", image, width, height);
	destroy_image(&image);

	// Reduce to 2 to the power of 18 colors (262144).
	load_image(filename, &image, &width, &height);
	reduce_to_n_colors(&image, width, height, 18);
	save_image("18bit_rgb.png", image, width, height);
	destroy_image(&image);

	return 0;
}