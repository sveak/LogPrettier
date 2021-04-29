######################################################################
# @author      : roman (vrv@sveak.com)
# @file        : makefile
# @created     : 29, 2021 12:09:04 +07
######################################################################

IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=

_OBJ = main.o nxjson.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o

