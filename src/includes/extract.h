#ifndef _EXTRACT_H_
#define _EXTRACT_H_

#include "imageutils.h"

int decrypt_LSBE(BmpImage image, char * out_filename, FILE * fp);
int decrypt_LSB4(BmpImage image, char * out_filename, FILE * fp);
int decrypt_LSB1(BmpImage image, char * out_filename, FILE * fp);
char get_lsb1(FILE* in);
char get_lsb4(FILE* in);
char get_lsbe(FILE* in);

#endif
