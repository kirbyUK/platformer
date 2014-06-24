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
sf::Image Player::_sprites[SPRITES];

//The file path of the file containing the player's highscore:
const char* Player::HIGHSCORE_FILE = "highscore";

//How many pixels the character will move after a second of constant motion in
//that direction:
const float Player::X_VELOCITY = 100.0;
const float Player::Y_VELOCITY = 100.0;

//The maximum jump height in pixels:
const float Player::MAX_JUMP_HEIGHT = 100.0;

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
	_jumpDistanceCovered = 0;
	_facing = RIGHT;
	_direction.x = 0;
	_direction.y = 0;
}

void jump()
{
	//stuff
}

void Player::move(Direction d)
{
	//Adjust the position vector:
	switch(d)
	{
		case LEFT:  if(_direction.x > -1) _direction.x--; break;
		case RIGHT: if(_direction.y < 1)  _direction.x++; break;
	}
}

//Checks if the proposed movement will cause a collision, and intervenes if so:
bool Player::handleCollision(sf::RectangleShape s, float frameTime)
{
	//Create a new Rect representing the player after the proposed movement:
	sf::FloatRect r
	(
		(_sprite.getGlobalBounds().left + (_direction.x * (frameTime * X_VELOCITY))),
		(_sprite.getGlobalBounds().top + (_direction.y * (frameTime * Y_VELOCITY))),
		_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height
	);

	//Check if this new Rect collides with the given sprite:
	sf::FloatRect intersection;
	if(r.intersects(s.getGlobalBounds(), intersection))
	{
		//If there is a collision, we have to check which direction it's in.
		//This is done by taking the rectangle created by the intersection and
		//looking at the sides. If it it taller than it is wide, it's in the x
		//direction. If it's the opposite, it's the y. If they're the same,
		//it's both:
		if(intersection.width < intersection.height)
			_direction.x = 0;
		else if(intersection.width > intersection.height)
			_direction.y = 0;
		else if(intersection.width == intersection.height)
		{
			_direction.x = 0;
			_direction.y = 0;
		}
		return true;
	}
	else
		return false;
}

//Moves the player based on the values in the direction vector. This should be
//called last, after everything involving collisions and all that has been done:
void Player::handleMovement(float frameTime)
{
	_sprite.move
	(
		(_direction.x * (X_VELOCITY * frameTime)), //x
		(_direction.y * (Y_VELOCITY * frameTime))  //y
	);

	//Flip the character if required:
	if(_facing != _direction.x)
	{
		//Do the flip:
		sf::IntRect rect = _sprite.getTextureRect();
		rect.left += rect.width;
		rect.width = -rect.width;
		_sprite.setTextureRect(rect);

		_facing = static_cast <Direction>(_direction.x);
	}

	//Reset the vector:
	_direction.x = 0;
	_direction.y = 0;
}

sf::Sprite& Player::getSprite()
{
	return _sprite;
}

unsigned int Player::getScore() const
{
	return _score;
}

unsigned int Player::getHighScore() const
{
	return _highscore;
}
