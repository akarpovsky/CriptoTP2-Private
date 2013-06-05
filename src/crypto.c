#include "includes/defines.h"
#include "includes/crypto.h"
#include <openssl/evp.h>

unsigned char *
encryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl, char* action){
	
	char* encryptedData= encryptAndDecryptData(algorithm, mode,password, data, lenght, outl,"ENCRYPT");
	//TODO TENGO Q CALCULAR EL TAMAÑO Y PONERSELO ADELANTE

	
}


unsigned char *
decryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl, char* action){

	return encryptAndDecryptData(algorithm,mode,password,data,lenght,outl,"DECRYPT");
}


unsigned char*
encryptAndDecryptData(unsigned char* algorithm,unsigned char * mode,unsigned char * password,unsigned char* data,int lenght int * outl, char* action){
	int primitive=0;
    	int chaining=-1;
	int bits=0, templ=0;
	int enc=0;
	//TODO: FIJARSE QUE VALORES NECESITA ACTION PARA ENCRIPTAR Y DESENCRIPTAR
	unsigned char key[TAM_CLAVE], iv[TAM_CLAVE];
	unsigned char* out=malloc(lenght+1);
	EVP_CIPHER_CTX ctx;
	
	getOptions(algorithm, mode,&primitive,&chaining,&bits);
	//creo la Key y el IV a partir de la pass que me dan

	//TODO: FIJARSE COMO SACAR EL ALGORITMO SIN HACER 500 IFs
	EVP_BytesToKey(ALGORITMO, EVP_md5(),NULL,password,strlen(password),1,key,iv);
	//Inicializo el contexto
	EVP_CIPHER_CTX_init(&ctx);
	//le digo con que algoritmo, key e iv voy a trabajar y si quiero encriptar o desencriptar


	EVP_CipherInit_ex(ctx, ALGORITMO, NULL, key, iv, enc);
	//encrypta data de longitud lenght y lo pone en out y guarda en outl el tamaño
	EVP_CipherUpdate(&ctx, out, outl, data, lenght);
	//encrypta el ultimo bloque, paddea con PKCS5 y deja en templ el tamaño.
	EVP_CipherFinal_ex(&ctx, out + *outl, &templ); 

	*outl +=templ;
		
	//Limpio la estructura
	EVP_CIPHER_CTX_cleanup(&ctx);

	return out;
}

void
getOptions(char* algorithm, char* mode, int* primitive, int* chaining, int* bits){
if(algorithm !=NULL){

        if( strcmp(algorithm,"aes128")==0){
            *primitive= AES128;
            *bits=128;
        }else if ( strcmp(algorithm,"aes192")==0){
            *primitive= AES192;
            *bits=192;
        }else if ( strcmp(algorithm,"aes256")==0){
            *primitive= AES256;
            *bits=256;
        }else if ( strcmp(algorithm,"des")==0){
            *primitive= DES;
        }
    }else{
        *primitive= AES128;    
        *bits=128;
    }

    if(mode !=NULL){
            if( strcmp(mode,"ecb")==0){
                *chaining=ECB;
            }else if(strcmp(mode,"cfb")==0){
                *chaining=CBF;
            }else if(strcmp(mode,"ofb")==0){
                *chaining=OFB;
            }else if(strcmp(mode,"cbc")==0){
                *chaining=CBC;
            }
    }else{
        *chaining=CBC;
        }   
}

