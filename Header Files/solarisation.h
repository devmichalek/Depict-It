#ifndef __SOLARISATION_H_
#define __SOLARISATION_H_

/*Solarise below <*/
int solarise_below
(unsigned char*, unsigned char*);

/*Solarise above >*/
int solarise_above
(unsigned char*, unsigned char*);

/*Solarise RGB channels.*/
int solarisation
(unsigned char**, unsigned, unsigned, unsigned char, int (*fun)(unsigned char*, unsigned char*));

/*Inversion Test*/
int solarisation_test
(const char*);
#endif