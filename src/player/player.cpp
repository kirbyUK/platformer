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
#include "player.h"
#include <fstream>

const char* HIGHSCORE_FILE = "highscore";

//sf::Image Player::_images[SPRITES];

bool Player::init()
{
	//stuff
	return true;
}

Player::Player()
{
	//Set the initial position:
	_sprite.setPosition(0, 0);

	//Get the previous highscore:
	std::ifstream file(HIGHSCORE_FILE);
	file >> _highscore;
	file.close();

	//Initalise everything else:
	_score = 0;
	_isJumping = false;
	_facing = RIGHT;
}

bool Player::checkCollision(sf::Sprite& s) const
{
	return _sprite.getGlobalBounds().intersects(s.getGlobalBounds());
}

void jump()
{
	//stuff
}

void move(Direction d)
{
	//stuff
}

sf::Sprite& Player::getSprite()
{
	return _sprite;
}

unsigned int Player::getScore()
{
	return _score;
}

unsigned int Player::getHighScore()
{
	return _highscore;
}
