#ifndef __GAMMA_CORRECTION_H_
#define __GAMMA_CORRECTION_H_

/*Manipulate gamma curve.*/
int gamma_correction
(unsigned char**, unsigned, unsigned, double);

/*Inversion Test*/
int gamma_correction_test
(const char*);
#endif