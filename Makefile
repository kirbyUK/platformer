CC=g++
FLAGS=-Wall -c
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
DESTDIR=/usr/local
BIN=platformer

all: $(BIN)

$(BIN): player.o
	$(CC) $(LIBS) player.o -o $(BIN)

player.o: player.cpp player.h
	$(CC) $(FLAGS) player.cpp 

deinstall: uninstall
uninstall:
	rm $(DESTDIR)/bin/$(BIN)

install:
	install -m 0755 $(BIN) $(DESTDIR)/bin/

clean:
	rm *.o
	rm $(BIN)
