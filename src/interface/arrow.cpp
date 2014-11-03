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
#include "arrow.h"
#include <iostream>

//The filepaths to the images, with backticks for Windows:
#ifndef ASSETS
	#define ASSETS "assets"
#endif

#ifdef _WIN32
	const std::string Arrow::SPRITE_PATH = 
		(((std::string)ASSETS) + ((std::string)"\\sprites\\arrow.png"));
#else
	const std::string Arrow::SPRITE_PATH =
		(((std::string)ASSETS) + ((std::string)"/sprites/arrow.png"));
#endif

//The colour to remove in the images and replace with transparency:
const sf::Color Arrow::COLOUR_MASK(0, 255, 0);

//The image containing the sprite:
sf::Image Arrow::_image;

//Attempts to load up the image, must be called before the constructor:
bool Arrow::init()
{
	if(! _image.loadFromFile(SPRITE_PATH))
	{
		std::cerr << "Unable to load '" << SPRITE_PATH << "'.\n";
		return false;
	}
	else
		_image.createMaskFromColor(COLOUR_MASK);

	return true;
}

Arrow::Arrow(Facing f, float x, float y)
{
	//Load the texture from the image:
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	//Set the position:
	_sprite.setPosition(x, y);

	//Rotate the sprite:
	_sprite.setOrigin((_sprite.getGlobalBounds().width / 2),
					  (_sprite.getGlobalBounds().height / 2));
	_sprite.rotate(static_cast <int>(f));
}

sf::Sprite& Arrow::getSprite()
{
	return _sprite;
}
