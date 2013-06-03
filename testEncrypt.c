#include "includes/encrypt.h"
#include "includes/decrypt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 //Compilarlo con : gcc testEncrypt.c encrypt.c decrypt.c -lm -lcrypto
int 
main(void){
	unsigned char * message= "mensajede16bitss";
        unsigned char * enc;
        unsigned char * out;
        unsigned char * iv="holacomo";
        unsigned char * password="dinudinu";
       
 
        int length = strlen((char *)message);
	printf("El Mensaje a encryptar es :%s\n",message);
	printf("PRUEBA DE DES OFB\n");        
        enc = mydes_ofb_encrypt( message, length, password, iv);
        out = mydes_ofb_decrypt( enc, length, password, iv);
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE DES ECB\n"); 
	enc=mydes_ecb_encrypt( message, length, password);
	out=mydes_ecb_decrypt( enc, length, password);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE DES CBC\n"); 
	enc=mydes_cbc_encrypt( message, length, password,iv);
	out=mydes_cbc_decrypt( enc, length, password,iv);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");

	printf("PRUEBA DE DES CFB\n"); 
	enc=mydes_cfb_encrypt( message, length, password,iv);
	out=mydes_cfb_decrypt( enc, length, password,iv);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");

	printf("PRUEBA DE AES128 ECB\n"); 
	enc=myaes_ecb_encrypt( message, length, password,128);
	out=myaes_ecb_decrypt( enc, length, password,128);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES128 CBC\n"); 
	enc=myaes_cbc_encrypt( message, length, password,iv,128);
	out=myaes_cbc_decrypt( enc, length, password,iv,128);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES128 CFB\n"); 
	enc=myaes_cfb_encrypt( message, length, password,iv,128);
	out=myaes_cfb_decrypt( enc, length, password,iv,128);	
        printf("%s\n",enc);
        printf("%s\n",out);
	printf("-----------------------------\n");
	free(enc);
	free(out);
	printf("PRUEBA DE AES128 OFB\n"); 
	enc=myaes_ofb_encrypt( message, length, password,iv,128);
	out=myaes_ofb_decrypt( enc, length, password,iv,128);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);

	printf("-----------------------------\n");
	printf("PRUEBA DE AES 192 ECB\n"); 
	enc=myaes_ecb_encrypt( message, length, password,192);
	out=myaes_ecb_decrypt( enc, length, password,192);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES192 CBC\n"); 
	enc=myaes_cbc_encrypt( message, length, password,iv,192);
	out=myaes_cbc_decrypt( enc, length, password,iv,192);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES192 CFB\n"); 
	enc=myaes_cfb_encrypt( message, length, password,iv,192);
	out=myaes_cfb_decrypt( enc, length, password,iv,192);	
        printf("%s\n",enc);
        printf("%s\n",out);
	printf("-----------------------------\n");
	free(enc);
	free(out);
	printf("PRUEBA DE AES192 OFB\n"); 
	enc=myaes_ofb_encrypt( message, length, password,iv,192);
	out=myaes_ofb_decrypt( enc, length, password,iv,192);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);

	printf("-----------------------------\n");
	printf("PRUEBA DE AES 256 ECB\n"); 
	enc=myaes_ecb_encrypt( message, length, password,256);
	out=myaes_ecb_decrypt( enc, length, password,256);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES256 CBC\n"); 
	enc=myaes_cbc_encrypt( message, length, password,iv,256);
	out=myaes_cbc_decrypt( enc, length, password,iv,256);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);
	printf("-----------------------------\n");
	printf("PRUEBA DE AES256 CFB\n"); 
	enc=myaes_cfb_encrypt( message, length, password,iv,256);
	out=myaes_cfb_decrypt( enc, length, password,iv,256);	
        printf("%s\n",enc);
        printf("%s\n",out);
	printf("-----------------------------\n");
	free(enc);
	free(out);
	printf("PRUEBA DE AES256 OFB\n"); 
	enc=myaes_ofb_encrypt( message, length, password,iv,256);
	out=myaes_ofb_decrypt( enc, length, password,iv,256);	
        printf("%s\n",enc);
        printf("%s\n",out);
	
	free(enc);
	free(out);

	printf("-----------------------------\n");


        return 0;

}

 
