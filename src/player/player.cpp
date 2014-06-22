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
#include <iostream>
#include <fstream>

//The total number of images:
//const short int Player::SPRITES = 1;

//there'll be an enum here to give each image a useful name

//The filepaths to the images, with backticks for Windows:
#ifdef _WIN32
	const std::string Player::SPRITE_PATHS[SPRITES] = 
	{
		"assets\\sprites\\placeholder.png",
	};
#else
	const std::string Player::SPRITE_PATHS[SPRITES] = 
	{
		"assets/sprites/placeholder.png",
	};
#endif

//The colour to remove in the images and replace with transparency:
const sf::Color Player::COLOUR_MASK(0, 255, 0);

//The array storing all the images once they've been loaded:
sf::Image Player::_sprites[Player::SPRITES];

//The file path of the file containing the player's highscore:
const char* Player::HIGHSCORE_FILE = "highscore";

//Attempts to load up all the images, must be called before the constructor:
bool Player::init()
{
	for(short int i = 0; i < SPRITES; i++)
	{
		if(! _sprites[i].loadFromFile(SPRITE_PATHS[i]))
		{
			std::cerr << "Unable to load '" << SPRITE_PATHS[i] << "'.\n";
			return false;
		}
		else
			//If it loads fine, remove the green background:
			_sprites[i].createMaskFromColor(COLOUR_MASK);
	}
	return true;
}

Player::Player()
{	
	//Load the texture from the image:
	_texture.loadFromImage(_sprites[0]);
	_sprite.setTexture(_texture);

	//Set the initial position:
	_sprite.setPosition(37.5, 125);

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
