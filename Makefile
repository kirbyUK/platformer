CC=g++
FLAGS=-Wall -c
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
DESTDIR=/usr/local
BIN=platformer

all: $(BIN)

$(BIN): main.o player.o block.o staticBlock.o
	$(CC) $(LIBS) main.o player.o block.o staticBlock.o \
				  -o $(BIN)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

player.o: player.cpp player.h
	$(CC) $(FLAGS) player.cpp 

block.o: block.cpp block.h
	$(CC) $(FLAGS) block.cpp

staticBlock.o: staticBlock.cpp staticBlock.h
	$(CC) $(FLAGS) staticBlock.cpp

deinstall: uninstall
uninstall:
	rm $(DESTDIR)/bin/$(BIN)

install:
	install -m 0755 $(BIN) $(DESTDIR)/bin/

clean:
	rm *.o
	rm $(BIN)
