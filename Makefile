IDIR=include
CC=g++
CFLAGS=-g -I$(IDIR)
LIBS=-lyaml-cpp -lSDLmain -lSDL_image -lSDL -lGL

ODIR=obj
SDIR=src
_OBJ=main.o\
		 Application.o\
		 BaseEngine.o\
		 Camera.o\
		 Event.o\
		 GameEngine.o\
		 Level.o\
		 Positionable.o\
		 Primitives.o\
		 Texture.o\
		 YamlLoader.o\
		 Vector2.o\

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -r $(ODIR)/*.o *~ core $(IDIR)/*~
