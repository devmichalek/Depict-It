#ifndef __IMAGE_H_
#define __IMAGE_H_

int load_image(const char*, unsigned char**, unsigned*, unsigned*);
int save_image(const char*, const unsigned char*, unsigned, unsigned);
int destroy_image(unsigned char**);

#endif