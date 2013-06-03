#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include "imageutils.h"

typedef struct carrier
{
    unsigned int fileSize;
    void * fileContents;
    char * extension;
} PortadorFileT;

PortadorFileT * readPortadorData(const char * sfilename);

void freePortadorFile(PortadorFileT * sfile);

void encrypt_LSBE(BmpImage image, char * bit_array, int bit_array_size);
void encrypt_LSB4(BmpImage image, char * bit_array, int bit_array_size);
void encrypt_LSB1(BmpImage image, char * bit_array, int bit_array_size);

unsigned char* encryptData(char* algorithm,char * mode,char * password, char* data,unsigned int lenght, char* iv);
void getOptions(char* algorihtm, char* mode, int* primitive, int* chaining, int* bits);
unsigned char * myaes_ecb_encrypt(unsigned char * text, int length, unsigned char * password, int bits);
unsigned char * myaes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char* myaes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * mydes_ecb_encrypt(unsigned char * text, int length, unsigned char * password);
unsigned char * mydes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);

#endif
