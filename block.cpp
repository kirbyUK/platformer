#include "block.h"

const sf::Color Block::BLOCK_COLOUR = sf::Color(242, 241, 235);

sf::RectangleShape Block::getShape() const
{
	return _shape;
}
