#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "includes/defines.h"
#include "includes/imageutils.h"
#include "includes/encrypt.h"
#include "includes/decrypt.h"
#include "includes/main.h"
#include "includes/cmdline.h"

int main(int argc, char **argv){
	
    struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

    //Parametros cableados
    int type;
    int mode;
    int primitiva=0;
    int modo=-1;
     char * accion;
    //Mensaje a Cifrar
    char * ptr = "KarpoyDinu";
    char * imagen_levantar = args_info->out_arg;
    
    char * password =args_info->pass_arg;

    /*
     *
     *  Empieza Programa
     *
     */

	// Levanto argumentos de la linea de comandos
	if(cmdline_parser(argc, argv, args_info) != 0) {
		return EXIT_FAILURE;
	}

	if(args_info->ENCRYPT_mode_counter){
		printf("\n\nModo: Encrypt (EMBED)\n\n");
		accion = "ENCRIPT";
		type = ENCRIPT;
	}else if(args_info->DECRYPT_mode_counter){
		printf("\n\nModo: Decrypt (EXTRACT)\n\n");
		accion = "DECRIPT";
		type = DECRIPT;
	}else{
        fprintf(stderr, "Error: Modo de operación no reconocido. Pruebe ejecutar el programa con --help para obtener ayuda.\n\n");
        exit(EXIT_FAILURE);
	}

	printUserArguments(args_info);

	//Completo el modo (steg_orig guarda el algoritmo de esteganografiado)
	getStenographyMode(args_info->steg_arg,&mode);

	getPrimiteAndMode(args_info->a_arg,args_info->m_arg,&primitiva,&modo);

	
	//Calculo Padding
	int padding_size;
	if ( mode == LSBE){
		padding_size = LSBE;
	}else{
		padding_size = mode * RGB;	
	} 

	//Abro la imagen
	BmpImage image = create_bmp_image(args_info->p_arg);
	//Cargo la imagen
	if(load_bmp_image(image) != LOADING_OK){
        fprintf(stderr, "Error: No se ha podido cargar la imagen portadora. Compruebe que la ruta \"%s\" sea correcta.\n\n", args_info->p_arg);
        exit(EXIT_FAILURE);
    }


	//Calculo capacidad de la imagen
	int image_capacity = image->width * image->height * mode;


	//Hace que el size sea múltiplo de LSB correspondiente y agrega padding
	int bit_array_size;
	int message_size = (strlen(ptr)*CHAR_BITS) + (padding_size-(strlen(ptr)*CHAR_BITS)%padding_size);
	

	int file_size;
	file_size = message_size;
	char * extension = ".txt";
	char * bit_array = malloc(32+padding_size+strlen(ptr)*CHAR_BITS+strlen(extension)*CHAR_BITS);

	//Imprimo informacion sobre la imagen
	print_bmp_image(image);

	int i,j,h,k;


	if ( type == ENCRIPT){

        FILE *fp;

        fp = fopen(args_info->in_arg, "rb");

        if(fp == NULL){
            fprintf(stderr, "Error: No se ha podido abrir el archivo \"%s\" que se desea ocultar (--in).\n\n", args_info->in_arg);
            exit(EXIT_FAILURE);
        }

    	//ARMO EL VECTOR CON LOS BITS
    	//PRIMERO ME QUEDO CON EL TAMANIO
    	h =0;
        printf("%d => ", file_size);
       	for(i = 31; i >= 0; --i){
                if (file_size & 1 << i){
                	bit_array[h] = '1';
                }else{
                	bit_array[h] = '0';
                }
                printf("%c",bit_array[h]);
            	h++;
    	}
        putchar('\n');

        if( mode == LSB1){
        	//1 BIT DE CORRECION PARA QUE SEA MULTIPLO DE 3
        	bit_array[h++] = '0';
        }else if ( mode == LSB4){
        	//4 BIT DE CORRECION PARA QUE SEA MULTIPLO DE 12
        	bit_array[h++] = '0';
        	bit_array[h++] = '0';
        	bit_array[h++] = '0';
        	bit_array[h++] = '0';
        }
        
        int size_length = h;

        //LUEGO PONGO LOS BITS DEL MENSAJE
    	for(; *ptr != 0; ++ptr)
        {
            printf("%c => ", *ptr);
            /* perform bitwise AND for every bit of the character */
            for(i = 7; i >= 0; --i){
                if (*ptr & 1 << i){
                	bit_array[h] = '1';
                }else{
                	bit_array[h] = '0';
                }
                printf("%c",bit_array[h]);
            	h++;
    		}
            putchar('\n');
        }

    	//Completo el Padding con 0 para que no afecte el ocultamiento.
        for (; h<(message_size+size_length);h++){
        	bit_array[h] = '0';
        }

         //LUEGO PARSEO LA EXTENSION
        for(; *extension != 0; ++extension)
        {
            printf("%c => ", *extension);
            /* perform bitwise AND for every bit of the character */
            for(i = 7; i >= 0; --i){
                if (*extension & 1 << i){
                	bit_array[h] = '1';
                }else{
                	bit_array[h] = '0';
                }
                printf("%c",bit_array[h]);
            	h++;
    		}
            putchar('\n');
        }


        //Completo el Padding con 0 para que no afecte el ocultamiento.
        if( mode != LSBE){
        	for ( i = h; (h%padding_size) != 0;h++){
        		bit_array[h] = '0';
        	}
    	}

        //Actualizo el tamanio total
        bit_array_size = h;
        for( k = 0; k<bit_array_size;k++)
        	printf("%c", bit_array[k]);
        putchar(10);
    	
    //	char* encryptedData=NULL;
    //	if(primitive!= NO_ENCRYPTION)
    //		encryptedData=encryptData(primitiva,modo,bit_array);

        	
        	//Chequeo que se pueda almacenar la informacion en la imagen.
        	//TODO: VAMOS A TENER QUE VER COMO CALCULAR LA CAPACIDAD CON LSBE
        	if ( image_capacity < bit_array_size){
                fprintf(stderr, "Error: La imagen no tiene la capacidad de almacenar el archivo, la capacidad maxima es %d.\n\n", image_capacity);
                exit(EXIT_FAILURE);
    		}
       		
       		//Llamo a la funcion correspondiente dependiendo del modo
        	if ( mode == LSB1 ){
        		encrypt_LSB1(image, bit_array, bit_array_size);
        	}else if ( mode == LSB4 ){
        		encrypt_LSB4(image, bit_array, bit_array_size);
        	}else{
    			encrypt_LSBE(image, bit_array, bit_array_size);
    		}
        	//Salvo la nueva imagen
    		if(save_bmp_image(image, args_info->out_arg) == FALSE){
                fprintf(stderr, "Error: No se ha podido crear el archivo de salida \"%s\".\n\n", args_info->out_arg);
                exit(EXIT_FAILURE);
            }else{
                printf("Creado el archivo de salida: \"%s\".\n\n", args_info->out_arg);
            }

	}else{
		//MODO DESCIFRAR: 

		//Abro la imagen
		// BmpImage image = create_bmp_image(imagen_levantar);
		//Cargo la imagen
		load_bmp_image(image);
 		
 		if ( mode == LSB1 ){
    		decrypt_LSB1(image);
    	}else if ( mode == LSB4 ){
    		decrypt_LSB4(image);
    	}else{
			decrypt_LSBE(image);
		}


	}

	printf("Fin del Programa\n");
}

void
getPrimiteAndMode(char* primitive, char* chaining , int* primitiva, int* modo){
if(primitive !=NULL){
		if( strcmp(primitive,"aes128")==0){
			*primitiva= AES128;
		}else if ( strcmp(primitive,"aes192")==0){
			*primitiva= AES192;
		}else if ( strcmp(primitive,"aes256")==0){
			*primitiva= AES256;
		}else if ( strcmp(primitive,"des")==0){
			*primitiva= DES;
		}

		if(chaining !=NULL){
			if( strcmp(chaining,"ecb")==0){
				*modo=ECB;
			}else if(strcmp(chaining,"cfb")==0){
				*modo=CBF;
			}else if(strcmp(chaining,"ofb")==0){
				*modo=OFB;
			}else if(strcmp(chaining,"cbc")==0){
				*modo=CBC;
		}else
			*modo=CBC;
		}
	}
}
void
getStenographyMode(char* estenografia, int* mode){
if ( strcmp(estenografia,"LSB1") == 0){
		*mode = LSB1;
	}else if (strcmp(estenografia,"LSB4") == 0){
		*mode = LSB4;
	}else if(strcmp(estenografia,"LSBE") == 0){
		*mode = LSBE;
	}
}

void 
printUserArguments(struct gengetopt_args_info *args_info){
	printf("*******************************************************\n");
	printf("Parámetros obligatorios:\n");
	if(args_info->ENCRYPT_mode_counter){
		printf("Modo: Encrypt (EMBED)\n\n");
		printf("\tAlgoritmo de esteganografiado: %s\n", args_info->steg_arg);
		printf("\tArchivo a ocultar: %s\n", args_info->in_arg);
	}else if(args_info->DECRYPT_mode_counter){
		printf("Modo: Decrypt (EXTRACT)\n\n");
		printf("\tAlgoritmo de esteganografiado: %s\n", args_info->steg_arg);

	}
		printf("\tArchivo portador: %s\n", args_info->p_arg);
		printf("\tArchivo de salida: %s\n", args_info->out_arg);
	
	printf("\nParámetros opcionales:\n");
	
	if(args_info->a_orig == NULL){
		printf("\tAlgoritmo de encripción: %s [USING DEFAULT]\n", args_info->a_arg);
	}else{
		printf("\tAlgoritmo de encripción: %s\n", args_info->a_arg);
	}

	if(args_info->m_orig == NULL){
		printf("\tModo de encadenamiento: %s [USING DEFAULT]\n", args_info->m_arg);
	}else{
		printf("\tModo de encadenamiento: %s\n", args_info->m_arg);
	}

	if(args_info->pass_orig == NULL){
		printf("\tPassword no especificada\n");
	}else{
		printf("\tPassword: %s\n", args_info->pass_arg);
	}

	printf("\n*******************************************************\n\n");
}

