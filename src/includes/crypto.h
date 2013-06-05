#ifndef _CRYPTO_H_
#define _CRPYTO_H_

unsigned char* encryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght, char* action);
void getOptions(char* algorithm, char* mode, int* primitive, int* chaining, int* bits);
unsigned char * decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl, char* action);
unsigned char * encryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl, char* action);

#endif
