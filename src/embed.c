#include "includes/defines.h"
#include "includes/embed.h"

#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))

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
   /* int k;
    putchar(10);
    putchar(10);
    for( k = 0; k<bit_array_size;k++){
                printf("%c", bit_array[k]);
                if(bit_array[k] == '0')
                    printf("<-CERO");
    }
    putchar(10);

    printf("VALOR:%c", (unsigned char) 254);*/
    int amount_pixels = bit_array_size/RGB + bit_array_size%RGB;
    int i,j,h;
    h=0;
    for( j=0; j<image->height && h<bit_array_size; j++ ) {
        for( i=0; i<image->width && h<bit_array_size; i++) {
            //printf("BITA - %d\n",(int)(bit_array[h]-'0'));
     //       printf("i: %d, j: %d - %d - %c\n",i,j,image->bitmap[(j*image->width) + i].red, bit_array[h]);
            if ( bit_array[h++] == '0' )
                image->bitmap[(j*image->width) + i].red = CLR_BIT(image->bitmap[(j*image->width) + i].red,0);
            else
                image->bitmap[(j*image->width) + i].red = image->bitmap[(j*image->width) + i].red | 1;
       //     printf("i: %d, j: %d - %d - %c\n",i,j,image->bitmap[(j*image->width) + i].red,bit_array[h]);
            if ( bit_array[h++] == '0' )
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green & (unsigned char)254;
            else
                image->bitmap[(j*image->width) + i].green = image->bitmap[(j*image->width) + i].green | 1;
            
            if ( bit_array[h++] == '0' )
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue & (unsigned char)254;
            else
                image->bitmap[(j*image->width) + i].blue = image->bitmap[(j*image->width) + i].blue | 1;
            
        }
    }

}
