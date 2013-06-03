#include "includes/defines.h"
#include "includes/extract.h"
#include <math.h>

int decrypt_LSBE(BmpImage image){

    //Recupero el mensaje;
    int i,j,k,h, bit_array_size;
    char * aux2 = calloc (1,32);
    char * aux3 = calloc (1,64);
    char * ans_extension = calloc(1,64);
    int * tamanio = calloc(1,sizeof(int));
    int ocultar = FALSE;
    h = 0;

    //Leo los primeros 32 para obtener el size;
     for( j=0; j<image->height && h<32; j++ ) {
        for( i=0; i<image->width && h<32; i++) {
            if ( image->bitmap[(j*image->width) + i].red >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                
                ocultar--;
                aux2[h++] = image->bitmap[(j*image->width) + i].red & 1;
            }
            if ( image->bitmap[(j*image->width) + i].green >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                
                ocultar--;
                aux2[h++] = image->bitmap[(j*image->width) + i].green & 1;
            }   
            if ( image->bitmap[(j*image->width) + i].blue >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                
                ocultar--;
                aux2[h++] = image->bitmap[(j*image->width) + i].blue & 1;
            }       
                
        }
    //  if (h < bit_array_size)
    //      i=0;
    }

    //Transformo los bits a un numero int concreto
    int total=0;
    for ( k = 0; k < 32; k++){
        printf("%d",aux2[k]);
        if ( (aux2[k]%2) == 1){
            total += pow(2,(31-k));
        }
    }
    putchar(10);
    //Armo el array para contener el mensaje
    bit_array_size = total;
    printf("FINAL TAM:%d AND H:%d\n", total,h);
    char * aux = calloc (1,bit_array_size); 
    char * respuesta = calloc (1,bit_array_size);

    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;
    //Leo el mensaje en base al tamanio obtenido anteriormente
     for(; j<image->height && h<bit_array_size; j++ ) {
        for(; i<image->width && h<bit_array_size; i++) {
            if ( image->bitmap[(j*image->width) + i].red >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux[h++] = image->bitmap[(j*image->width) + i].red & 1;
            }
            if ( image->bitmap[(j*image->width) + i].green >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux[h++] = image->bitmap[(j*image->width) + i].green & 1;
            }   
            if ( image->bitmap[(j*image->width) + i].blue >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux[h++] = image->bitmap[(j*image->width) + i].blue & 1;
            }       
        }
        if (h < bit_array_size)
            i=0;
    }

    printf("H: %d\n",h);
    for ( k = 0; k < h; k++){
        printf("%d",aux[k]);
    }
    putchar(10);
    int var;
    for ( k = 0; k < h; k++){
        
        if ( (aux[k]%2) == 1){
            if(k<8){
                respuesta[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                respuesta[var] |= 1 << (7-(k%8));
            }
        }
    }

    //Parseo la extension
    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;

     for(; j<image->height && h<32; j++ ) {
        for(; i<image->width && h<32; i++) {
        //  printf("i: %d, j: %d - %d\n",i,j,image->bitmap[(j*image->width) + i].red);
            if ( image->bitmap[(j*image->width) + i].red >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux3[h++] = image->bitmap[(j*image->width) + i].red & 1;
            }
            if ( image->bitmap[(j*image->width) + i].green >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux3[h++] = image->bitmap[(j*image->width) + i].green & 1;
            }   
            if ( image->bitmap[(j*image->width) + i].blue >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                aux3[h++] = image->bitmap[(j*image->width) + i].blue & 1;
            }       
        }
        if (h < bit_array_size)
            i=0;
    }

    for ( k = 0; k < h; k++){
        printf("%d ", aux3[k]);
        if ( (aux3[k]%2) == 1){
            if(k<8){
                ans_extension[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                ans_extension[var] |= 1 << (7-(k%8));
            }
        }
    }
    


    printf("texto:%s\n", respuesta);
    printf("ext:%s\n", ans_extension);

    char example[100];
    strcpy (example,"respuesta");
    strcat (example,ans_extension);
    FILE * salida = fopen(example, "wb");
    FCHK(fwrite(respuesta, bit_array_size, 1, salida)); 


}

int decrypt_LSB4(BmpImage image){

    //Recupero el mensaje;
    int i,j,k,h, bit_array_size;
    h = 0;
    char * aux2 = calloc (1,64);
    char * aux3 = calloc (1,64);
    char * ans_extension = calloc(1,64);
    int * tamanio = calloc(1,sizeof(int));
    

    //Leo los primeros 32 para obtener el size;
     for( j=0; j<image->height && h<36; j++ ) {
        for( i=0; i<image->width && h<36; i++) {
            printf("valor:%d\n", image->bitmap[(j*image->width) + i].red);
            aux2[h++] = (image->bitmap[(j*image->width) + i].red & (char)8) >> 3;
            aux2[h++] = (image->bitmap[(j*image->width) + i].red & (char)4) >> 2;
            aux2[h++] = (image->bitmap[(j*image->width) + i].red & (char)2) >> 1;
            aux2[h++] = (image->bitmap[(j*image->width) + i].red & (char)1) >> 0;
            
            aux2[h++] = (image->bitmap[(j*image->width) + i].green & (char)8) >> 3;
            aux2[h++] = (image->bitmap[(j*image->width) + i].green & (char)4) >> 2;
            aux2[h++] = (image->bitmap[(j*image->width) + i].green & (char)2) >> 1;
            aux2[h++] = (image->bitmap[(j*image->width) + i].green & (char)1) >> 0;

            aux2[h++] = (image->bitmap[(j*image->width) + i].blue & (char)8) >> 3;
            aux2[h++] = (image->bitmap[(j*image->width) + i].blue & (char)4) >> 2;
            aux2[h++] = (image->bitmap[(j*image->width) + i].blue & (char)2) >> 1;
            aux2[h++] = (image->bitmap[(j*image->width) + i].blue & (char)1) >> 0;
        }
    }
    putchar(10);
    for ( k = 0; k < 32; k++){
        printf("%d", aux2[k]);
    }
    putchar(10);

    //Transformo los bits a un numero int concreto
    int total=0;
    for ( k = 0; k < 32; k++){
        if ( (aux2[k]%2) == 1){
            printf("imprime:%d\n",k);
            total += pow(2,(31-k));
        }
    }

    //Armo el array para contener el mensaje
    bit_array_size = total;
    printf("\nFINAL TAM:%d\n", total);
    char * aux = calloc (1,bit_array_size); 
    char * respuesta = calloc (1,bit_array_size);

    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;

    //Leo el mensaje en base al tamanio obtenido anteriormente
     for(; j<image->height && h<bit_array_size; j++ ) {
        for(; i<image->width && h<bit_array_size; i++) {
            aux[h++] = (image->bitmap[(j*image->width) + i].red & (char)8) >> 3;
            aux[h++] = (image->bitmap[(j*image->width) + i].red & (char)4) >> 2;
            aux[h++] = (image->bitmap[(j*image->width) + i].red & (char)2) >> 1;
            aux[h++] = (image->bitmap[(j*image->width) + i].red & (char)1) >> 0;
            
            aux[h++] = (image->bitmap[(j*image->width) + i].green & (char)8) >> 3;
            aux[h++] = (image->bitmap[(j*image->width) + i].green & (char)4) >> 2;
            aux[h++] = (image->bitmap[(j*image->width) + i].green & (char)2) >> 1;
            aux[h++] = (image->bitmap[(j*image->width) + i].green & (char)1) >> 0;

            aux[h++] = (image->bitmap[(j*image->width) + i].blue & (char)8) >> 3;
            aux[h++] = (image->bitmap[(j*image->width) + i].blue & (char)4) >> 2;
            aux[h++] = (image->bitmap[(j*image->width) + i].blue & (char)2) >> 1;
            aux[h++] = (image->bitmap[(j*image->width) + i].blue & (char)1) >> 0;
        }
        if (h < bit_array_size)
            i=0;
    }

    printf("H: %d\n",h);
    for ( k = 0; k < h; k++){
        printf("%d",aux[k]);
    }
    putchar(10);

    for ( k = 0; k < h; k++){
        if ( (aux[k]%2) == 1){
            if(k<8){
                respuesta[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                respuesta[var] |= 1 << (7-(k%8));
            }
        }
    }

    //Parseo la extension
    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;

     for(; j<image->height && h<32; j++ ) {
        for(; i<image->width && h<32; i++) {
        //  printf("i: %d, j: %d - %d\n",i,j,image->bitmap[(j*image->width) + i].red);
            aux3[h++] = (image->bitmap[(j*image->width) + i].red & (char)8) >> 3;
            aux3[h++] = (image->bitmap[(j*image->width) + i].red & (char)4) >> 2;
            aux3[h++] = (image->bitmap[(j*image->width) + i].red & (char)2) >> 1;
            aux3[h++] = (image->bitmap[(j*image->width) + i].red & (char)1) >> 0;
            
            aux3[h++] = (image->bitmap[(j*image->width) + i].green & (char)8) >> 3;
            aux3[h++] = (image->bitmap[(j*image->width) + i].green & (char)4) >> 2;
            aux3[h++] = (image->bitmap[(j*image->width) + i].green & (char)2) >> 1;
            aux3[h++] = (image->bitmap[(j*image->width) + i].green & (char)1) >> 0;

            aux3[h++] = (image->bitmap[(j*image->width) + i].blue & (char)8) >> 3;
            aux3[h++] = (image->bitmap[(j*image->width) + i].blue & (char)4) >> 2;
            aux3[h++] = (image->bitmap[(j*image->width) + i].blue & (char)2) >> 1;
            aux3[h++] = (image->bitmap[(j*image->width) + i].blue & (char)1) >> 0;
        }
        if (h < bit_array_size)
            i=0;

    }

    for ( k = 0; k < h; k++){
        if ( (aux3[k]%2) == 1){
            if(k<8){
                ans_extension[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                ans_extension[var] |= 1 << (7-(k%8));
            }
        }
    }
    


    printf("texto:%s\n", respuesta);
    printf("ext:%s\n", ans_extension);

    char example[100];
    strcpy (example,"respuesta");
    strcat (example,ans_extension);
    FILE * salida = fopen(example, "wb");
    FCHK(fwrite(respuesta, bit_array_size, 1, salida)); 

}

int
decrypt_LSB1(BmpImage image){

    //Recupero el mensaje;
    int i,j,k,h, bit_array_size;
    h = 0;
    char * aux2 = calloc (1,32);
    char * aux3 = calloc (1,64);
    char * ans_extension = calloc(1,64);
    int * tamanio = calloc(1,sizeof(int));
    

    //Leo los primeros 32 para obtener el size;
     for( j=0; j<image->height && h<32; j++ ) {
        for( i=0; i<image->width && h<32; i++) {
            aux2[h++] = image->bitmap[(j*image->width) + i].red & 1;
            aux2[h++] = image->bitmap[(j*image->width) + i].green & 1;
            aux2[h++] = image->bitmap[(j*image->width) + i].blue & 1;
        }
        if (h < bit_array_size)
            i=0;
    }

    //Transformo los bits a un numero int concreto
    int total=0;
    for ( k = 0; k < 32; k++){
        if ( (aux2[k]%2) == 1){
            total += pow(2,(31-k));
        }
    }

    //Armo el array para contener el mensaje
    bit_array_size = total;
    printf("FINAL TAM:%d", total);
    char * aux = calloc (1,bit_array_size); 
    char * respuesta = calloc (1,bit_array_size);

    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;

    //Leo el mensaje en base al tamanio obtenido anteriormente
     for(; j<image->height && h<bit_array_size; j++ ) {
        for(; i<image->width && h<bit_array_size; i++) {
            //printf("i: %d, j: %d - %d\n",i,j,image->bitmap[(j*image->width) + i].red);
            aux[h++] = image->bitmap[(j*image->width) + i].red & 1;
            aux[h++] = image->bitmap[(j*image->width) + i].green & 1;
            aux[h++] = image->bitmap[(j*image->width) + i].blue & 1;
        }
        if (h < bit_array_size)
            i=0;
    }

    printf("H: %d\n",h);
    for ( k = 0; k < h; k++){
        printf("%d",aux[k]);
    }

    for ( k = 0; k < h; k++){
        if ( (aux[k]%2) == 1){
            if(k<8){
                respuesta[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                respuesta[var] |= 1 << (7-(k%8));
            }
        }
    }

    //Parseo la extension
    //Empiezo de 0 y hago una correcion de un incremento mal asignado en el anterior bucle
    h=0;
    j--;

     for(; j<image->height && h<32; j++ ) {
        for(; i<image->width && h<32; i++) {
        //  printf("i: %d, j: %d - %d\n",i,j,image->bitmap[(j*image->width) + i].red);
            aux3[h++] = image->bitmap[(j*image->width) + i].red & 1;
            aux3[h++] = image->bitmap[(j*image->width) + i].green & 1;
            aux3[h++] = image->bitmap[(j*image->width) + i].blue & 1;
        }
        if (h < bit_array_size)
            i=0;
    }

    for ( k = 0; k < h; k++){
        if ( (aux3[k]%2) == 1){
            if(k<8){
                ans_extension[0] |= 1 << (7-(k%8));
            }else{
                int var = k/8;
                ans_extension[var] |= 1 << (7-(k%8));
            }
        }
    }
    


    printf("texto:%s\n", respuesta);
    printf("ext:%s\n", ans_extension);

    char example[100];
    strcpy (example,"respuesta");
    strcat (example,ans_extension);
    FILE * salida = fopen(example, "wb");
    FCHK(fwrite(respuesta, bit_array_size, 1, salida)); 

}