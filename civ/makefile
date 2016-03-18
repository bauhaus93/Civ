
CC      = gcc
CFLAGS  = -std=c++14 -pedantic -Wall
LDFLAGS = -Wall
SDLHEADER = sdl\SDL.h

OBJ = Game.o Map.o FPSHandler.o  CivExceptions.o SDLManager.o Common.o SpriteFactory.o Sprite.o
DEP = $(OBJ:.o=.d)
BIN = civ.exe

all: $(OBJ)
    $(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

-include $(DEP)

%.o: %.c
    $(CC) -MD $(CFLAGS) -c $*.c -o $*.o
#    $(CC) -MM $(CFLAGS) $*.c > $*.d

.PHONEY: clean
    rm -f $(BIN) *.o *.d