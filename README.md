#platformer

![preview](https://raw.github.com/kirbyman62/platformer/master/preview.png)

An exceedingly simple platformer game because I need to make something I can actually finish. SFML2 and C++ as always.

The point of the game is to run back and forth between the two platforms either side of the screen. What's in between those two pillars changes every time.

##Building

The program requires [SFML](http://www.sfml-dev.org) ( >= 2.0). There are detailed instructions on how to install it in their tutorials section.

###Linux

Although the Makefile has an install target it doesn't work because it doesn't copy the assets over. For the time being, just run

```
make
```

And use the binary that appears in the project directory.

###Windows

####Using MinGW

If you have MinGW installed and in your path, you can use the supplied Makefile (with a few modifications).

1) Download the [MinGW build](http://sfml-dev.org/download/sfml/2.1/SFML-2.1-windows-gcc-4.7-mingw-32bits.zip) 
of SFML, and save it somewhere convenient. I put mine in C:\

2) Edit the Makefile like so:

```Makefile
FLAGS=-Wall -c -g -IC:\SFML-2.1\include
LIBS=-LC:\SFML-2.1\lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
```

3) Using cmd.exe, cd in to the directory and run the command:

```
mingw32-make
```

##TODO:

- [ ] Add a timer

- [x] Add pause functionality

- [ ] Implement lock file

- [ ] Add more layouts

- [ ] Fix [bugs](https://github.com/kirbyman62/platformer/issues)
