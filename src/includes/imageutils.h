#ifndef _IMAGEUTILS_H_
#define _IMAGEUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "cmdline.h"
#define LOADING_OK 0

typedef struct
{   
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Rgb;

struct bmp_image {
    char *filename;
    int width;
    int height;
    short pixel_bits;
    int image_size;

    int header_size;

    unsigned char *header;
    Rgb * bitmap;
};

typedef struct bmp_image * BmpImage;
void printUserArguments(struct gengetopt_args_info *args_info);


BmpImage create_bmp_image(char * filename);
int load_bmp_image(BmpImage im);
int save_bmp_image(BmpImage im, char * filename);
void free_bmp_image(struct bmp_image* im);
BmpImage duplicate(BmpImage im, char * filename);
void print_bmp_image(BmpImage im);
void print_bmp_bitmap(BmpImage im);

#endif