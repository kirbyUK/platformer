CC=g++
FLAGS=-Wall -c -g
LIBS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
DESTDIR=/usr/local
SRC=src
PDIR=$(SRC)/player
BDIR=$(SRC)/block
MDIR=$(SRC)/movement
SDIR=$(SRC)/sound
IDIR=$(SRC)/interface
LDIR=$(SRC)/layout
BIN=platformer
OBJS=main.o player.o block.o staticBlock.o dynamicBlock.o deathBlock.o \
	 movementType.o upDown.o leftRight.o square.o sfx.o screens.o text.o \
	 arrow.o layout.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -g $(OBJS) -o $(BIN) $(LIBS)

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

deathBlock.o: $(BDIR)/deathBlock.cpp $(BDIR)/deathBlock.h
	$(CC) $(FLAGS) $(BDIR)/deathBlock.cpp

# ./src/movement -----------------------------

movementType.o: $(MDIR)/movementType.cpp $(MDIR)/movementType.h
	$(CC) $(FLAGS) $(MDIR)/movementType.cpp

upDown.o: $(MDIR)/upDown.cpp $(MDIR)/upDown.h
	$(CC) $(FLAGS) $(MDIR)/upDown.cpp

leftRight.o: $(MDIR)/leftRight.cpp $(MDIR)/leftRight.h
	$(CC) $(FLAGS) $(MDIR)/leftRight.cpp

square.o: $(MDIR)/square.cpp $(MDIR)/square.h
	$(CC) $(FLAGS) $(MDIR)/square.cpp

# ./src/sound --------------------------------

sfx.o: $(SDIR)/sfx.cpp $(SDIR)/sfx.h
	$(CC) $(FLAGS) $(SDIR)/sfx.cpp

# ./src/interface ----------------------------

screens.o: $(IDIR)/screens.cpp $(IDIR)/screens.h
	$(CC) $(FLAGS) $(IDIR)/screens.cpp

text.o: $(IDIR)/text.cpp $(IDIR)/text.h
	$(CC) $(FLAGS) $(IDIR)/text.cpp

arrow.o: $(IDIR)/arrow.cpp $(IDIR)/arrow.h
	$(CC) $(FLAGS) $(IDIR)/arrow.cpp

# ./src/layout -------------------------------

layout.o: $(LDIR)/layout.cpp $(LDIR)/layout.h
	$(CC) $(FLAGS) $(LDIR)/layout.cpp

# --------------------------------------------

deinstall: uninstall
uninstall:
	rm $(DESTDIR)/bin/$(BIN)

install:
	install -m 0755 $(BIN) $(DESTDIR)/bin/

clean:
	rm -f $(OBJS) $(BIN)
