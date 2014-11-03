/* Copyright (c) Alex Kerr 2014
* This file is part of 'platformer'
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
* SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
* OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
* CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
		Text(unsigned int charSize, float x, float y);

		//Updates the text with the given data value:
		sf::Text& updateText(unsigned int);
		sf::Text& updateText(unsigned int, unsigned int);
		sf::Text& updateText();
};

#endif
