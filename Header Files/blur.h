#ifndef __BLUR_H_
#define __BLUR_H_

/*Pixelate*/
int pixelate
(unsigned char**, unsigned, unsigned, int);

/*Gaussian Kernel*/
double* generate_gaussian_kernel
(int, double);

/*Gaussian Blur.*/
int gaussian_blur
(unsigned char**, unsigned, unsigned, int);

/*Blur Test*/
int blur_test
(const char*);
#endif