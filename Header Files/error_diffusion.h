#ifndef __ERROR_DIFFUSION_H_
#define __ERROR_DIFFUSION_H_

/*RGB*/
unsigned char* red(unsigned char*);
unsigned char* green(unsigned char*);
unsigned char* blue(unsigned char*);

/*Truncate*/
int truncate
(int);

/*Get Pixel at posiiton x, y.*/
unsigned char* get_pixel
(unsigned char*, unsigned, unsigned, unsigned, unsigned);

/*Floyd-Steinberg Error Diffusion Conversion*/
int error_diffusion
(unsigned char**, unsigned, unsigned, int);

/*Error Diffusion Test*/
int error_diffusion_test
(const char*);
#endif