#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include "./includes/defines.h"
#include "./includes/encrypt.h"

unsigned char*
encryptData( const char* algorithm,const char * mode,const  char * password,const  char* data, const unsigned int lenght){

	unsigned char encryptedData=NULL;
	int primitive=0;
	int chaining=-1;
	int bits=0;
	if(algorithm !=NULL){

		if( strcmp(algorithm,"aes128")==0){
			primitive= AES;
			bits=128;
		}else if ( strcmp(algorithm,"aes192")==0){
			primitive= AES;
			bits=192;
		}else if ( strcmp(algorithm,"aes256")==0){
			primitive= AES;
			bits=256;
		}else if ( strcmp(algorithm,"des")==0){
			primitive= DES;
		}
	}else{
		primitive= AES;	
		bits=128;
	}

	if(mode !=NULL){
			if( strcmp(mode,"ecb")==0){
				chaining=ECB;
			}else if(strcmp(mode,"cfb")==0){
				chaining=CBF;
			}else if(strcmp(mode,"ofb")==0){
				chaining=OFB;
			}else if(strcmp(mode,"cbc")==0){
				chaining=CBC;
			}
	}else{
		chaining=CBC;
		}	
	
	if(primitive==DES){
		if(chaining==ECB)
			return mydes_ecb_encrypt(data, lenght, password);
		else if(chaining== CBC)
			return mydes_cbc_encrypt(data, lenght, password, "a");
		else if(chaining== OFB)
			return mydes_ofb_encrypt(data, lenght, password, "a");
		else
			return mydes_cfb_encrypt(data, lenght, password, "a");
	}else if(primitive==AES){

		if(chaining==ECB)
			return myaes_ecb_encrypt(data,lenght,password,bits);
		else if(chaining==CBC)
			return myaes_cbc_encrypt(data,lenght,password,"a",bits);
		else if(chaining==OFB)
			return myaes_ofb_encrypt(data,lenght,password,"a",bits);
		else 
			return myaes_cfb_encrypt(data,lenght,password,"a",bits);
	}
	
			

}



unsigned char *
myaes_ecb_encrypt(unsigned char * text, int length, unsigned char * password, int bits)
{
        AES_KEY aeskey;
        unsigned char * ret = malloc(length);

        unsigned char outbuf[16];

        AES_set_encrypt_key(password,bits,&aeskey);

        int i = 0;
        int blocks = length/16;
        for(i=0;i<blocks;i++)
        {
                AES_ecb_encrypt(text+i*16, outbuf, &aeskey, AES_ENCRYPT);
                memcpy(ret+i*16, outbuf, 16);
        }
               
        return ret;
}


unsigned char *
myaes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * ret;
        unsigned char * outbuf = malloc(length);
       
        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;
       
        memset(outbuf, 0, sizeof(outbuf));
       
        AES_set_encrypt_key(key, bits, &aeskey);

        AES_cbc_encrypt(text, outbuf, length, &aeskey, liv, AES_ENCRYPT);
       
        ret = outbuf;
       
        return ret;
}


unsigned char *
myaes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * outbuf = calloc(1,length);
        int num = 0;
       
        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;
       
        //memset(outbuf, 0, 8);

        AES_set_encrypt_key(key, bits, &aeskey);

        AES_cfb128_encrypt(text, outbuf, length, &aeskey, liv, &num, AES_ENCRYPT);

        return outbuf;
}

unsigned char*
myaes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv, int bits)
{
        unsigned char * outbuf = calloc(1,length);
        int num = 0;

        unsigned char liv[16];

        memcpy(liv,iv,16);

        AES_KEY aeskey;

        //memset(outbuf, 0, 8);

        AES_set_encrypt_key(key, bits, &aeskey);

        AES_ofb128_encrypt(text, outbuf, length, &aeskey, liv, &num);

        return outbuf;
}


unsigned char *
mydes_ecb_encrypt(unsigned char * text, int length, unsigned char * password)
{
        unsigned char * enc;
        unsigned char * key;
       
        enc = malloc(length);
       
        key = malloc(8);
        memcpy((char *)key, password, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)key, (DES_key_schedule *)schedule);

        int blocks = length/8;
        int i;
       
        for(i=0;i<blocks;i++)
        {
                DES_ecb_encrypt((const_DES_cblock *)(text+i*8), (DES_cblock *)(enc+i*8), schedule, DES_ENCRYPT);
        }
       
        return enc;
}


unsigned char *
mydes_cbc_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv)
{
        unsigned char * enc;
        enc = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

        DES_ncbc_encrypt(text, enc, length, schedule, (DES_cblock *)liv, DES_ENCRYPT);

        return enc;
}


unsigned char *
mydes_cfb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv)
{
        unsigned char * enc;
        enc = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

        DES_cfb_encrypt(text, enc, 8, length, schedule, (DES_cblock *)liv, DES_ENCRYPT);

        return enc;
}


unsigned char *
mydes_ofb_encrypt(unsigned char * text, int length, unsigned char * key, unsigned char * iv)
{
        unsigned char * enc;
        enc = malloc(length);
        unsigned char liv[8];

        memcpy(liv,iv,8);

        unsigned char * deskey;
       
        deskey = malloc(8);
        memcpy((char *)deskey, key, 8);

        DES_key_schedule * schedule;
        schedule = malloc(sizeof(DES_key_schedule));
       
        DES_key_sched((const_DES_cblock *)deskey, (DES_key_schedule *)schedule);

        DES_ofb_encrypt(text, enc, 8, length, schedule, (DES_cblock *)liv);

        return enc;
}

