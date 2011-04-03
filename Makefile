IDIR=include
CC=g++
CFLAGS=-g -I$(IDIR)
LIBS=-lyaml-cpp -lSDLmain -lSDL_image -lSDL -lGL

ODIR=obj
SDIR=src
_OBJ=main.o\
		 Application.o\
		 BaseEngine.o\
		 Event.o\
		 GameEngine.o\
		 Level.o\
		 Texture.o\
		 YamlLoader.o\
		 Primitives.o\

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o *~ core $(IDIR)/*~
