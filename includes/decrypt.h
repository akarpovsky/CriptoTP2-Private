#ifndef _DECRYPT_H_
#define _DECRYPT_H_


unsigned char * decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* encryptedData,int lenght,unsigned char* iv);
unsigned char * myaes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password, int bits);
unsigned char * myaes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * myaes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits);
unsigned char * mydes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password);
unsigned char * mydes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
unsigned char * mydes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv);
#endif
