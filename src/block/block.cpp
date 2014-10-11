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
bool Block::isPlayerOnTop(sf::Sprite& player) const
{
	//Create a box the height of the player plus one and the width of the block:
	float playerHeight = player.getGlobalBounds().height;
	float boxWidth = _shape.getSize().x;
	float x = _shape.getPosition().x;
	float y = _shape.getPosition().y - playerHeight;
	sf::FloatRect r(x, y, boxWidth, playerHeight);

	//Make a rect that is 1 pixel tall to represent the top of the player:
	sf::FloatRect p(player.getPosition(),
		sf::Vector2f(player.getGlobalBounds().width, 1));

	if(p.intersects(r))
		return true;

	return false;
}

sf::RectangleShape Block::getShape() const
{
	return _shape;
}
