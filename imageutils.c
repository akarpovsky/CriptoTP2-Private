#include "includes/defines.h"
#include "includes/imageutils.h"

BmpImage
create_bmp_image(char * filename)
{
    BmpImage ret = malloc(sizeof(struct bmp_image));
    ret->filename = malloc(strlen(filename) + 1);
    strcpy(ret->filename, filename);
    return ret;
}

int 
load_bmp_image(BmpImage im)
{
    FILE *fp;
    int array_offset;

    fp = fopen(im->filename, "rb");

    if(fp == NULL) {
        THROW_FILE_ERROR;
    }

    fseek(fp, 10, SEEK_SET);
    FCHK(fread(&array_offset, 4, 1, fp));

    /*Se copia el header entero para guardarlo como estaba*/
    im->header_size = array_offset;
    im->header = malloc(im->header_size);
    fseek(fp, 0x00, SEEK_SET);
    FCHK(fread(im->header, im->header_size, 1, fp));

    fseek(fp, 0x12, SEEK_SET);
    FCHK(fread(&(im->width), sizeof(im->width), 1, fp));

    fseek(fp, 0x16, SEEK_SET);
    FCHK(fread(&(im->height), sizeof(im->height), 1, fp));

    fseek(fp, 0x1C, SEEK_SET);
    FCHK(fread(&(im->pixel_bits), sizeof(im->pixel_bits), 1, fp));

    fseek(fp, 0x22, SEEK_SET);
    FCHK(fread(&(im->image_size), sizeof(im->image_size), 1, fp));

    im->bitmap = malloc(im->image_size * sizeof(Rgb));
    fseek(fp, im->header_size, SEEK_SET);

//  FCHK(fread(im->bitmap, im->image_size, 1, fp));

    Rgb *pixel = (Rgb*) malloc( sizeof(Rgb) );
    int read, i,j;
    for( j=0; j<im->height; j++ ) {
    //  printf( "------ Row %d\n", j+1 );
        read = 0;
        for( i=0; i<im->width; i++ ) {
            if( fread(pixel, 1, sizeof(Rgb), fp) != sizeof(Rgb) ) {
                printf( "Error reading pixel!\n" );
                return -1;
            }
            read += sizeof(Rgb);
            im->bitmap[(j*im->width) + i].red = pixel->red;
            im->bitmap[(j*im->width) + i].green = pixel->green;
            im->bitmap[(j*im->width) + i].blue = pixel->blue;
        }
        if( read % 4 != 0 ) {
            read = 4 - (read%4);
            printf( "Padding: %d bytes\n", read );
            fread( pixel, read, 1, fp );
        }
    }

    fclose(fp);
    return LOADING_OK;
}

int
save_bmp_image(BmpImage im, char * filename) 
{
    FILE *fp;
    fp = fopen(filename, "wb");
    int i,j;
    if(fp != NULL) {
        fseek(fp, 0x00, SEEK_SET);
        FCHK(fwrite(im->header, im->header_size, 1, fp));
    //  FCHK(fwrite(im->bitmap, im->image_size, 1, fp));
        for( j=0; j<im->height; j++ ) {
            for( i=0; i<im->width; i++ ) {
                FCHK(fwrite(&(im->bitmap[(j*im->width) + i]), sizeof(Rgb), 1, fp));
            }
    }

        fclose(fp);
        return true;
    }
    return false;
}

void
free_bmp_image(struct bmp_image* im)
{
    free(im->header);
    free(im->bitmap);
}

BmpImage 
duplicate(BmpImage im, char * filename) {
    BmpImage ret = malloc(sizeof(struct bmp_image));

    ret->filename = filename;
    ret->width = im->width;
    ret->height = im->height;
    ret->pixel_bits = im->pixel_bits;
    ret->image_size = im->image_size;
    ret->header_size = im->header_size;
    ret->header = malloc(im->header_size);
    ret->bitmap = malloc(im->image_size);
    memcpy(ret->header, im->header, im->header_size);
    memcpy(ret->bitmap, im->bitmap, im->image_size);

    return ret;
}

void 
print_bmp_image(BmpImage im) {
    printf("Width: %d\n", im->width);
    printf("Height: %d\n", im->height);
    printf("Pixel_bits: %d\n", im->pixel_bits);
    printf("Size: %d\n", im->image_size);
    printf("Header size: %d\n", im->header_size);
}

void
print_bmp_bitmap(BmpImage im){
    int i,j;
    for( j=0; j<im->height; j++ ) {
        printf( "------ Row %d\n", j+1 );
        for( i=0; i<im->width; i++ ) {
            printf( "Pixel %d: %3d %3d %3d\n", i+1, im->bitmap[(j*im->width) + i].red, im->bitmap[(j*im->width) + i].green, im->bitmap[(j*im->width) + i].blue );
        }
    }
}