/* Copyright (c) Alex Kerr 2014
* This file is part of 'platformer'
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
* SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
* OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
* CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include "dynamicBlock.h"

DynamicBlock::DynamicBlock(float width, float height, float x, float y,
	std::shared_ptr <MovementType> m) : Block(width, height, x, y)
{
	//Set the movement type:
	_movement = m;
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
