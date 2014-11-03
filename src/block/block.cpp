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
