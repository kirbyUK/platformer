#platformer

![preview](https://raw.github.com/kirbyman62/platformer/master/preview.png)

An exceedingly simple platformer game because I needed to make something I can 
actually finish. SFML2 and C++ as always.

The point of the game is to run back and forth between the two platforms either
side of the screen. What's in between those two pillars changes every time.

##Downloads

I upload a new build with every 
[release](https://github.com/kirbyman62/platformer/releases).

**Windows**:
[32-bit](https://github.com/kirbyman62/platformer/releases/download/v1.1/platformer_win32-1.1.zip)

**Debian**:
[32-bit](https://github.com/kirbyman62/platformer/releases/download/v1.1/platformer_1.1-1_i386.deb)
|
[64-bit](https://github.com/kirbyman62/platformer/releases/download/v1.1/platformer_1.1-1_amd64.deb)

##Building

The program requires [SFML](http://www.sfml-dev.org) (>= 2.0) and
[libjsoncpp](https://github.com/open-source-parsers). Check your package
manager, they seem to be available for most decent distros.

###Linux

Provided you have SFML and libjsoncpp installed in a standard place, it should
be as easy as running:

```
make
sudo make install
platformer
```

### Mac

Along with the instructions in the Linux section, edit the Makefile similar to
Windows, like so:

```Makefile
FLAGS=-Wall -c -g -I/usr/local/include
LIBS=-L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
```

###Windows

####Using MinGW

If you have MinGW installed and in your path, you can use the supplied Makefile.

1) Download the [MinGW build](http://sfml-dev.org/download/sfml/2.1/SFML-2.1-windows-gcc-4.7-mingw-32bits.zip) 
of SFML, and extract it somewhere convinient. I placed mine in a parent
directory called 'lib'. Do the same with libjsoncpp.

2) Using cmd.exe, cd in to the directory and run the command:

```
mingw32-make SFML_PATH=..\lib\SFML-2.1 JSONCPP_PATH=..\lib\jsoncpp
```

3) Run the game

```
platformer.exe
```

The 'install' and 'uninstall' targets don't work and I can't see them doing so
any time in the near future, so you'll have to run the binary from the git
directory for now.

##TODO:

- [ ] Add more levels

- [ ] Fix [bugs](https://github.com/kirbyman62/platformer/issues)
