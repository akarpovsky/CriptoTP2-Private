#ifndef _DECRYPT_H_
#define _DECRYPT_H_

#include "imageutils.h"

int decrypt_LSBE(BmpImage image);
int decrypt_LSB4(BmpImage image);
int decrypt_LSB1(BmpImage image);

#endif
