CC=g++
SRC=src
PDIR=$(SRC)/player
BDIR=$(SRC)/block
MDIR=$(SRC)/movement
SDIR=$(SRC)/sound
IDIR=$(SRC)/interface
LDIR=$(SRC)/level
QDIR=$(SRC)/system
BIN=platformer
OBJS=main.o player.o block.o staticBlock.o dynamicBlock.o deathBlock.o \
	 movementType.o upDown.o leftRight.o square.o sfx.o music.o screens.o \
	 text.o arrow.o timer.o level.o lockfile.o

ifdef SystemRoot
    CCFLAGS += -D WIN32
	SFML_PATH=..\..\lib\SFML-2.1
	LIBJSONCPP_PATH=..\..\lib\jsoncpp
	FLAGS=-Wall -Werror -c -g -I$(SFML_PATH)/include -I$(LIBJSONCPP_PATH)/include -std=c++11
	LIBS=-L$(SFML_PATH)/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -L$(LIBJSONCPP_PATH)/lib -ljsoncpp
#   DESTDIR="\""C:\Program Files (x86)"\""
#	ASSETS_DIR="$(DESTDIR)\\$(BIN)\\assets"
#	HIGHSCORE_DIR=%appdata%\\$(BIN)
#	HIGHSCORE="$(HIGHSCORE_DIR)\\highscore"
	ASSETS_DIR="assets"
	HIGHSCORE="highscore"
	LOCKFILE="lockfile"
else
    UNAME_S := $(shell uname -s)
	USER := $(shell whoami)
	HOMEDIR := $(shell grep $(USER) /etc/passwd | cut -d ":" -f6)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
        FLAGS=-Wall -Werror -c -g -std=c++11
        LIBS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp
        DESTDIR=/usr/local
		ASSETS_DIR="$(DESTDIR)/share/$(BIN)/assets"
		HIGHSCORE_DIR=$(HOMEDIR)/.$(BIN)
		HIGHSCORE="$(HIGHSCORE_DIR)/highscore"
		LOCKFILE="$(HIGHSCORE_DIR)/lockfile"
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
		SFML_PATH=/usr/local
        FLAGS=-Wall -Werror -c -g -I$(SFML_PATH)/include -I$(LIBJSONCPP_PATH)/include
        LIBS=-L$(SFML_PATH)/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -L$(LIBJSONCPP_PATH)/lib
        DESTDIR=/usr/local
		ASSETS_DIR="$(DESTDIR)/share/$(BIN)/assets"
		HIGHSCORE_DIR=$(HOMEDIR)/.$(BIN)
		HIGHSCORE="$(HIGHSCORE_DIR)/highscore"
		LOCKFILE="$(HIGHSCORE_DIR)/lockfile"
    endif
endif

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -g $(OBJS) -o $(BIN) $(LIBS)

# ./src/ -------------------------------------

main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) $(SRC)/main.cpp

# ./src/player/ ------------------------------

player.o: $(PDIR)/player.cpp $(PDIR)/player.h
	$(CC) $(FLAGS) -DASSETS='$(ASSETS_DIR)' -DHIGHSCORE='$(HIGHSCORE)' \
		$(PDIR)/player.cpp 

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
	$(CC) $(FLAGS) -DASSETS='$(ASSETS_DIR)' $(SDIR)/sfx.cpp

music.o: $(SDIR)/music.cpp $(SDIR)/music.h
	$(CC) $(FLAGS) -DASSETS='$(ASSETS_DIR)' $(SDIR)/music.cpp

# ./src/interface ----------------------------

screens.o: $(IDIR)/screens.cpp $(IDIR)/screens.h
	$(CC) $(FLAGS) $(IDIR)/screens.cpp

text.o: $(IDIR)/text.cpp $(IDIR)/text.h
	$(CC) $(FLAGS) -DASSETS='$(ASSETS_DIR)' $(IDIR)/text.cpp

arrow.o: $(IDIR)/arrow.cpp $(IDIR)/arrow.h
	$(CC) $(FLAGS) -DASSETS='$(ASSETS_DIR)' $(IDIR)/arrow.cpp

timer.o: $(IDIR)/timer.cpp $(IDIR)/timer.h
	$(CC) $(FLAGS) $(IDIR)/timer.cpp

# ./src/level -------------------------------

level.o: $(LDIR)/level.cpp $(LDIR)/level.h
	$(CC) $(FLAGS) $(LDIR)/level.cpp

# ./src/system -------------------------------

lockfile.o: $(QDIR)/lockfile.cpp $(QDIR)/lockfile.h
	$(CC) $(FLAGS) -DLOCKFILE='$(LOCKFILE)' $(QDIR)/lockfile.cpp

# --------------------------------------------

ifdef SystemRoot
    RM = del /Q
    FixPath = $(subst /,\,$1)
	BIN := $(BIN).exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -f
		CP = cp
        FixPath = $1
    endif
    ifeq ($(UNAME_S),Darwin)
        RM = rm -f
		CP = cp
        FixPath = $1
    endif
endif

deinstall: uninstall
uninstall:
	$(RM) $(call FixPath,$(DESTDIR)/bin/$(BIN))
	$(RM) -r $(DESTDIR)/share/$(BIN)
	$(RM) -r $(HIGHSCORE_DIR)

install:
	if [ ! -d $(DESTDIR)/bin ]; then mkdir -p $(DESTDIR)/bin; fi
	$(CP) $(BIN) $(DESTDIR)/bin/
	if [ ! -d $(ASSETS_DIR) ]; then mkdir -p $(ASSETS_DIR); fi
	$(CP) -r assets/* $(ASSETS_DIR)
	if [ ! -d $(HIGHSCORE_DIR) ]; then mkdir -p $(HIGHSCORE_DIR); fi
	if [ ! -e $(HIGHSCORE) ]; then echo 0 > $(HIGHSCORE); fi
	chown -R $(USER) $(HIGHSCORE_DIR)

clean:
	$(RM) $(call FixPath,$(OBJS)) $(call FixPath,$(BIN))
