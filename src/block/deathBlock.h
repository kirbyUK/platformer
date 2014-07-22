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
#ifndef DEATH_BLOCK_H
#define DEATH_BLOCK_H
#include "block.h"

class DeathBlock : public Block
{
	private:
		//The red colour used:
		static const sf::Color DEATH_BLOCK_RED;

		//The amount of time in seconds before we switch colour:
		static const float ANIMATION_TIME;

		//The clock to comtrol the animation:
		sf::Clock _animation;

	public:
		//Constructor:
		DeathBlock(float, float, float, float);

		//Control the flickering, the only reason this class exists:
		void handleEvents(float);
};

#endif
