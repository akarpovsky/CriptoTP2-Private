#ifndef _MAIN_H_
#define _MAIN_H_

#include "cmdline.h"

void getStenographyMode(char* estenografia, int* mode);
void getPrimiteAndMode(char* primitive, char* chaining , int* primitiva, int* modo);
void printUserArguments(struct gengetopt_args_info *args_info);
#endif
