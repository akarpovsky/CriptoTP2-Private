#ifndef _EMBED_H_
#define _EMBED_H_

#include "imageutils.h"

void encrypt_LSBE(BmpImage image, char * bit_array, int bit_array_size);
void encrypt_LSB4(BmpImage image, char * bit_array, int bit_array_size);
void encrypt_LSB1(BmpImage image, char * bit_array, int bit_array_size);

#endif

