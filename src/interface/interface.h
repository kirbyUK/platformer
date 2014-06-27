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
#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include <string>

enum Text
{
	SCORE,
	HIGHSCORE,
	FPS,
	TEXT_ITEMS,
};

class Interface
{
	private:
		//The font and text items:
		static const std::string FONT_PATH;
		static const sf::Color TEXT_COLOUR;
		static sf::Font _font;
		sf::Text _text[TEXT_ITEMS];

	public:
		//Load the font:
		static bool init();

		//Positions the text relative to the window:
		Interface(sf::Window*);

		//Returns the specified text item with the given subbed in:
		sf::Text& getText(Text, unsigned int);
};

#endif
