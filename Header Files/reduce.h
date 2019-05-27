#ifndef __REDUCE_H_
#define __REDUCE_H_

extern const float RGB_SQR_TABLE[6];

/*Find closest reduced color*/
void find_closest_color
(unsigned char*, unsigned char*, unsigned char*, unsigned);

/*Find closest even reduced color*/
void find_closest_even_color
(unsigned char*, unsigned char*, unsigned char*, unsigned);

/*Reduce to 2 to the power of n colors*/
int reduce_to_n_colors
(unsigned char**, unsigned, unsigned, int);

/*Reduce to 2 to the power of n (even) colors*/
int reduce_to_n_even_colors
(unsigned char**, unsigned, unsigned, int);

/*Reduce Test*/
int reduce_test
(const char*);
#endif