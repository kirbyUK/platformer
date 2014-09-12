#platformer

![preview](https://raw.github.com/kirbyman62/platformer/master/preview.png)

An exceedingly simple platformer game because I need to make something I can actually finish. SFML2 and C++ as always.

The point of the game is to run back and forth between the two platforms either side of the screen. What's in between those two pillars changes every time.

##Building

The program requires [SFML](http://www.sfml-dev.org) ( >= 2.0). There are detailed instructions on how to install it in their tutorials section.

###Linux

Provided you have SFML installed in a standard place, it should be as easy as running:

```
make
sudo make install
platformer
```

### Mac

Along with the instructions in the Linux section, edit the Makefile similar to Windows, like so:

```Makefile
FLAGS=-Wall -c -g -I/usr/local/include
LIBS=-L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
```

###Windows

####Using MinGW

If you have MinGW installed and in your path, you can use the supplied Makefile.

1) Download the [MinGW build](http://sfml-dev.org/download/sfml/2.1/SFML-2.1-windows-gcc-4.7-mingw-32bits.zip) 
of SFML, and extract it somewhere convinient. I placed mine in C:\

2) Using cmd.exe, cd in to the directory and run the command:

```
mingw32-make SFML_PATH=C:\SFML-2.1
```

Replacing 'C:\SFML-2.1' with where ever you extract SFML to.

##TODO:

- [x] Add a timer

- [x] Add pause functionality

- [ ] Implement lock file

- [ ] Add more layouts

- [ ] Fix [bugs](https://github.com/kirbyman62/platformer/issues)
