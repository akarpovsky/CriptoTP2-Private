#ifndef _DEFINES_H_
#define _DEFINES_H_

#define THROW_FILE_ERROR return 1
#define FCHK(x) if((x) != 1) {THROW_FILE_ERROR;}
#define ERRORMSG(x) fprintf(stderr, x); return EXIT_FAILURE;

#define ENCRIPT 1
#define DECRIPT 0
#define LSB1 1
#define LSB4 2
#define LSBE 8
#define LSB_bit_array 4
#define SIZE 100
#define CHAR_BITS 8
#define RGB 3
#define RGB_LSB4 12
#define TRUE 8
#define FALSE 0
#define AES 1
#define DES 2
#define NO_ENCRYPTION 0
#define CBC 0
#define OFB 1	
#define ECB 2
#define CBF 3

#endif
