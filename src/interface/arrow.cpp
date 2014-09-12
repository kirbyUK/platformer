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
#include "arrow.h"
#include <iostream>

//The filepaths to the images, with backticks for Windows:
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
