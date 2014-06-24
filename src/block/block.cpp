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
#include "block.h"

const sf::Color Block::BLOCK_COLOUR = sf::Color(242, 241, 235);

//Checks if the player is standing on top of the block:
bool Block::isPlayerOnTop(sf::Sprite& p) const
{
	//Create a box the height of the player plus one and the width of the block:
	float playerHeight = p.getGlobalBounds().height + 1.0;
	float boxWidth = _shape.getSize().x;
	float x = _shape.getPosition().x;
	float y = _shape.getPosition().y - playerHeight;
	sf::FloatRect r(x, y, boxWidth, playerHeight);

	//Check if the top of the player is within this box:
	return r.contains(p.getPosition());
}

sf::RectangleShape Block::getShape() const
{
	return _shape;
}
