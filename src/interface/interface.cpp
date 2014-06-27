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
#include "interface.h"
#include <iostream>
#include <sstream>

//The filepath to the font, with backslashes for Windows:
#ifdef _WIN32
	const std::string Interface::FONT_PATH = "assets\\fonts\\pcsenior.ttf";
#else
	const std::string Interface::FONT_PATH = "assets/fonts/pcsenior.ttf";
#endif

//The text colour:
const sf::Color Interface::TEXT_COLOUR = sf::Color(242, 241, 235);

sf::Font Interface::_font;

bool Interface::init()
{
	if(! _font.loadFromFile(FONT_PATH))
	{
		std::cerr << "Unable to load '" << FONT_PATH << "'\n";
		return false;
	}
	return true;
}

Interface::Interface(sf::Window* w)
{
	//Sorts out the colour and font and size for all the text items:
	for(int i = 0; i < TEXT_ITEMS; i++)
	{
		_text[i].setFont(_font);
		_text[i].setCharacterSize(16);
		_text[i].setColor(TEXT_COLOUR);
	}

	//Now set the specific stuff:
	_text[SCORE].setString("SCORE: 00");
	_text[SCORE].setPosition(
		((w->getSize().x - _text[SCORE].getGlobalBounds().width) - 5), 5);

	_text[HIGHSCORE].setString("HIGH:  00");
	_text[HIGHSCORE].setPosition
	(
		(_text[SCORE].getPosition().x), 
		(_text[SCORE].getPosition().y + _text[SCORE].getGlobalBounds().height + 2)
	);

	_text[FPS].setString("FPS: 000");
	_text[FPS].setPosition(5, 5);
} 

sf::Text& Interface::getText(Text text, unsigned int i)
{
	std::stringstream ss;
	if(text == SCORE)
	{
		if(i < 10)
			ss << "SCORE: 0" << i;
		else
			ss << "SCORE: " << i;
	}
	else if(text == HIGHSCORE)
	{
		if(i < 10)
			ss << "HIGH:  0" << i;
		else
			ss << "HIGH:  " << i;
	}
	else if(text == FPS)
	{
		ss << "FPS: " << i;
	}
	_text[text].setString(ss.str());
	return _text[text];
}
