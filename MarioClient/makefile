FILES=src/main.c src/GameState.c src/MainState.c src/JeuState.c src/Mario.c src/Enemy.c
LIBSW=$(shell sdl-config --libs)
LIBSU=-lSDLmain -lSDL -lSDL_image
OPTS= $(shell sdl-config --cflags)
OUTPUT=SMB

all:
	gcc $(OPTS) $(FILES)  $(LIBSW) -o $(OUTPUT)

unix:
	gcc $(OPTS) $(FILES) $(LIBSU) -o $(OUTPUT)
