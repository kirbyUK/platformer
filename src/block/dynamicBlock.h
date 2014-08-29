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
#ifndef DYNAMIC_BLOCK_H
#define DYNAMIC_BLOCK_H
#include "block.h"
#include "../movement/movementType.h"

class DynamicBlock : public Block
{
	private:
		MovementType* _movement;

	public:
		//Constructor, takes the width, height, initial x/y co-ordinates and
		//the movement type:
		DynamicBlock(float, float, float, float, MovementType*);
		~DynamicBlock();

		//Checks if the player is anywhere in range of the block, so the block
		//can push the player along if required:
		bool isPlayerInRange(sf::Sprite&);

		void handleEvents(float);

		sf::Vector2f getDistanceMoved() const;
};

#endif
