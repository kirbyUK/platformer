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
#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

class Block
{
	protected:
		sf::RectangleShape _shape;
		static const sf::Color BLOCK_COLOUR; 
	public:
		virtual ~Block() { }
		virtual void handleEvents(float) = 0;

		//Checks if the player is standing directly on top of the block:
		bool isPlayerOnTop(sf::Sprite&) const;

		sf::RectangleShape getShape() const;
};

extern sf::RectangleShape detection;
extern sf::RectangleShape playerTop;

#endif
