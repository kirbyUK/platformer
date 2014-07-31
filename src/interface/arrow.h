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
#ifndef ARROW_H
#define ARROW_H
#include <SFML/Graphics.hpp>
#include <string>

//The direction the tip of the arrow is pointing to:
enum Facing { NORTH = 0, EAST = 90, SOUTH = 180, WEST = 270 };

class Arrow
{
	private:
		//Static members relating to the loading of the image file for use as a
		// texture for the sprite:
		static const std::string SPRITE_PATH;
		static const sf::Color COLOUR_MASK;
		static sf::Image _image;

		//The texture and the sprite:
		sf::Texture _texture;
		sf::Sprite _sprite;

	public:
		//Load the image:
		static bool init();

		//Constructor, takes the direction it's pointing to and the co-ords:
		Arrow(Facing, float, float);

		sf::Sprite getSprite() const;
};

#endif
