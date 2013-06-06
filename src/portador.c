#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "includes/portador.h"

PortadorFileT *
readPortadorData(const char * sfilename)
{
    PortadorFileT * sfiledata;
    FILE * stegoFile;
    char * extension;
    int fsize;

    if ( (stegoFile = fopen(sfilename, "r")) == NULL)
    {
        return NULL;
    }

    if ( (sfiledata = calloc(1, sizeof(PortadorFileT))) == NULL)
    {
        fclose(stegoFile);
        return NULL;
    }


    // Tamaño del archivo
    fseek(stegoFile, 0L, SEEK_END);
    fsize = ftell(stegoFile);
    fseek(stegoFile, 0L, SEEK_SET);

    if ( (sfiledata -> fileContents = calloc(1, fsize)) == NULL)
    {
        fprintf(stderr,"Out of memory when reading %s\n", sfilename);
        fclose(stegoFile);
        free(sfiledata);
        return NULL;
    }

    sfiledata -> fileSize = fsize;
    fread(sfiledata -> fileContents, fsize,1,stegoFile);

    if (ferror(stegoFile) > 0)
    {
        free(sfiledata);
        fclose(stegoFile);
        return NULL;
    }

    extension = strstr(sfilename, ".");

    if ((sfiledata -> extension = calloc(1, sizeof(char) * strlen(extension) + 1)) == NULL)
    {
        free(sfiledata);
        fclose(stegoFile);
        return NULL;
    }

    strncpy(sfiledata -> extension, extension, strlen(extension));

    fclose(stegoFile);
    return sfiledata;
}

void freePortadorFile(PortadorFileT * sfile)
{
    free(sfile -> extension);
    free(sfile -> fileContents);
    free(sfile);
    return;
} 
