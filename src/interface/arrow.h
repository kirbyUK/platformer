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

		sf::Sprite& getSprite();
};

#endif
