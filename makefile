IDIR=includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=-lm -lcrypto

_DEPS= cmdline.h embed.h extract.h imageutils.h defines.h encrypt.h
DEPS=$(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ= main.o cmdline.o embed.o extract.o imageutils.o encrypt.o
OBJ=$(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:	%.c $(DEPS)
				$(CC) -c -o $@ $< $(CFLAGS)

stegobmp:	$(OBJ)
			$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

%.o:		%.c $(DEPS) $(CC) -c -o $@ $< $(LIBS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR) /*~
	rm -fr $(ODIR)
	mkdir obj

