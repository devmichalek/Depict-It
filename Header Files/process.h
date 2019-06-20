#ifndef __PROCESS_H_
#define __PROCESS_H_

struct Commands
{

/*--- Support Functions ---*/
unsigned char* (*red)(unsigned char*);													/*Extract Red from RGB*/
unsigned char* (*green)(unsigned char*);												/*Extract Green from RGB*/
unsigned char* (*blue)(unsigned char*);													/*Extract Blue from RGB*/
unsigned char (*minRGB)(unsigned char*);												/*Get minimum of Red Green Blue*/
unsigned char (*maxRGB)(unsigned char*);												/*Get maximum of Red Green Blue*/
int (*below_threshold)(unsigned char*, unsigned char*);									/*Check if channel is below threshold*/
int (*above_threshold)(unsigned char*, unsigned char*);									/*Check if channel is above threshold*/
int (*truncate)(int);																	/*Truncate, Convert to 0 <=> 255*/
unsigned char* (*get_pixel)(unsigned char*, unsigned, unsigned, unsigned, unsigned);	/*Get Pixel at posiiton x, y*/
void (*find_closest_color)(unsigned char*, unsigned char*, unsigned char*, unsigned);	/*Find closest reduced color*/
double* (*generate_kernel)(int, double);												/*Generate Gaussian Kernel*/
int (*quick_image_check)(unsigned char*, unsigned, unsigned);							/*Quickly checks if image is valid*/

/*--- Oryginal Functions ---*/
int (*average)(unsigned char**, unsigned, unsigned);								/*Grayscale Averaging Conversion*/
int (*blur)(unsigned char**, unsigned, unsigned, unsigned);							/*Gaussian Blur Conversion*/
int (*brighten)(unsigned char**, unsigned, unsigned, int);							/*Brightness Conversion*/
int (*contrast)(unsigned char**, unsigned, unsigned, int);							/*Contrast Conversion*/
int (*decompose)(unsigned char**, unsigned, unsigned, char*);						/*Grayscale Decomposition Conversion*/
int (*desaturate)(unsigned char**, unsigned, unsigned);								/*Grayscale Desaturation Conversion*/
int (*diffuse)(unsigned char**, unsigned, unsigned, unsigned);						/*Floyd-Steinberg Error Diffusion Conversion*/
int (*__gamma)(unsigned char**, unsigned, unsigned, double);						/*Gamma Conversion*/
int (*grayshade)(unsigned char**, unsigned, unsigned, unsigned);					/*Grayscale Shades Conversion*/
int (*invert)(unsigned char**, unsigned, unsigned);									/*Inversion Algorithm*/
int (*luminance)(unsigned char**, unsigned, unsigned, float, float, float);			/*Luminance Conversion*/
int (*pixelate)(unsigned char**, unsigned, unsigned, unsigned);						/*Pixelate Conversion*/
int (*reduce)(unsigned char**, unsigned, unsigned, unsigned);						/*Reduce to n (>= 2) to the power of 3 colors*/
int (*singlechannel)(unsigned char**, unsigned, unsigned, char);					/*Single Channel Conversion*/
int (*solarise)(unsigned char**, unsigned, unsigned, unsigned, char*);				/*Solarisation Algorithm*/

/*--- Test Functions ---*/
int (*average_test)(const char*);
int (*blur_test)(const char*);
int (*brighten_test)(const char*);
int (*contrast_test)(const char*);
int (*decompose_test)(const char*);
int (*desaturate_test)(const char*);
int (*diffuse_test)(const char*);
int (*gamma_test)(const char*);
int (*grayshade_test)(const char*);
int (*invert_test)(const char*);
int (*luminance_test)(const char*);
int (*pixelate_test)(const char*);
int (*reduce_test)(const char*);
int (*singlechannel_test)(const char*);
int (*solarise_test)(const char*);

};

extern const struct Commands LibCommands;

#endif