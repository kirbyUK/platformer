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
#include "text.h"
#include <sstream>
#include <iostream>

#ifndef ASSETS
	#define ASSETS "assets"
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
	_text.setFillColor(TEXT_COLOUR);
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
	_text.setFillColor(TEXT_COLOUR);
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
