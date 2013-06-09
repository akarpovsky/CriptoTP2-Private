#include "includes/defines.h"
#include "includes/imageutils.h"
#include "includes/embed.h"
#include "includes/extract.h"
#include "includes/main.h"
#include "includes/cmdline.h"
#include "includes/crypto.h"
#include "includes/portador.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <openssl/evp.h>


int decrypt_LSBE(BmpImage image, char * out_filename, FILE * fp , char* algorithm, char* encrypt_mode, char* password){

    int size, i,decryptedSize;
    char * msg;
    char * ext;
    unsigned char * decryptedMsg;
  
    for(i=0; i<4; i++){
        *(((char*)&size)+3-i)=get_lsbe(fp);
    }
    printf("NUEVO SIZE:%d\n", size);

    msg = calloc(size+10, sizeof(char));
    ext = calloc(10, sizeof(char));

    for(i=0; i<size; i++){
        msg[i]=get_lsbe(fp);
    }
    
    
    i = 0;
    if(password==NULL){
    	do{
  	         ext[i]=get_lsbe(fp);
   	         i++;
   	 }while(ext[i-1]);
	 image->data=msg;
	 image->size=size;
	 image->extension = ext;
    }else{
		decryptedMsg=(unsigned char *)decryptData( algorithm, encrypt_mode, password,msg ,size ,&decryptedSize);
		image->data=decryptedMsg;
	 	image->size=decryptedSize;
	 	image->extension = decryptedMsg+decryptedSize;
		
	}

    	 

    char file_name[100];
    strcpy (file_name,out_filename);
    strcat (file_name,image->extension);
    FILE * salida = fopen(file_name, "wb");
    FCHK(fwrite(image->data, image->size, sizeof(char), salida)); 

}

int decrypt_LSB4(BmpImage image, char * out_filename, FILE * fp ,char* algorithm, char* encrypt_mode, char* password){   


    int size =0,decryptedSize;
    int i;
    char * msg;
    char * ext;
    unsigned char * decryptedMsg;
   
    for(i=0; i<4; i++){
       *(((char*)&size)+3-i)=get_lsb4(fp);
    }
    printf("NUEVO SIZE:%d\n", size);

    msg = calloc(size+10, sizeof(char));
    ext = calloc(10, sizeof(char));

    for(i=0; i<size; i++){
        msg[i]=get_lsb4(fp);
    }
    
    
    i = 0;
    if(password==NULL){
    	do{
    	        ext[i]=get_lsb4(fp);
    	        i++;
    	}while(ext[i-1]);
	 image->data=msg;
	 image->size=size;
	 image->extension = ext;
    }else{
		decryptedMsg=(unsigned char *)decryptData( algorithm, encrypt_mode, password,msg ,size ,&decryptedSize);
		image->data=decryptedMsg;
	 	image->size=decryptedSize;
	 	image->extension = decryptedMsg+decryptedSize;
		
	}

    char file_name[100];
    strcpy (file_name,out_filename);
    strcat (file_name,image->extension);
    FILE * salida = fopen(file_name, "wb");
    FCHK(fwrite(image->data,image->size, sizeof(char), salida)); 


}


int decrypt_LSB1(BmpImage image, char * out_filename, FILE * fp, char* algorithm, char* encrypt_mode, char* password){


    int size=0, i, decryptedSize;
    char * msg;
    char * ext;
    char file_name[100];// = malloc(100); 
    unsigned char * decryptedMsg;
    for(i=0; i<4; i++){
        *(((char*)&size)+3-i)=get_lsb1(fp);
	
    }
    	printf("NUEVO SIZE:%d\n", size);

    msg = calloc(size+10, sizeof(char));
    ext = calloc(10, sizeof(char));


    for(i=0; i<size; i++){
        msg[i]=get_lsb1(fp);
    }
    	  
    i = 0;
    if(password==NULL){
	
  	  do{
    	        ext[i]=get_lsb1(fp);
    	        i++;
  	 }while(ext[i-1]);
   	 image->data=msg;
   	 image->size=size;
    image->extension = ext;

    }else{
		
		decryptedMsg=(unsigned char *) decryptData( algorithm, encrypt_mode, password,msg ,size ,&decryptedSize);
			
		image->data=decryptedMsg+sizeof(DWORD);
		for(i=0; i<4; i++){
			*(((char*)&size)+3-i)=*(decryptedMsg+i);
		}
	 	image->size=size;//decryptedSize-5-sizeof(DWORD);
	 	image->extension = decryptedMsg+size+sizeof(DWORD);
		
	}
 
    strcpy (file_name,out_filename);
    strcat (file_name,image->extension);
    FILE * salida = fopen(file_name, "wb");
    FCHK(fwrite(image->data, (size_t)image->size, sizeof(char), salida)); 
}

char get_lsb1(FILE* in){
    int i;
    char byte=0, hidden;
    for(i=0; i<8; i++){
        hidden = fgetc(in);
        char bit=(hidden&1);
        byte|=(bit<<(7-(i%8)));
    }
    return byte;
}

char get_lsb4(FILE* in){
    int i;
    char byte=0, hidden;
    for(i=0; i<2; i++){
        hidden = fgetc(in);
        char nibble=(hidden&0x0F);
        byte|=nibble<<(1- i%2)*4;
    }

    return byte;
}

char get_lsbe(FILE* in){
    int i;
    char byte=0, hidden;
    for(i=0; i<8; i++){
        do{
            hidden = fgetc(in);
        }while(!( hidden==(char)0xFF || hidden==(char)0xFE));
        char bit=(hidden&1);
        byte|=(bit<<(7-(i%8)));
    }
    return byte;
}
