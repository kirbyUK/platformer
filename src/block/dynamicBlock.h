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
#ifndef DYNAMIC_BLOCK_H
#define DYNAMIC_BLOCK_H
#include "block.h"
#include "../movement/movementType.h"
#include <memory>

class DynamicBlock : public Block
{
	private:
		std::shared_ptr <MovementType> _movement;

	public:
		//Constructor, takes the width, height, initial x/y co-ordinates and
		//the movement type:
		DynamicBlock(float, float, float, float, std::shared_ptr <MovementType>);

		void handleEvents(float);

		sf::FloatRect getDetectionBox(sf::Sprite&) const;
		sf::Vector2f getDistanceMoved() const;
};

#endif
