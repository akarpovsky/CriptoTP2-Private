#ifndef _CRYPTO_H_
#define _CRPYTO_H_

unsigned char* encryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght ,int * outl);
unsigned char * decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl);
unsigned char* encryptAndDecryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght ,int * outl, int action);
EVP_CIPHER*  getCipher(char* algorithm, char* mode/*, int* bits*/);
#endif
