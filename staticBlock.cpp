#include "staticBlock.h"

StaticBlock::StaticBlock(float width, float height, float x, float y)
{
	//Create the rectangle:
	_shape.setSize(sf::Vector2f(width, height));
	_shape.setPosition(x, y);
	_shape.setFillColor(BLOCK_COLOUR);
}

//Checks if the player is standing on top of the block:
bool StaticBlock::isPlayerOnTop(sf::Sprite& p)
{
	//Create a box the height of the player plus one and the width of the block:
	float playerHeight = p.getGlobalBounds().height + 1.0;
	float boxWidth = _shape.getSize().x;
	float x = _shape.getPosition().x;
	float y = _shape.getPosition().y + playerHeight;
	sf::FloatRect r(x, y, boxWidth, playerHeight);

	//Check if the top of the player is within this box:
	return r.contains(p.getPosition());
}
