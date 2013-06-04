#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include "includes/defines.h"
#include "includes/encrypt.h"
#include "includes/decrypt.h"

unsigned char * decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* encryptedData,int lenght, unsigned char* iv){

	int primitive=0;
	int chaining=-1;
	int bits=0;
	
	getOptions(algorithm,mode,&primitive,&chaining,&bits);

	if(primitive==DES){

		if(chaining==ECB)
			return (unsigned char*) mydes_ecb_decrypt(encryptedData, lenght, password);
		else if(chaining== CBC)
			return (unsigned char*) mydes_cbc_decrypt(encryptedData, lenght, password, iv);
		else if(chaining== OFB)
			return (unsigned char*) mydes_ofb_decrypt(encryptedData, lenght, password, iv);
		else
			return (unsigned char*) mydes_cfb_decrypt(encryptedData, lenght, password, iv);
	}
	if(primitive==AES){

		if(chaining==ECB)
			return (unsigned char*) myaes_ecb_decrypt(encryptedData,lenght,password,bits);
		else if(chaining==CBC)
			return (unsigned char*) myaes_cbc_decrypt(encryptedData,lenght,password,iv,bits);
		else if(chaining==OFB)
			return (unsigned char*) myaes_ofb_decrypt(encryptedData,lenght,password,iv,bits);
		else 
			return (unsigned char*) myaes_cfb_decrypt(encryptedData,lenght,password,iv,bits);
	}
}

unsigned char *
myaes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password, int bits)
{
        unsigned char outbuf[16];
        unsigned char * ret = malloc(length);

        AES_KEY aeskey;
       
        int i = 0;
        int blocks = length/16;

        AES_set_decrypt_key(password, bits, &aeskey);

        for(i=0;i<blocks;i++)
        {

                AES_ecb_encrypt(enc+i*16, outbuf, &aeskey, AES_DECRYPT);
                memcpy(ret+i*16,outbuf,16);
        }

        return ret;
}

unsigned char *
myaes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * ret;
        unsigned char * outbuf = malloc(length);

        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;
       
        memset(outbuf, 0, sizeof(outbuf));
       
        AES_set_decrypt_key(key, bits, &aeskey);

        AES_cbc_encrypt(enc, outbuf, length, &aeskey, liv, AES_DECRYPT);
               
        ret = outbuf;
       
        return ret;
}

unsigned char *
myaes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * outbuf= calloc(1,length);
        int num = 0;

        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;
       
       
        AES_set_encrypt_key(key, bits, &aeskey);

        AES_cfb8_encrypt(enc, outbuf, length, &aeskey, liv, &num, AES_DECRYPT);

        return outbuf;
}

unsigned char *
myaes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * outbuf= calloc(1,length);
        int num = 0;

        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;


        AES_set_encrypt_key(key, bits, &aeskey);

        AES_ofb128_encrypt(enc, outbuf, length, &aeskey, liv, &num);

        return outbuf;
}

unsigned char *
mydes_ecb_decrypt(unsigned char * enc, int length, unsigned char * password)
{
        unsigned char * out;
        unsigned char * key;
       
        out = malloc(length);
       
        key = malloc(8);
        memcpy((char *)key, password, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)key, (DES_key_schedule *)schedule);

        int blocks = length/8;
        int i;
       
        for(i=0;i<blocks;i++)
        {
                DES_ecb_encrypt((const_DES_cblock *)(enc+8*i), (DES_cblock *)(out+i*8), schedule, DES_DECRYPT);
        }
       
        return out;
}

unsigned char *
mydes_cbc_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv)
{      
        unsigned char * out;
        out = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

       
       
        DES_ncbc_encrypt(enc, out, length, schedule, (DES_cblock *)liv, DES_DECRYPT);
               
        return out;
}

unsigned char *
mydes_cfb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv)
{
        unsigned char * out;
        out = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

        DES_cfb_encrypt(enc, out, 8, length, schedule, (DES_cblock *)liv, DES_DECRYPT);
       
        return out;
}

unsigned char *
mydes_ofb_decrypt(unsigned char * enc, int length, unsigned char * key, unsigned char * iv)
{
        unsigned char * out;
        out = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

        DES_ofb_encrypt(enc, out, 8, length, schedule, (DES_cblock *)liv);
       
        return out;
}


