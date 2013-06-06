
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "includes/crypto.h"
#include "includes/defines.h"
#include <openssl/evp.h>
int
main(void){


	unsigned char* mensaje= "Inteligencia, dame el nombre exacto de las cosas... Quemi palabra sea la cosa misma, creada por mi alma nuevamente.";
	unsigned char* out; 
	unsigned char* mensaje2;
	char* key= "dinudinu";
	int outl=0;
	int outl2=0;
	int i=0;
	out=encryptData("aes256","ofb",key,mensaje,strlen(mensaje) ,&outl);
	
	printf("la longitud de mensaje es %d y la del mensaje encriptado es %d\n\n",strlen(mensaje),outl);
	mensaje2=decryptData("aes256","ofb",key,out,outl,&outl2);
	
	for(i=0; i<outl2; i++){
		printf("%c",*(mensaje2+i));
	}
	printf("\n");
	return 1;
}
