#include "includes/defines.h"
#include "includes/encrypt.h"

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

StegoFileT *
readStegoFile(const char * sfilename)
{
    StegoFileT * sfiledata;
    FILE * stegoFile;
    char * extension;
    int fsize;

    if ( (stegoFile = fopen(sfilename, "r")) == NULL)
    {
        return NULL;
    }

    if ( (sfiledata = calloc(1, sizeof(StegoFileT))) == NULL)
    {
        fclose(stegoFile);
        return NULL;
    }


    // Reads file size
    fseek(stegoFile, 0L, SEEK_END);
    fsize = ftell(stegoFile);
    fseek(stegoFile, 0L, SEEK_SET);

    if ( (sfiledata -> fileContents = calloc(1, fsize)) == NULL)
    {
        fprintf(stderr,"Out of memory when reading %s\n", sfilename);
        fclose(stegoFile);
        free(sfiledata);
        return NULL;
    }

    // assign filesize, reads in data from file and sets file extension
    sfiledata -> fileSize = fsize;
    fread(sfiledata -> fileContents, fsize,1,stegoFile);

    // checks for file read error
    if (ferror(stegoFile) > 0)
    {
        free(sfiledata);
        fclose(stegoFile);
        return NULL;
    }

    extension = strstr(sfilename, ".");

    if ((sfiledata -> extension = calloc(1, sizeof(char) * strlen(extension) + 1)) == NULL)
    {
        free(sfiledata);
        fclose(stegoFile);
        return NULL;
    }

    strncpy(sfiledata -> extension, extension, strlen(extension));

    fclose(stegoFile);
    return sfiledata;
}

void freeStegoFile(StegoFileT * sfile)
{
    free(sfile -> extension);
    free(sfile -> fileContents);
    free(sfile);
    return;
}