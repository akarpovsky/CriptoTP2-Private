#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_


unsigned char * decryptData(char* algorithm,char * mode,char * password,char* encryptedData,unsigned int lenght, char* iv);
unsigned char * myaes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password, int bits);
unsigned char * myaes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * mydes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password);
unsigned char * mydes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
#endif
