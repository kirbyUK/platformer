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
#include "dynamicBlock.h"

DynamicBlock::DynamicBlock(float width, float height, float x, float y, 
							MovementType* m)
{
	//Create the rectangle:
	_shape.setSize(sf::Vector2f(width, height));
	_shape.setPosition(x, y);
	_shape.setFillColor(BLOCK_COLOUR);

	//Set the movement type:
	_movement = m;
}

DynamicBlock::~DynamicBlock()
{
	delete _movement;
}

void DynamicBlock::handleEvents(float frameTime)
{
	_movement->handleEvents(_shape, frameTime);
}

sf::FloatRect DynamicBlock::getDetectionBox(sf::Sprite& p) const
{
	//Create a box around the block with space for the player:
	return sf::FloatRect
	(
		(_shape.getPosition().x - (p.getGlobalBounds().width / 2)),
		_shape.getPosition().y,
		(_shape.getSize().x + p.getGlobalBounds().width),
		(_shape.getSize().y + (p.getGlobalBounds().height / 2))
	);
}

sf::Vector2f DynamicBlock::getDistanceMoved() const
{
	return _movement->getDistanceMoved();
}
