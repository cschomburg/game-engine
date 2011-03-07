IDIR=src
CC=g++
CFLAGS=-g -I$(IDIR)
LIBS=-lyaml-cpp -lSDLmain -lSDL_image -lSDL

ODIR=obj
SDIR=src
_OBJ=main.o\
		 Application.o\
		 BaseEngine.o\
		 Event.o\

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o *~ core $(IDIR)/*~
