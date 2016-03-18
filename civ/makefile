CC = g++
CFLAGS = -std=c++14 -Wall
LDFLAGS = -Wall -lSDL2
SDLHEADER = SDL/SDL.h

OBJ = Main.o Game.o Map.o FPSHandler.o  CivExceptions.o SDLManager.o Common.o SpriteFactory.o Sprite.o
DEP = $(OBJ:.o=.d)
BIN = civ

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

-include $(DEP)

%.o: %.cpp
	$(CC) $(CFLAGS) -MD -c $*.cpp -o $*.o
#    $(CC) -MM $(CFLAGS) $*.c > $*.d

.PHONY: clean
clean:
	 rm -f $(BIN) *.o *.d
