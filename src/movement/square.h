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
#ifndef SQUARE_H
#define SQUARE_H
#include "movementType.h"

class Square : public MovementType
{
	private:
		//The direction the block is moving in:
		sf::Vector2i _direction;

		//The boundaries, which the block's origin while stay within:
		float _boundaries[2][2];

	public:
		Square(float, float, float, float, float, sf::Vector2i);
		void handleEvents(sf::RectangleShape&, float);
};

#endif
