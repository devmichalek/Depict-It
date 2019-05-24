#ifndef __GRAYSCALE_H_
#define __GRAYSCALE_H_

/*Grayscale Averaging Conversion*/
int grayscale_averaging
(unsigned char**, unsigned, unsigned, float);

/*Grayscale Luminance Conversion*/
int grayscale_luminance
(unsigned char**, unsigned, unsigned, float, float, float);

/*Grayscale Desaturation Conversion*/
unsigned char minRGB
(unsigned char*);
unsigned char maxRGB
(unsigned char*);
int grayscale_desaturation
(unsigned char**, unsigned, unsigned);

/*Grayscale Decomposition Conversion*/
int grayscale_decomposition
(unsigned char**, unsigned, unsigned, unsigned char(*)(unsigned char*));

/*Grayscale Single Channel Conversion*/
int grayscale_single_channel
(unsigned char**, unsigned, unsigned, unsigned char);

/*Grayscale Shades Conversion*/
int grayscale_shades
(unsigned char**, unsigned, unsigned, unsigned char);

/*Grayscale Test*/
int grayscale_test
(const char*);
#endif