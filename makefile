IDIR=includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=-lm -lcrypto

_DEPS= cmdline.h decrypt.h encrypt.h imageutils.h defines.h
DEPS=$(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ= main.o cmdline.o decrypt.o encrypt.o imageutils.o
OBJ=$(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:	%.c $(DEPS)
				$(CC) -c -o $@ $< $(CFLAGS)

stegobmp:	$(OBJ)
			$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

%.o:		%.c $(DEPS) $(CC) -c -o $@ $< $(LIBS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR) /*~