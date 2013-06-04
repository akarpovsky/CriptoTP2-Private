#ifndef _MAIN_H_
#define _MAIN_H_

#include "cmdline.h"

typedef unsigned int    DWORD;
typedef unsigned short int  WORD;
typedef unsigned char   BYTE;

void getStenographyMode(char* estenografia, int* mode);
void printUserArguments(struct gengetopt_args_info *args_info);
unsigned char * paddingPKCS5(unsigned char *in, int *inl, size_t blocksize);

#endif
