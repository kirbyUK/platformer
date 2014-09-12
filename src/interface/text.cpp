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
#include "text.h"
#include <sstream>
#include <iostream>

#ifndef ASSETS
	#define ASSETS "./assets"
#endif

//The filepath to the font, with backslashes for Windows:
#ifdef _WIN32
	const std::string Text::FONT_PATH = 
		(((std::string)ASSETS) + ((std::string)"\\fonts\\pcsenior.ttf"));
#else
	const std::string Text::FONT_PATH =
		(((std::string)ASSETS) + ((std::string)"/fonts/pcsenior.ttf"));
#endif

//The text colour:
const sf::Color Text::TEXT_COLOUR = sf::Color(242, 241, 235);

sf::Font Text::_font;

bool Text::init()
{
	if(! _font.loadFromFile(FONT_PATH))
	{
		std::cerr << "Unable to load '" << FONT_PATH << "'\n";
		return false;
	}
	return true;
}

Text::Text(std::string string, unsigned int charSize, Corner corner,
			sf::Window* w, float x, float y)
{
	_text.setFont(_font);
	_text.setCharacterSize(charSize);
	_text.setColor(TEXT_COLOUR);
	_string = string;

	//Set the string premptively so we can get the size:
	std::stringstream ss;
	ss << _string << "00";
	_text.setString(ss.str());
	float textX = _text.getGlobalBounds().width;
	float textY = _text.getGlobalBounds().height;

	//Get the window's sizes:
	float windowX = w->getSize().x;
	float windowY = w->getSize().y;

	//Keep a track of how big the text is:
	_size = _text.getGlobalBounds().width;
	_corner = corner;

	switch(corner)
	{
		case TOP_LEFT:     _text.setPosition(x, y); break;
		case TOP_RIGHT:    _text.setPosition((windowX - textX - x), y); break;
		case BOTTOM_LEFT:  _text.setPosition(x, (windowY - textY - y)); break;
		case BOTTOM_RIGHT: _text.setPosition((windowX - textX - x), (windowY - textY - y)); break;
	}
}

//Used for the Timer class, which is less complex:
Text::Text(unsigned int charSize, float x, float y)
{
	_text.setFont(_font);
	_text.setCharacterSize(charSize);
	_text.setColor(TEXT_COLOUR);
	_text.setPosition(x, y);
}

sf::Text& Text::updateText(unsigned int value)
{
	std::stringstream ss;

	//Append a zero if it's a single-digit value:
	if(value < 10)
		ss << _string << "0" << value;
	else
		ss << _string << value;

	_text.setString(ss.str());

	//Update the position if the size changes, but only if it's on the right:
	if((_corner == TOP_RIGHT) || (_corner == BOTTOM_RIGHT))
	{
		if(_text.getGlobalBounds().width != _size)
		{
			_text.move(-(_text.getGlobalBounds().width - _size), 0);
			_size = _text.getGlobalBounds().width;
		}
	}

	return _text;
}

//Used to return the text for a Timer object:
sf::Text& Text::updateText(unsigned int seconds, unsigned int milliseconds)
{
	std::stringstream ss;

	//Append a zero if it's a single-digit value:
	if(seconds < 10)
		ss << "0" << seconds << ":" << milliseconds;
	else
		ss << _string << seconds << ":" << milliseconds;

	_text.setString(ss.str());
	return _text;
}

sf::Text& Text::updateText()
{
	_text.setString(_string);
	return _text;
}
