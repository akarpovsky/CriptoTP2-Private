#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

unsigned char* encryptData( const char* algorithm,const char * mode,const  char * password,const  char* data, const unsigned int lenght);
unsigned char * myaes_ecb_encrypt(unsigned char * text, int length, unsigned char * password, int bits);
unsigned char * myaes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char* myaes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * mydes_ecb_encrypt(unsigned char * text, int length, unsigned char * password);
unsigned char * mydes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv);
#endif
