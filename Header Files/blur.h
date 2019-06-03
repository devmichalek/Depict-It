#ifndef __BLUR_H_
#define __BLUR_H_

/*Pixalate*/
int pixalate
(unsigned char**, unsigned, unsigned, int);

/*Gaussian Kernel*/
double* generate_gaussian_kernel
(int);

/*Gaussian Blur.*/
int gaussian_blur
(unsigned char**, unsigned, unsigned, int, int);

/*Blur Test*/
int blur_test
(const char*);
#endif