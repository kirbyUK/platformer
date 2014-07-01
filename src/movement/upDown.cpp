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
#include "upDown.h"

UpDown::UpDown(float velocity, float boundary1, float boundary2)
{
	_distanceMoved.x = 0;
	_distanceMoved.y = 0;

	_velocity = velocity;
	if(boundary1 > boundary2)
	{
		_boundaries[0] = boundary1;
		_boundaries[1] = boundary2;
	}
	else
	{
		_boundaries[0] = boundary2;
		_boundaries[1] = boundary1;
	}
	_direction = 1;
}

void UpDown::handleEvents(sf::RectangleShape& shape, float frameTime)
{
	//Check if we need to change direction:
	if(shape.getPosition().y >= _boundaries[0])
		_direction = -1;
	else if(shape.getPosition().y <= _boundaries[1])
		_direction = 1;

	//Move the block:
	shape.move(0, (_direction * (_velocity * frameTime)));

	//Save the distance moved:
	_distanceMoved.y = (_direction * (_velocity * frameTime));
}
