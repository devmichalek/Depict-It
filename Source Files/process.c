#include "process.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- Support Functions ---*/
unsigned char* red(unsigned char* pixel)
{	/*Extract Red from RGB*/
	return pixel;
}

unsigned char* green(unsigned char* pixel)
{	/*Extract Green from RGB*/
	return pixel + 1;
}

unsigned char* blue(unsigned char* pixel)
{	/*Extract Blue from RGB*/
	return pixel + 2;
}

unsigned char minRGB(unsigned char* rgb)
{	/*Get minimum of Red Green Blue*/
	unsigned char* ptr = rgb;
	unsigned char smallest = 0xFF;
	for (unsigned i = 0; i < 3; ++i, ++ptr)
		if (*ptr < smallest)
			smallest = *ptr;
	return smallest;
}

unsigned char maxRGB(unsigned char* rgb)
{	/*Get maximum of Red Green Blue*/
	unsigned char* ptr = rgb;
	unsigned char greatest = 0x00;
	for (unsigned i = 0; i < 3; ++i, ++ptr)
		if (*ptr > greatest)
			greatest = *ptr;
	return greatest;
}

int below_threshold(unsigned char* channel, unsigned char* threshold)
{	/*Check if channel is below threshold*/
	return *channel < *threshold;
}

int above_threshold(unsigned char* channel, unsigned char* threshold)
{	/*Check if channel is above threshold*/
	return *channel > *threshold;
}

int truncate(int input)
{	/*Truncate, Convert to 0 <=> 255*/
	if (input > 0xFF)
		return 0xFF;
	if (input < 0x00)
		return 0x00;
	return input;
}

unsigned char* get_pixel(unsigned char* image, unsigned width, unsigned height, unsigned x, unsigned y)
{	/*Get Pixel at posiiton x, y*/
	if (x < 0 || x >= width)
		return NULL;
	if (y < 0 || y >= height)
		return NULL;
	return &image[(((y * width) + x) * 4)];
}

void find_closest_color(unsigned char* r, unsigned char* g, unsigned char* b, unsigned count)
{	/*Find closest reduced color*/
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

double* generate_kernel(int n, double sigma)
{	/*Generate Gaussian Kernel*/
	double* kernel = (double*)malloc(sizeof(double) * n * n);
	double mean = (double)n / 2;
	double sum = 0.0;
	int x, y;
	for (x = 0; x < n; ++x)
		for (y = 0; y < n; ++y)
		{
			kernel[(y * n) + x] = exp(-0.5 * (pow(((double)x - mean) / sigma, 2.0) + pow(((double)y - mean) / sigma, 2.0)))
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

int quick_image_check(unsigned char* image, unsigned width, unsigned height)
{	/*Quickly checks if image is valid*/
	if (image && width && height)
		return 0;
	
	printf("Error: Image is invalid\n");
	return 1; // image is invalid
}



/*--- Oryginal Functions ---*/
int average(unsigned char** image, unsigned width, unsigned height)
{	/*Arguments: image, width, height*/
	if (quick_image_check(*image, width, height))
		return 1;

	unsigned char* _image = *image;
	float gray;
	unsigned i = 0;
	unsigned size = width * height;
	for (; i < size * 4; i += 4)
	{	// Make an average of read, green and blue.
		gray = (_image[i] + _image[i + 1] + _image[i + 2]) / 3.0f;
		_image[i] = (unsigned char)gray;
		_image[i + 1] = (unsigned char)gray;
		_image[i + 2] = (unsigned char)gray;
	}
	return 0;
}

int blur(unsigned char** image, unsigned width, unsigned height, unsigned asis)
{	/*Arguments: image, width, height, asis size*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (asis > 20)
	{
		printf("Warning: Max asis size for Blur algorithm is 20. Asis will be truncated...\n");
		asis = 20;
	}

	// Calculate kernel.
	int size = asis * 2 + 1;
	double* kernel = generate_kernel(size, (double)(asis * 2));

	double sum_red;
	double sum_green;
	double sum_blue;

	unsigned _where;
	int x, y, a, b;
	int asis_x, asis_y;
	unsigned char* pixel = NULL;

	for (y = 0; y < (int)height; ++y)
		for (x = 0; x < (int)width; ++x)
		{
			sum_red = sum_green = sum_blue = 0;
			for (b = -((int)asis); b <= (int)asis; ++b)		// y
				for (a = -((int)asis); a <= (int)asis; ++a)	// x
				{	// Normalize. Wrapping Up.
					asis_x = x + a;
					asis_y = y + b;
					if (asis_x < 0) { asis_x = 0; }
					else if (asis_x >(int)width - 1) { asis_x = width - 1; }
					if (asis_y < 0) { asis_y = 0; }
					else if (asis_y >(int)height - 1) { asis_y = height - 1; }

					// Multiply.
					_where = ((b + (int)asis) * size) + a + (int)asis;
					pixel = get_pixel(*image, width, height, asis_x, asis_y);
					sum_red += (double)*red(pixel)		* kernel[_where];
					sum_green += (double)*green(pixel)	* kernel[_where];
					sum_blue += (double)*blue(pixel)	* kernel[_where];
				}

			// Set new channels to pixel.
			pixel = get_pixel(*image, width, height, x, y);
			*red(pixel) = (unsigned)sum_red;
			*green(pixel) = (unsigned)sum_green;
			*blue(pixel) = (unsigned)sum_blue;
		}

	// Destroy kernel.
	free(kernel);
	return 0;
}

int brighten(unsigned char** image, unsigned width, unsigned height, int level)
{	/*Arguments: image, width, height, brightness level*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (level < -0xFF)
	{
		printf("Warning: Min brightness level is -255. Brightness level will be truncated...\n");
		level = -0xFF;
	}
	else if (level > 0xFF)
	{
		printf("Warning: Max brightness level is 255. Brightness level will be truncated...\n");
		level = 0xFF;
	}

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

int contrast(unsigned char** image, unsigned width, unsigned height, int level)
{	/*Arguments: image, width, height, contrast level*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (level < -0xFF)
	{
		printf("Warning: Min contrast level is -255. Contrast level will be truncated...\n");
		level = -0xFF;
	}
	else if (level > 0xFF)
	{
		printf("Warning: Max contrast level is 255. Contrast level will be truncated...\n");
		level = 0xFF;
	}

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

int decompose(unsigned char** image, unsigned width, unsigned height, char* fname)
{	/*Arguments: image, width, height, function name min/max*/
	if (quick_image_check(*image, width, height))
		return 1;

	unsigned char(*fun)(unsigned char*) = minRGB;
	if (!fname)
		printf("Warning: Function name for Decompose algorithm is not set... choosing min function\n");
	else if (!strcmp(fname, "max"))
		fun = maxRGB;
	else if (strcmp(fname, "min"))
		printf("Warning: Function name for Decompose algorithm is not properly set... choosing min function\n");

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

int desaturate(unsigned char** image, unsigned width, unsigned height)
{	/*Arguments: image, width, height*/
	if (quick_image_check(*image, width, height))
		return 1;

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

int diffuse(unsigned char** image, unsigned width, unsigned height, unsigned count)
{	/*Arguments: image, width, height, number of colors to the power of the 3 to reduce to*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (count > 12)
	{
		printf("Warning: Max number of colors for Diffuse algortihm is 12 (to the power of 3)...\n");
		count = 12;
	}

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
			error_red = (float)(*red(pixel)) - nearest_red;
			error_green = (float)(*green(pixel)) - nearest_green;
			error_blue = (float)(*blue(pixel)) - nearest_blue;

			// Replace pixel.
			*red(pixel) = nearest_red;
			*green(pixel) = nearest_green;
			*blue(pixel) = nearest_blue;

			// Set neighbours.
			pixel = get_pixel(*image, width, height, x + 1, y);
			if (pixel)
			{	// 7 / 16
				*red(pixel) = truncate((int)((float)*red(pixel) + (0.4375f * error_red)));
				*green(pixel) = truncate((int)((float)*green(pixel) + (0.4375f * error_green)));
				*blue(pixel) = truncate((int)((float)*blue(pixel) + (0.4375f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x - 1, y + 1);
			if (pixel)
			{	// 3 / 16
				*red(pixel) = truncate((int)((float)*red(pixel) + (0.1875f * error_red)));
				*green(pixel) = truncate((int)((float)*green(pixel) + (0.1875f * error_green)));
				*blue(pixel) = truncate((int)((float)*blue(pixel) + (0.1875f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x, y + 1);
			if (pixel)
			{	// 5 / 16
				*red(pixel) = truncate((int)((float)*red(pixel) + (0.3125f * error_red)));
				*green(pixel) = truncate((int)((float)*green(pixel) + (0.3125f * error_green)));
				*blue(pixel) = truncate((int)((float)*blue(pixel) + (0.3125f * error_blue)));
			}

			pixel = get_pixel(*image, width, height, x + 1, y + 1);
			if (pixel)
			{	// 1 / 16
				*red(pixel) = truncate((int)((float)*red(pixel) + (0.0625f * error_red)));
				*green(pixel) = truncate((int)((float)*green(pixel) + (0.0625f * error_green)));
				*blue(pixel) = truncate((int)((float)*blue(pixel) + (0.0625f * error_blue)));
			}
		}
	}

	return 0;
}

int gamma(unsigned char** image, unsigned width, unsigned height, double ratio)
{	/*Arguments: image, width, height, gamma ratio*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (ratio < 0)
	{
		printf("Warning: Gamma correction algorithm takes only positive floating-point numbers...\n");
		return 0; // actually not error
	}

	if (ratio > 8.0)
	{
		printf("Warning: Gamma correction algorithm max floating-point number is 8.0, reducing...\n");
		ratio = 8.0;
	}

	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		_image[i] = (unsigned char)(0xFF * pow(((float)_image[i] / 0xFF), ratio));
		_image[i + 1] = (unsigned char)(0xFF * pow(((float)_image[i + 1] / 0xFF), ratio));
		_image[i + 1] = (unsigned char)(0xFF * pow(((float)_image[i + 1] / 0xFF), ratio));
	}

	return 0;
}

int grayshade(unsigned char** image, unsigned width, unsigned height, unsigned count)
{	/*Arguments: image, width, height, number of shades*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (count < 2)
	{
		printf("Warning: Increasing number of shades for Grayshade algorithm to 2...\n");
		count = 2;
	}
	else if (count > 0xFF)
	{
		printf("Warning: Max number of shades for Grayshade algorithm is 255, reducing number of shades...\n");
		count = 0xFF;
	}

	float factor = (float)(0xFF / count);
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

int invert(unsigned char** image, unsigned width, unsigned height)
{	/*Arguments: image, width, height*/
	if (quick_image_check(*image, width, height))
		return 1;

	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
	{
		_image[i] = 0xFF - _image[i];
		_image[i + 1] = 0xFF - _image[i + 1];
		_image[i + 2] = 0xFF - _image[i + 2];
	}

	return 0;
}

int luminance(unsigned char** image, unsigned width, unsigned height, float ar, float ag, float ab)
{	/*Arguments: image, width, height, red ratio, green ratio, blue ratio*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (ar < 0.0f || ag < 0.0f || ab < 0.0f)
	{
		printf("Error: Luminancing image, RGB ratio must be a positive floating-point value\n");
		return 1;
	}

	if (ar > 1.0f)
	{
		printf("Warning: Luminancing image, red ratio's max value is 1.0, reducing red channel...\n");
		ar = 1.0f;
	}

	if (ag > 1.0f)
	{
		printf("Warning: Luminancing image, green ratio's max value is 1.0, reducing green channel...\n");
		ag = 1.0f;
	}

	if (ab > 1.0f)
	{
		printf("Warning: Luminancing image, blue ratio's max value is 1.0, reducing blue channel...\n");
		ab = 1.0f;
	}

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

int pixelate(unsigned char** image, unsigned width, unsigned height, unsigned pixel_size)
{	/*Arguments: image, width, height, pixel size*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (pixel_size < 2)
	{
		printf("Warning: Min pixel size for Pixelate algorithm is 2, increasing pixel size to 2...\n");
		pixel_size = 2;
	}
	else if (pixel_size >= width && pixel_size >= height)
	{
		printf("Error: Max pixel size for Pixelate algorithm is image'width | image'height\n");
		return 1;
	}

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

			// calculate
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

int reduce(unsigned char** image, unsigned width, unsigned height, unsigned count)
{	/*Arguments: image, width, height, number of colors to the power of the 3 to reduce to*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (count > 15)
	{
		printf("Warning: Max number of colors for Reduce algortihm is 15 (to the power of 3)...\n");
		count = 15;
	}

	--count;
	unsigned char* _image = *image;
	unsigned size = width * height;
	unsigned i = 0;
	for (; i < size * 4; i += 4)
		find_closest_color(&_image[i], &_image[i + 1], &_image[i + 2], count);
	return 0;
}

int singlechannel(unsigned char** image, unsigned width, unsigned height, char channel)
{	/*Arguments: image, width, height, channel - r/g/b*/
	int n = 0;
	if (channel == 'g')			n = 1;
	else if (channel == 'b')	n = 2;
	else if (channel != 'r')
	{
		printf("Error: Unknown channel %c for Singlechannel algorithm\n", channel);
		return 1;
	}

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

int solarise(unsigned char** image, unsigned width, unsigned height, unsigned th, char* fname)
{	/*Arguments: image, width, height, function name above/below*/
	if (quick_image_check(*image, width, height))
		return 1;

	if (th > 0xFF)
	{
		printf("Warning: Threshold is too great for Solarise algorithm, reducing threshold...\n");
		th = 0xFF;
	}

	unsigned char threshold = (unsigned char)th;
	int(*fun)(unsigned char*, unsigned char*) = below_threshold;
	if (!fname)
		printf("Warning: Function name for Solarise algorithm is not set... choosing below function\n");
	else if (!strcmp(fname, "above"))
		fun = above_threshold;
	else if (strcmp(fname, "below"))
		printf("Warning: Function name for Solarise algorithm is not properly set... choosing below function\n");

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



/*--- Test Functions ---*/
int average_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Grayscale Average.
	if (!load_image(filename, &image, &width, &height))
	{
		average(&image, width, height);
		save_image("average.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int blur_test(const char* filename)
{
	char buffer[1024];
	unsigned width, height;
	unsigned char* image = NULL;

	for (int i = 1; i <= 7; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			blur(&image, width, height, i);
			sprintf(buffer, "gaussian_blur_xy%d_%s\0", i, filename);
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	return 0;
}

int brighten_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;
	char buffer[1024];

	if (!load_image(filename, &image, &width, &height))
	{
		brighten(&image, width, height, 64);
		sprintf(buffer, "brightned_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		brighten(&image, width, height, -64);
		sprintf(buffer, "darkened_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int contrast_test(const char* filename)
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

int decompose_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		decompose(&image, width, height, "min");
		save_image("decompose_min.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		decompose(&image, width, height, "max");
		save_image("decompose_max.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int desaturate_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		desaturate(&image, width, height);
		save_image("desaturated.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int diffuse_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	// Reduce to n to the power of 3 colors with Floyd-Steinberg Error Diffusion.
	char buffer[1024];
	for (int i = 2; i <= 6; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			diffuse(&image, width, height, i);
			sprintf(buffer, "%d_colors_e_diff.png\0", (int)pow(i, 3));
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	return 0;
}

int gamma_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		gamma(&image, width, height, 0.25);
		char buffer[1024];
		sprintf(buffer, "gamma_0_25%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		gamma(&image, width, height, 2.0);
		char buffer[1024];
		sprintf(buffer, "gamma_2_00_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int grayshade_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		grayshade(&image, width, height, 4);
		save_image("shades_4.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		grayshade(&image, width, height, 16);
		save_image("shades_16.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int invert_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		invert(&image, width, height);
		char buffer[1024];
		sprintf(buffer, "inverted_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int luminance_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		luminance(&image, width, height, 0.3f, 0.59f, 0.11f);
		save_image("luminance.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		luminance(&image, width, height, 0.2126f, 0.7152f, 0.0722f);
		save_image("luminance_ITU-R.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int pixelate_test(const char* filename)
{
	char buffer[1024];
	unsigned width, height;
	unsigned char* image = NULL;

	for (int i = 2; i <= 10; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			pixelate(&image, width, height, i);
			sprintf(buffer, "pixelate_%d_%s\0", i, filename);
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	return 0;
}

int reduce_test(const char* filename)
{
	char buffer[1024];
	unsigned width, height;
	unsigned char* image = NULL;

	for (int i = 2; i <= 15; ++i)
	{
		if (!load_image(filename, &image, &width, &height))
		{
			reduce(&image, width, height, i);
			sprintf(buffer, "%d_colors.png\0", (int)pow(i, 3));
			save_image(buffer, image, width, height);
			destroy_image(&image);
		}
		else
			break;
	}

	return 0;
}

int singlechannel_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;

	if (!load_image(filename, &image, &width, &height))
	{
		singlechannel(&image, width, height, 'r');
		save_image("single_channel_red.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		singlechannel(&image, width, height, 'g');
		save_image("single_channel_green.png", image, width, height);
		destroy_image(&image);
	}

	if (!load_image(filename, &image, &width, &height))
	{
		singlechannel(&image, width, height, 'b');
		save_image("single_channel_blue.png", image, width, height);
		destroy_image(&image);
	}

	return 0;
}

int solarise_test(const char* filename)
{
	unsigned width, height;
	unsigned char* image = NULL;
	char buffer[1024];

	// Solarise below.
	if (!load_image(filename, &image, &width, &height))
	{
		solarise(&image, width, height, 0xFF / 2, "below");
		sprintf(buffer, "solarised_below_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	// Solarise above.
	if (!load_image(filename, &image, &width, &height))
	{
		solarise(&image, width, height, 0xFF / 2, "above");
		sprintf(buffer, "solarised_above_%s\0", filename);
		save_image(buffer, image, width, height);
		destroy_image(&image);
	}

	return 0;
}