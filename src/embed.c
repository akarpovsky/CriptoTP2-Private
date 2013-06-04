#include "includes/defines.h"
#include "includes/embed.h"

void
encrypt_LSBE(BmpImage image, char * bit_array, int bit_array_size){

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
    }
}

void
encrypt_LSB4(BmpImage image, char * bit_array, int bit_array_size){
    int amount_pixels = bit_array_size/RGB_LSB4 + bit_array_size%RGB_LSB4;
    int i,j,h;
    h=0;
    putchar(10);
    for( j=0; j<image->height && h<bit_array_size; j++ ) {
        for( i=0; i<image->width && h<bit_array_size; i++) {
            
            if ( (int)(bit_array[h++]-'0') == 0){
        
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & (char)(255-8);
            }else{
            
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (char)8;
            }
        
            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & (char)(255-4);
            }else{
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (char)(4);
            }
            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & (char)(255-2);
            }else{
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (char)(2);
            }
            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & (char)(255-1);
            }else{
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (char)(1);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (char)(255-8);
            }else{
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (char)(8);
            }
            
            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (char)(255-4);
            }else{
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (char)(4);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (char)(255-2);
            }else{
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (char)(2);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (char)(255-1);
            }else{
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (char)(1);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (char)(255-8);
            }else{
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (char)(8);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (char)(255-4);
            }else{
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (char)(4);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (char)(255-2);
            }else{
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (char)(2);
            }

            if ( (int)(bit_array[h++]-'0') == 0){
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (char)(255-1);
            }else{
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (char)(1);
            }
            
        }
    }
}

void
encrypt_LSB1(BmpImage image, char * bit_array, int bit_array_size){

    int amount_pixels = bit_array_size/RGB + bit_array_size%RGB;
    int i,j,h;
    h=0;
 
    for( j=0; j<image->height && h<bit_array_size; j++ ) {
        for( i=0; i<image->width && h<bit_array_size; i++) {
            
            if ( (int)(bit_array[h]-'0') == 0)
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red & (int)(bit_array[h++]-'0');
            else
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | (int)(bit_array[h++]-'0');
            if ( (int)(bit_array[h]-'0') == 0)
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (int)(bit_array[h++]-'0');
            else
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | (int)(bit_array[h++]-'0');
            
            if ( (int)(bit_array[h]-'0') == 0)
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (int)(bit_array[h++]-'0');
            else
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | (int)(bit_array[h++]-'0');
            
        }
    }

}
