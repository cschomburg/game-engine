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
		 Color.o\
		 Entity.o\
		 GameEngine.o\
		 GameObject.o\
		 Level.o\
		 Player.o\
		 Rect.o\
		 Resource.o\
		 ResourceManager.o\
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
