#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "includes/encrypt.h"
#include "includes/defines.h"
#include "includes/imageutils.h"
#include "includes/embed.h"
#include "includes/extract.h"
#include "includes/main.h"
#include "includes/cmdline.h"
#include "includes/decrypt.h"

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
       // printf("TAMANIO:%d\n",sfile -> fileSize);
        inl = sizeof(DWORD) + sfile -> fileSize + strlen(sfile -> extension) + 1;
        printf("Espacio necesario para esteganografiar el archivo \"%s\" = %d.\n\n",args_info->in_arg, inl);

        // aloco espacio para fsize. file contents, fextension y \0

        if ( (in = calloc(1, inl)) == NULL )
        {
            fprintf(stderr, "Memoria insuficiente para esteganografiado del archivo \"%s\"\n", args_info->in_arg);
            freePortadorFile(sfile);
        }

        int endianSize = ntohl(sfile -> fileSize);
        //printf("ENDIAND:%d\n",endianSize);

        /* Nico: Si descomentas la tercer línea vas a tener en "in" todo lo que necesitamos: size, contenido, extension
            y lugar para el \0  */
     //   printf("mensaje: %s\n", sfile->fileContents);
      //  printf("extension: %s\n", sfile->extension);
        memcpy(in, &endianSize, 4);
        memcpy(in + sizeof(DWORD), sfile -> fileContents, sfile -> fileSize);
        memcpy(in + sizeof(DWORD) + sfile -> fileSize, sfile -> extension, strlen(sfile -> extension));
        //PARCHE ARRIBA.
    //    printf("final: %s\n", (char*)(in+4));


        //Calculo Padding
   /*     int padding_size;
        if ( mode == LSBE){
            padding_size = LSBE;
        }else{
            padding_size = mode * RGB;  
        } 

        printf("Padding size = %d\n\n", padding_size);*/

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


        // int message_size = (inl*CHAR_BITS) + (padding_size-(inl*CHAR_BITS)%padding_size);
//        int message_size = (sfile -> fileSize*CHAR_BITS) + (padding_size-(sfile -> fileSize*CHAR_BITS)%padding_size);


   //     int file_size;
    //    file_size = message_size;
        char * extension = sfile -> extension;
        // char * bit_array = calloc(1,32+padding_size+inl*CHAR_BITS);
        char * bit_array = calloc(1,inl*8);

        //Imprimo informacion sobre la imagen
        print_bmp_image(image);

        // Me muevo 4 bytes para pasar directamente al texto!
       // ptr = in + sizeof(int);


        //ARMO EL VECTOR CON LOS BITS
        //PRIMERO ME QUEDO CON EL TAMANIO
        h =0;
        //printf("Padding: %d\n", padding_size);
        //printf("File size: %d => ", file_size);
/*        for(i = 31; i >= 0; --i){
                if (endianSize & 1 << i){
                    bit_array[h] = '1';
                }else{
                    bit_array[h] = '0';
                }
                printf("%c",bit_array[h]);
                h++;
        }
            putchar('\n');
            h= h+1;*/
/*        if( mode == LSB1){
            //1 BIT DE CORRECION PARA QUE SEA MULTIPLO DE 3
            bit_array[h++] = '0';
        }else if ( mode == LSB4){
            //4 BIT DE CORRECION PARA QUE SEA MULTIPLO DE 12
            bit_array[h++] = '0';
            bit_array[h++] = '0';
            bit_array[h++] = '0';
            bit_array[h++] = '0';
        }
        
        int size_length = h;*/
       // h=0;
        printf("Armo el array de bits para estenografear: \n");
/*
        for(; h<32*8; h++){
            printf("%c", *(in-40));
            in++;
        }

        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);*/
        
        //LUEGO PONGO LOS BITS DEL MENSAJE
        for(h=0; h < inl*8; ++in)
        {
            printf("%c => ", *in);
            /* perform bitwise AND for every bit of the character */
            for(i = 7; i >= 0; --i){
                if (*in & 1 << i){
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
       /* for (; h<(message_size+size_length);h++){
            bit_array[h] = '0';
        }

        printf("Extension bits: \n");*/
         //LUEGO PARSEO LA EXTENSION
       /* for(; *extension != 0; ++extension)
        {
            printf("%c => ", *extension);*/
            /* perform bitwise AND for every bit of the character */
       /*     for(i = 7; i >= 0; --i){
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
            }*/

            //Actualizo el tamanio total
          printf("ACA ESTA H:%d\n",h);
            bit_array_size = h;
         /*   for( k = 0; k<bit_array_size;k++)
                printf("%c", bit_array[k]);
            putchar(10);*/
            
            char* encryptedData=NULL;
            if(password != NULL){
                //encryptedData=encryptData(primitiva,modo,bit_array);
            }

            
            printf("in_array_size= %d bits.\n", inl);
            //Chequeo que se pueda almacenar la informacion en la imagen.
            //TODO: VAMOS A TENER QUE VER COMO CALCULAR LA CAPACIDAD CON LSBE
            if ( image_capacity < bit_array_size){
                fprintf(stderr, "Error: La imagen no tiene la capacidad de almacenar el archivo, la capacidad maxima es %d.\n\n", image_capacity);
                exit(EXIT_FAILURE);
            }

            printf("PASE TODO\n");
            //Llamo a la funcion correspondiente dependiendo del modo
            if ( mode == LSB1 ){
             //   printf("ENTRO A LSB1");
                encrypt_LSB1(image, bit_array, bit_array_size);
             //   decrypt_LSB1(image,"salida2.txt");
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
        /* MODO EXTRACT */

        //Abro la imagen
        BmpImage image2 = create_bmp_image(args_info->p_arg);

        // Cargo la imagen
        if(load_bmp_image(image2) != LOADING_OK){
            fprintf(stderr, "Error: No se ha podido cargar la imagen con contenido oculto. Compruebe que la ruta \"%s\" sea correcta.\n\n", args_info->p_arg);
            exit(EXIT_FAILURE);
        }

        char * out_filename = args_info->out_arg;

        if ( mode == LSB1 ){
            decrypt_LSB1(image2, out_filename);
        }else if ( mode == LSB4 ){
            decrypt_LSB4(image2, out_filename);
        }else{
            decrypt_LSBE(image2, out_filename);
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