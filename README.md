platformer
==========

![preview](https://raw.github.com/kirbyman62/platformer/master/preview.png)

An exceedingly simple platformer game because I need to make something I can 
actually finish. SFML2 and C++ as always.

The point of the game is to run back and forth between the two platforms either
side of the screen. What's in between those two pillars changes every time.

Building
--------

The program requires [SFML](www.sfml-dev.org) ( >= 2.0). There are detailed
instructions on how to install it in their tutorials section.

*Linux*

Although the Makefile has an install target it doesn't work because it doesn't
copy the assets over. For the time being, just run

```
make
```

And use the binary that appears in the project directiory.

*Windows*

I managed to get it to build using Code::Blocks and the instructions given
in the [SFML tutorial](www.sfml-dev.org/tutorials/2.1/start-cb.php). I've never
used Code::Blocks before but I had to make a new project, import all the files
and then move the binary back to the git directory so it could see the assets.
