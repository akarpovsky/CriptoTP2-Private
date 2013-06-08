#include "includes/defines.h"
#include "includes/crypto.h"
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

unsigned char*
encryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght ,int * outl){

	return encryptAndDecryptData(algorithm,mode,password,data,lenght ,outl, ENCRIPT);
}

unsigned char*
decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght ,int * outl){

	return encryptAndDecryptData(algorithm,mode,password,data,lenght ,outl, DECRIPT);
}
unsigned char*
encryptAndDecryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght ,int * outl, int action){
	int primitive=0;
    	int chaining=-1;
	int templ=0;
	const EVP_CIPHER * cipher = getCipher(algorithm, mode);
	
	unsigned char* key= (unsigned char*) malloc(sizeof(unsigned char)*EVP_CIPHER_key_length(cipher));
	unsigned char* iv= (unsigned char*)malloc(sizeof(unsigned char)*EVP_CIPHER_iv_length(cipher));
	unsigned char* out=malloc(lenght + EVP_CIPHER_block_size(cipher));
	
	EVP_CIPHER_CTX ctx;
	
	//creo la Key y el IV a partir de la pass que me dan

	EVP_BytesToKey(cipher, EVP_md5(),NULL,password,strlen(password),1,key,iv);
	//Inicializo el contexto
	EVP_CIPHER_CTX_init(&ctx);
	//le digo con que algoritmo, key e iv voy a trabajar y si quiero encriptar o desencriptar


	EVP_CipherInit_ex(&ctx,cipher, NULL, key, iv, action);
	//encrypta data de longitud lenght y lo pone en out y guarda en outl el tamaño
	EVP_CipherUpdate(&ctx, out, outl, data, lenght);
	//encrypta el ultimo bloque, paddea con PKCS5 y deja en templ el tamaño.
	EVP_CipherFinal_ex(&ctx, out + *outl, &templ); 

	*outl +=templ;
		
	//Limpio la estructura
	EVP_CIPHER_CTX_cleanup(&ctx);
	free(key);
	free(iv);

	return out;
}


const EVP_CIPHER* 
getCipher(char* algorithm, char* mode/*, int* bits*/){

	OpenSSL_add_all_ciphers();
	unsigned char cipherName[13];
	
	if(algorithm !=NULL){

       		if( strcmp(algorithm,"aes128")==0){
       	     		 strcpy(cipherName,"aes-128-");
            		
        	}else if ( strcmp(algorithm,"aes192")==0){
           		 strcpy(cipherName,"aes-192-");
            		
        	}else if ( strcmp(algorithm,"aes256")==0){
          		 strcpy(cipherName,"aes-256-");
           		
       		}else if ( strcmp(algorithm,"des")==0){
      	      		strcpy(cipherName,"des-");
       		}
   	}else{
        strcpy(cipherName,"aes-128-");   
        
   	}
	
	if(mode !=NULL){
        	if( strcmp(mode,"ecb")==0){
        	        strcat(cipherName,"ecb");
        	}else if(strcmp(mode,"cfb")==0){
                	strcat(cipherName,"cfb");
            	}else if(strcmp(mode,"ofb")==0){
                	strcat(cipherName,"ofb");
            	}else if(strcmp(mode,"cbc")==0){
                	strcat(cipherName,"cbc");
            	}
    	}else{
        	strcat(cipherName,"cbc");
        }   

	return EVP_get_cipherbyname(cipherName);



}
