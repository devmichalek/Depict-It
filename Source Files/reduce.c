#include "reduce.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

void find_closest_color
(unsigned char* r, unsigned char* g, unsigned char* b, unsigned count)
{
	float divider = (float)(0xFF / count);
	unsigned char nearest_r, nearest_g, nearest_b;
	int table_r, table_g, table_b;

	// pre calculate ranges
	unsigned r_start = (unsigned)(*r / divider);
	unsigned g_start = (unsigned)(*g / divider);
	unsigned b_start = (unsigned)(*b / divider);
	unsigned r_end = (r_start >= count) ? r_start : r_start + 1;
	unsigned g_end = (g_start >= count) ? g_start : g_start + 1;
	unsigned b_end = (b_start >= count) ? b_start : b_start + 1;

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

int reduce_to_n_to_3_colors
(unsigned char** image, unsigned width, unsigned height, int n)
{
	if (n < 2 || n > 15)
		return 1;
	--n;

	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
		find_closest_color(&_image[i], &_image[i + 1], &_image[i + 2], n);
	return 0;
}

int reduce_test
(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Reduce to n to the power of 3 colors.
	char buffer[1024];
	for (int i = 2; i <= 15; ++i)
	{
		load_image(filename, &image, &width, &height);
		reduce_to_n_to_3_colors(&image, width, height, i);
		sprintf(buffer, "%d_colors.png\0", (int)pow(i, 3));
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}