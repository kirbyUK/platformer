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
#include "deathBlock.h"

const sf::Color DeathBlock::DEATH_BLOCK_RED = sf::Color(237, 69, 69);
const float DeathBlock::ANIMATION_TIME = 0.12;

DeathBlock::DeathBlock(float width, float height, float x, float y) :
	Block(width, height, x, y)
{
}

void DeathBlock::handleEvents(float f)
{
	if(_animation.getElapsedTime().asSeconds() >= ANIMATION_TIME)
	{
		if(_shape.getFillColor() == BLOCK_COLOUR)
			_shape.setFillColor(DEATH_BLOCK_RED);
		else
			_shape.setFillColor(BLOCK_COLOUR);
		_animation.restart();
	}
}
