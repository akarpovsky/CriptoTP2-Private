#include "includes/defines.h"
#include "includes/embed.h"

void
encrypt_LSBE(BmpImage image, char * bit_array, int bit_array_size){

    int i,j,h;
    char * image_array = image->data;
    j=0;
    for(i=0;(i<image->image_size) && (j< bit_array_size);i++){
        if ( image_array[i]==(char)255 || image_array[i]==(char)254){
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

   if (!(i < image->image_size)){
        printf("Error de tamaño. Ingrese una imagen mas grande y vuelva a intenetar");
        exit(0);
    }
}

void
encrypt_LSB4(BmpImage image, char * bit_array, int bit_array_size){
    int i,j;
    char * image_array = image->data;
    j=0;
    for(i=0;i<bit_array_size;){

        if ((bit_array[i++]%2) == 0){
            image_array[j] = image_array[j] & (char)(255-8);
        }else{
            image_array[j] = image_array[j] | (char)(8);
        }
        if ((bit_array[i++]%2) == 0){
            image_array[j] = image_array[j] & (char)(255-4);
        }else{
              image_array[j] = image_array[j] | (char)(4);
        }
        if ((bit_array[i++]%2) == 0){
            image_array[j] = image_array[j] & (char)(255-2);
        }else{
              image_array[j] = image_array[j] | (char)(2);
        }
        if ((bit_array[i++]%2) == 0){
            image_array[j] = image_array[j] & (char)(255-1);
        }else{
              image_array[j] = image_array[j] | (char)(1);
        }
        j++;
    }
}

void
encrypt_LSB1(BmpImage image, char * bit_array, int bit_array_size){
   
    int i;
    char * image_array = image->data;
  
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
