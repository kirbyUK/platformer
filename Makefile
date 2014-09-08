ifdef SystemRoot
    CCFLAGS += -D WIN32
    FLAGS=-Wall -Werror -c -g -IC:\SFML-2.1\include
    LIBS=-LC:\SFML-2.1\lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
    DESTDIR="\""C:\Program Files (x86)"\""
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
        FLAGS=-Wall -Werror -c -g
        LIBS=-lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
        DESTDIR=/usr/local
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
        FLAGS=-Wall -Werror -c -g -I/usr/local/include
        LIBS=-L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
        DESTDIR=/usr/local
    endif
endif

CC=g++
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

ifdef SystemRoot
    RM = del /Q
    FixPath = $(subst /,\,$1)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -f
        FixPath = $1
    endif
    ifeq ($(UNAME_S),Darwin)
        RM = rm -f
        FixPath = $1
    endif
endif

deinstall: uninstall
uninstall:
	$(RM) $(call FixPath,$(DESTDIR)/bin/$(BIN)/*)

install:
	install -m 0755 $(BIN) $(call FixPath,$(DESTDIR)/bin/)

clean:
	$(RM) $(call FixPath,$(OBJS)/*) $(call FixPath,$(BIN)/*)
