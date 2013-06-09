#include "includes/defines.h"
#include "includes/embed.h"

#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))

void
encrypt_LSBE(BmpImage image, char * bit_array, int bit_array_size){

    int i,j,h;
    char * image_array = image->data;
    j=0;
    for(i=0;(i<image->image_size) && (j< bit_array_size);i++){
        printf("image:%d\n",image_array[i]==(char)0xFF || image_array[i]==(char)0xFE);
        if ( image_array[i]==(char)0xFF || image_array[i]==(char)0xFE){
                 if ((image_array[i]%2) == 0){
                    if ( bit_array[j]%2 == 1){
                        image_array[i] += 1;
                    }
                }else{
                    if ( bit_array[j]%2 == 0){
                        image_array[i] -= 1;
                    }
                }
                j++;
        }
    }
    printf("I:%d\n",i);
   if (!(i < image->image_size)){
        printf("Error de tamaño. Ingrese una imagen mas grande y vuelva a intenetar");
        exit(0);
    }



/*
    int amount_pixels = bit_array_size/RGB + bit_array_size%RGB;
    int i,j,h;
    int ocultar = FALSE;
    
    h=0;
    for( j=0; j<image->height && h<bit_array_size; j++ ) {
        for( i=0; i<image->width && h<bit_array_size; i++) {

            if ( image->bitmap[(j*image->width) + i].red >= 254 || ocultar != FALSE){
                if ( ocultar == 0 ){
                    ocultar = TRUE; 
                }
                ocultar--;      
                if ( (int)(bit_array[h]-'0') == 0)
                    image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & 254;
                else
                    image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (int)(bit_array[h]-'0');
                h++;
            
            }
            
            if ( image->bitmap[(j*image->width) + i].green >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
                ocultar--;
                if ( (int)(bit_array[h]-'0') == 0)
                    image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & 254;
                else
                    image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (int)(bit_array[h]-'0');
                h++;
            }
            
            if ( image->bitmap[(j*image->width) + i].blue >= 254 || ocultar != FALSE){
                if ( ocultar == FALSE ){
                    ocultar = TRUE; 
                }
            
                ocultar--;
                if ( (int)(bit_array[h]-'0') == 0)
                    image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & 254;
                else
                    image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (int)(bit_array[h]-'0');
                h++;
            }

        }
    }*/
}

void
encrypt_LSB4(BmpImage image, char * bit_array, int bit_array_size){
    int i,j;
    char * image_array = image->data;
    j=0;
    for(i=0;i<bit_array_size;){

        if ((bit_array[i++]%2) == 0){
            printf("0");
            image_array[j] = image_array[j] & (char)(255-8);
        }else{
            printf("1");
            image_array[j] = image_array[j] | (char)(8);
        }
        if ((bit_array[i++]%2) == 0){
            printf("0");
            image_array[j] = image_array[j] & (char)(255-4);
        }else{
            printf("1");
              image_array[j] = image_array[j] | (char)(4);
        }
        if ((bit_array[i++]%2) == 0){
            printf("0");
            image_array[j] = image_array[j] & (char)(255-2);
        }else{
            printf("1");
              image_array[j] = image_array[j] | (char)(2);
        }
        if ((bit_array[i++]%2) == 0){
            printf("0");
            image_array[j] = image_array[j] & (char)(255-1);
        }else{
            printf("1");
              image_array[j] = image_array[j] | (char)(1);
        }
        j++;
    }
}

void
encrypt_LSB1(BmpImage image, char * bit_array, int bit_array_size){
   
    int i;
    char * image_array = image->data;
   // printf("ENTRE\n");
    for(i=0;i<bit_array_size;i++){
        if ((image_array[i]%2) == 0){
            if ( bit_array[i]%2 == 1){
                image_array[i] += 1;
            }
        }else{
            if ( bit_array[i]%2 == 0){
                image_array[i] -= 1;
            }
        }
    }
}
