CC = g++
CFLAGS = -std=c++14 -Wall
LDFLAGS = -Wall -lSDL2
SDLHEADER = SDL/SDL.h

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
BIN = civ

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

exec: $(BIN)
	./$(BIN)

-include $(DEP)

%.o: %.cpp
	$(CC) $(CFLAGS) -MD -c $*.cpp -o $*.o

.PHONY: clean
clean:
	 rm -f $(BIN) *.o *.d
