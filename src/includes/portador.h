#ifndef _PORTADOR_H_
#define _PORTADOR_H_ 

#include "imageutils.h" 

typedef struct carrier
{
    unsigned int fileSize;
    void * fileContents;
    char * extension;
} PortadorFileT;

PortadorFileT * readPortadorData(const char * sfilename);

void freePortadorFile(PortadorFileT * sfile);

#endif
