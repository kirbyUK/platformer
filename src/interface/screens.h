/* Copyright (c) Alex Kerr 2014
* This file is part of 'platformer'
*
* 'platformer' is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* 'platformer' is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRENTY; without the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Purpose License
* along with 'platformer'. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SCREENS_H
#define SCREENS_H
#include <SFML/Graphics.hpp>

//The height and width of the window:
const unsigned int WINDOW_X = 600, WINDOW_Y = 400;

//The background colour:
const sf::Color BACKGROUND = sf::Color(182, 48, 227);

//Different functions for different 'screens'. Returns true if the player does
//not choose to quit the game:
bool pause(sf::RenderWindow*, sf::Event&, bool);
bool gameOver(sf::RenderWindow*, sf::Event&, int, int);

#endif
