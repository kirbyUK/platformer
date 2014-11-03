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
#include "square.h"

Square::Square(float velocity, float x, float y, float width, float height, 
	Direction clock, sf::Vector2i d)
{
	_distanceMoved.x = 0;
	_distanceMoved.y = 0;

	_velocity = velocity;
	_boundaries[0][0] = x;
	_boundaries[0][1] = x + width;
	_boundaries[1][0] = y;
	_boundaries[1][1] = y + height;

	_direction = d;
	_clock = clock;
}

void Square::handleEvents(sf::RectangleShape& shape, float frameTime)
{
	//The block moves in a square shape (clockwise or anti-clockwise), like so:
	// * -------> *
	// ^          |
	// |          |
	// |          v
	// * <------- *

	//If the block hits any of the boundaries, change the direction:
	//Bottom left:
	if(shape.getPosition().x < _boundaries[0][0])
	{
		shape.setPosition(_boundaries[0][0], shape.getPosition().y);
		_direction.x = 0;
		_direction.y = -1;
	}
	//Top right:
 	else if(shape.getPosition().x > _boundaries[0][1])
	{
		shape.setPosition(_boundaries[0][1], shape.getPosition().y);
		_direction.x = 0;
		_direction.y = 1;
	}
	//Top left:
	else if(shape.getPosition().y < _boundaries[1][0])
	{
		shape.setPosition(shape.getPosition().x, _boundaries[1][0]);
		_direction.x = 1;
		_direction.y = 0;
	}
	//Bottom right:
	else if(shape.getPosition().y > _boundaries[1][1])
	{
		shape.setPosition(shape.getPosition().x, _boundaries[1][1]);
		_direction.x = -1;
		_direction.y = 0;
	}

	//Move the block:
	shape.move(
		(_clock * (_direction.x * (_velocity * frameTime))),
		(_clock * (_direction.y * (_velocity * frameTime)))
	);

	//Save the distance moved:
	_distanceMoved.x = (_clock * (_direction.x * (_velocity * frameTime)));
	_distanceMoved.y = (_clock * (_direction.y * (_velocity * frameTime)));
}
