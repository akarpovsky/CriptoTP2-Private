#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <openssl/evp.h>

#include "includes/defines.h"
#include "includes/imageutils.h"
#include "includes/embed.h"
#include "includes/extract.h"
#include "includes/main.h"
#include "includes/cmdline.h"
#include "includes/crypto.h"
#include "includes/portador.h"

int main(int argc, char **argv){
    
    struct gengetopt_args_info *args_info = malloc(sizeof(struct gengetopt_args_info));

    int type; // Encrypt | Decrypt (Embed | Extract)
    
    int mode; // LSBE | LSB4 | LSBE

    char * ptr; //Mensaje a Cifrar

    /* Para encriptación */
    char * algorithm = args_info->a_arg; // Algoritmo de encriptacion (AES128, DES, etc)
    char * encrypt_mode = args_info->m_arg; // Modo de encriptacion (CBC, OFB, etc)
    char * password = args_info->pass_arg; // Password ingresada por el usuario
    /* Fin encriptación */ 

    // Levanto argumentos de la linea de comandos
    if(cmdline_parser(argc, argv, args_info) != 0) {
        return EXIT_FAILURE;
    }

    if(args_info->ENCRYPT_mode_counter){
        printf("\n\nModo: Encrypt (EMBED)\n\n");
        type = ENCRIPT;
    }else if(args_info->DECRYPT_mode_counter){
        printf("\n\nModo: Decrypt (EXTRACT)\n\n");
        type = DECRIPT;
    }else{
        fprintf(stderr, "Error: Modo de operación no reconocido. Pruebe ejecutar el programa con --help para obtener ayuda.\n\n");
        exit(EXIT_FAILURE);
    }

    printUserArguments(args_info);

    //Completo el modo (steg_orig guarda el algoritmo de esteganografiado)
    getStenographyMode(args_info->steg_arg,&mode);

    
    int i,j,h,k;

    if ( type == ENCRIPT){

        PortadorFileT * sfile;
        unsigned char * in, * out;
        int outl, inl, padsize;

        if ( (sfile = readPortadorData(args_info->in_arg)) == NULL)
        {
            fprintf(stderr, "Error al leer el archivo archivo a encriptar: \"%s\".\n\n", args_info->in_arg);
            exit(EXIT_FAILURE);
        }

        //  calculo espacio necesario para: size + file contents + file extension length + \0
        inl = sizeof(DWORD) + sfile -> fileSize + strlen(sfile -> extension) + 1;
        printf("Espacio necesario para esteganografiar el archivo \"%s\" = %d.\n\n",args_info->in_arg, inl);

        // aloco espacio para fsize. file contents, fextension y \0

        if ( (in = calloc(1, inl)) == NULL )
        {
            fprintf(stderr, "Memoria insuficiente para esteganografiado del archivo \"%s\"\n", args_info->in_arg);
            freePortadorFile(sfile);
        }

        int endianSize = ntohl(sfile -> fileSize);

        memcpy(in, &endianSize, 4);
        memcpy(in + sizeof(DWORD), sfile -> fileContents, sfile -> fileSize);
        memcpy(in + sizeof(DWORD) + sfile -> fileSize, sfile -> extension, strlen(sfile -> extension));

        //Abro la imagen
        BmpImage image = create_bmp_image(args_info->p_arg);

        //Cargo la imagen
        if(load_bmp_image(image) != LOADING_OK){
            fprintf(stderr, "Error: No se ha podido cargar la imagen portadora. Compruebe que la ruta \"%s\" sea correcta.\n\n", args_info->p_arg);
            exit(EXIT_FAILURE);
        }

       // printf("Armo el array de bits para estenografear: \n");

        char * bit_array = calloc(1,inl*8);
        for(h=0; h < inl*8; ++in)
        {
          //  printf("%c => ", *in);
            /* Se hace el and bit a bit */
            for(i = 7; i >= 0; --i){
                if (*in & 1 << i){
                    bit_array[h] = '1';
                }else{
                    bit_array[h] = '0';
                }
           //     printf("%c",bit_array[h]);
                h++;
            }
            //putchar('\n');
        }

        //Imprimo informacion sobre la imagen
        print_bmp_image(image);

        int image_capacity = image->width * image->height * mode;
		if(password==NULL)
		    	if ( image_capacity < inl){
	              		fprintf(stderr, "Error: La imagen no tiene la capacidad de almacenar el archivo, la capacidad maxima es %d.\n\n", image_capacity);
	               		exit(EXIT_FAILURE);
	            	}
		/*else			
			if ( image_capacity < encrypted_bit_array_size){
	              		fprintf(stderr, "Error: La imagen no tiene la capacidad de almacenar el archivo, la capacidad maxima es %d.\n\n", image_capacity);
	               		exit(EXIT_FAILURE);
	            	}*/
            
            //Llamo a la funcion correspondiente dependiendo del modo
            if ( mode == LSB1 ){
             //   printf("ENTRO A LSB1");
                encrypt_LSB1(image, bit_array, inl*8);//:encrypt_LSB1(image, encrypted_bit_array, encrypted_bit_array_size);
             //   decrypt_LSB1(image,"salida2.txt");
            }else if ( mode == LSB4 ){
                encrypt_LSB4(image, bit_array, inl*8);//:encrypt_LSB4(image, encrypted_bit_array, encrypted_bit_array_size);
            }else{
               encrypt_LSBE(image, bit_array, inl*8);//: encrypt_LSBE(image, encrypted_bit_array, encrypted_bit_array_size);
            }
            //Salvo la nueva imagen
            if(save_bmp_image(image, args_info->out_arg) == FALSE){
                fprintf(stderr, "Error: No se ha podido crear el archivo de salida \"%s\".\n\n", args_info->out_arg);
                exit(EXIT_FAILURE);
            }else{
                printf("Creado el archivo de salida: \"%s.bmp\"\n\n", args_info->out_arg);
            }

    }else{
        /* MODO EXTRACT */

        char * out_filename = args_info->out_arg;

        //Abro la imagen
        BmpImage image = create_bmp_image(args_info->p_arg);
        

        // Cargo y hago el extract de la imagen
        if(extract_bmp_image(image, out_filename, mode,NULL,NULL,NULL) != LOADING_OK){
            fprintf(stderr, "Error: No se ha podido extraer el contenido oculto de la imagen con contenido. Compruebe que la ruta \"%s\" sea correcta.\n\n", args_info->p_arg);
            exit(EXIT_FAILURE);
        }

    }

    printf("Fin del Programa\n");
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

unsigned char *
paddingPKCS5(unsigned char *in, int *inl, size_t blocksize) {
    int pad;
    int i;
    unsigned char *inPad;
    pad = blocksize - (*inl) % blocksize;
    inPad = malloc(*inl + pad);
    memcpy(inPad, in, *inl);
    for (i = (*inl); i < (*inl + pad); i++)
        inPad[i] = pad;
    *inl +=pad;
    return (inPad);
}
