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
#ifndef STATIC_BLOCK_H
#define STATIC_BLOCK_H
#include "block.h"

class StaticBlock : public Block
{
	public:
		//Constructor, takes the width, height and x/y co-ordinates:
		StaticBlock(float, float, float, float);

		void handleEvents(float) { }

		//Checks if the player is standing directly on top of the block:
		bool isPlayerOnTop(sf::Sprite&);
};

#endif
