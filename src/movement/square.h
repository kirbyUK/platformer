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
#ifndef SQUARE_H
#define SQUARE_H
#include "movementType.h"

enum Direction { ANTI_CLOCKWISE = -1, CLOCKWISE = 1 };

class Square : public MovementType
{
	private:
		//Whether the block will go clockwise or anti-clockwise:
		Direction _clock;

		//The direction the block is currently moving in:
		sf::Vector2i _direction;

		//The boundaries, which the block's origin while stay within:
		float _boundaries[2][2];

	public:
		Square(float, float, float, float, float, Direction, sf::Vector2i);
		void handleEvents(sf::RectangleShape&, float);
};

#endif
