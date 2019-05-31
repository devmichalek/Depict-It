#ifndef __REDUCE_H_
#define __REDUCE_H_

/*Find closest reduced color*/
void find_closest_color
(unsigned char*, unsigned char*, unsigned char*, unsigned);

/*Reduce to n (>= 2) to the power of 3 colors*/
int reduce_to_n_to_3_colors
(unsigned char**, unsigned, unsigned, int);

/*Reduce Test*/
int reduce_test
(const char*);
#endif