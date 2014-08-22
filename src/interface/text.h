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
#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include <string>

enum Corner
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
};

class Text
{
	private:
		static const std::string FONT_PATH;
		static const sf::Color TEXT_COLOUR;
		static sf::Font _font;

		//The text item and the string it contains:
		sf::Text _text;
		std::string _string;

		//The size of the text item:
		float _size;
		Corner _corner;

	public:
		//Load the font:
		static bool init();

		//Constructor, takes the text's string, character size, a corner of the
		//window to offset from, a pointer to the window, and the offsets:
		Text(std::string, unsigned int, Corner, sf::Window*, float, float);

		//Updates the text with the given data value:
		sf::Text& updateText(unsigned int);
		sf::Text& updateText();
};

#endif
