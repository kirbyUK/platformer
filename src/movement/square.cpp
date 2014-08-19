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
#include "square.h"

Square::Square(float velocity, float x, float y, float width, float height)
{
	_distanceMoved.x = 0;
	_distanceMoved.y = 0;

	_velocity = velocity;
	_boundaries[0][0] = x;
	_boundaries[0][1] = x + width;
	_boundaries[1][0] = y;
	_boundaries[1][1] = y + height;

	_direction.x = -1;
	_direction.y = 0;
}

void Square::handleEvents(sf::RectangleShape& shape, float frameTime)
{
	//The block moves in a clockwise square shape, like so:
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
	shape.move((_direction.x * (_velocity * frameTime)),
				(_direction.y * (_velocity * frameTime)));

	//Save the distance moved:
	_distanceMoved.x = (_direction.x * (_velocity * frameTime));
	_distanceMoved.y = (_direction.y * (_velocity * frameTime));
}
