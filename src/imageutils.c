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

    fseek(fp, im->header_size, SEEK_SET);
    im->data = calloc(im->image_size,sizeof(char));
    FCHK(fread(im->data, im->image_size, 1, fp));

    fclose(fp);
    return LOADING_OK;
}

int 
extract_bmp_image(BmpImage im, char * out_filename,int mode, char* algorithm, char* encrypt_mode, char* password)
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

    fseek(fp, im->header_size, SEEK_SET);
    
    if ( mode == LSB1 ){
        printf("LSB1\n");
            decrypt_LSB1(im, out_filename, fp,algorithm,encrypt_mode,password);
    }else if ( mode == LSB4 ){
            printf("LSB4\n");
            decrypt_LSB4(im, out_filename, fp, algorithm,encrypt_mode,password);
    }else{
        printf("LSBE\n");
            decrypt_LSBE(im, out_filename, fp, algorithm,encrypt_mode,password);
    }

    fclose(fp);
    return LOADING_OK;
}

int
save_bmp_image(BmpImage im, char * filename) 
{
    char filepath[100];
    char *target = "./target/";
    strcpy (filepath, target);
    strcat (filepath, filename);

    FILE *fp;
    fp = fopen(filepath, "wb");
    int i,j;
    if(fp != NULL) {
        fseek(fp, 0x00, SEEK_SET);
        FCHK(fwrite(im->header, im->header_size, 1, fp));
        FCHK(fwrite(im->data, im->image_size, 1, fp));
      /*  for( j=0; j<im->height; j++ ) {
            for( i=0; i<im->width; i++ ) {
              //  FCHK(fwrite(&(im->bitmap[(j*im->width) + i]), sizeof(Rgb), 1, fp));
            }
    }*/

        fclose(fp);
        return true;
    }
    return false;
}

void

free_bmp_image(struct bmp_image* im)
{
    free(im->header);
   // free(im->size);
    free(im->data);
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
 //   ret->bitmap = malloc(im->image_size);
    memcpy(ret->header, im->header, im->header_size);
   // memcpy(ret->bitmap, im->bitmap, im->image_size);

    return ret;
}

void 
print_bmp_image(BmpImage im) {
    printf("\n*************** IMAGE DATA ***************\n");
    printf("\tFilename: %s\n", im->filename);
    printf("\tWidth: %d\n", im->width);
    printf("\tHeight: %d\n", im->height);
    printf("\tPixel_bits: %d\n", im->pixel_bits);
    printf("\tSize: %d\n", im->image_size);
    printf("\tHeader size: %d\n", im->header_size);
    printf("******************************************\n\n");
}

void
print_bmp_bitmap(BmpImage im){
    int i,j;
    for( j=0; j<im->height; j++ ) {
        printf( "------ Row %d\n", j+1 );
        for( i=0; i<im->width; i++ ) {
          //  printf( "Pixel %d: %3d %3d %3d\n", i+1, im->bitmap[(j*im->width) + i].red, im->bitmap[(j*im->width) + i].green, im->bitmap[(j*im->width) + i].blue );
        }
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
