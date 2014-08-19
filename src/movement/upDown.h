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
#ifndef UP_DOWN_H
#define UP_DOWN_H
#include "movementType.h"

class UpDown : public MovementType
{
	private:
		//The direction the block is moving in. Works in a similar way to the
		//player's '_direction' vector, but only in 1 dimension:
		short int _direction;

		//The boundaries, which the block's origin while stay within:
		float _boundaries[2];

	public:
		UpDown(float, float, float);
		void handleEvents(sf::RectangleShape&, float);
};

#endif
