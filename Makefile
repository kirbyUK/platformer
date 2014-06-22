CC=g++
FLAGS=-Wall -c
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
DESTDIR=/usr/local
SRC=src
PDIR=$(SRC)/player
BDIR=$(SRC)/block
MDIR=$(SRC)/movement
BIN=platformer

all: $(BIN)

#$(BIN): main.o player.o block.o staticBlock.o dynamicBlock.o movementType.o
#	$(CC) $(LIBS) 	main.o player.o block.o staticBlock.o dynamicBlock.o 
#					movementType.o \
#					-o $(BIN)
$(BIN): main.o player.o block.o staticBlock.o dynamicBlock.o
	$(CC) $(LIBS) 	main.o player.o block.o staticBlock.o dynamicBlock.o \
					-o $(BIN)

# ./src/ -------------------------------------

main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) $(SRC)/main.cpp

# ./src/player/ ------------------------------

player.o: $(PDIR)/player.cpp $(PDIR)/player.h
	$(CC) $(FLAGS) $(PDIR)/player.cpp 

# ./src/block/ -------------------------------

block.o: $(BDIR)/block.cpp $(BDIR)/block.h
	$(CC) $(FLAGS) $(BDIR)/block.cpp

staticBlock.o: $(BDIR)/staticBlock.cpp $(BDIR)/staticBlock.h
	$(CC) $(FLAGS) $(BDIR)/staticBlock.cpp

dynamicBlock.o: $(BDIR)/dynamicBlock.cpp $(BDIR)/dynamicBlock.h
	$(CC) $(FLAGS) $(BDIR)/dynamicBlock.cpp

# ./src/movement -----------------------------

#movementType.o: $(MDIR)/movementType.cpp $(MDIR)/movementType.h
#	$(CC) $(FLAGS) $(MDIR)/movementType.cpp

# --------------------------------------------

deinstall: uninstall
uninstall:
	rm $(DESTDIR)/bin/$(BIN)

install:
	install -m 0755 $(BIN) $(DESTDIR)/bin/

clean:
	rm *.o
	rm $(BIN)
