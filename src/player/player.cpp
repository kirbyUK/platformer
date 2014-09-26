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
#include <cmath>

//there'll be an enum here to give each image a useful name

#ifndef ASSETS
	#define ASSETS "assets"
#endif

//The filepaths to the images, with backticks for Windows:
#ifdef _WIN32
	const std::string Player::SPRITE_PATHS[SPRITES] = 
	{
		(((std::string)ASSETS) + ((std::string)"\\sprites\\placeholder.png"))
	};
#else
	const std::string Player::SPRITE_PATHS[SPRITES] = 
	{
		(((std::string)ASSETS) + ((std::string)"/sprites/placeholder.png"))
	};
#endif

//The colour to remove in the images and replace with transparency:
const sf::Color Player::COLOUR_MASK(0, 255, 0);

//The array storing all the images once they've been loaded:
sf::Image Player::_sprites[SPRITES];

//The file path of the file containing the player's highscore:
#ifndef HIGHSCORE
	#define HIGHSCORE "highscore"
#endif

const char* Player::HIGHSCORE_FILE = HIGHSCORE;

//How many pixels the character will move after a second of constant motion in
//that direction:
const float Player::X_VELOCITY = 270.0;
const float Player::Y_VELOCITY = 250.0;

//The maximum and minimum jump height in pixels:
const float Player::MAX_JUMP_HEIGHT = 70.0;
const float Player::MIN_JUMP_HEIGHT = MAX_JUMP_HEIGHT / 2;

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

const sf::Uint8* Player::getPixelsPointer()
{
	return _sprites[0].getPixelsPtr();
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
	if(! file)
		_highscore = 0;
	else
	{
		file >> _highscore;
		file.close();
	}

	//Initalise everything else:
	_score = 0;
	_isJumping = false;
	_canJump = true;
	_maxJumpHeight = MAX_JUMP_HEIGHT;
	_jumpDistanceCovered = 0;
	_facing = RIGHT;
	_resetVectors();
}

void Player::reset()
{
	//Set the initial position:
	_sprite.setPosition(37.5, 125);

	//Check if the high score needs changing:
	if(_score > _highscore)
		_highscore = _score;
	
	//Reset everything else:
	_score = 0;
	_isJumping = false;
	_canJump = true;
	_maxJumpHeight = MAX_JUMP_HEIGHT;
	_jumpDistanceCovered = 0;
	if(_facing != RIGHT)
	{
		sf::IntRect rect = _sprite.getTextureRect();
		rect.left += rect.width;
		rect.width = -rect.width;
		_sprite.setTextureRect(rect);
		_facing = RIGHT;
	}
	_resetVectors();
}

void Player::jump()
{
	if(_canJump)
	{
		_isJumping = true;
		_canJump = false;
		_sfx.play(JUMP);
	}
}

//Sets the maximum jump height to a fraction of the actual maximum, to allow
//for short hopping:
void Player::setMaxJumpHeight(float seconds, float frameTime)
{
	if(_isJumping)
	{
		seconds *= frameTime;
		seconds *= 420;
		_maxJumpHeight = MAX_JUMP_HEIGHT * seconds;
		if(_maxJumpHeight < MIN_JUMP_HEIGHT)
			_maxJumpHeight = MIN_JUMP_HEIGHT;
		else if(_maxJumpHeight > MAX_JUMP_HEIGHT)
			_maxJumpHeight = MAX_JUMP_HEIGHT;
	}
}

//Handles y-based player movement, as it is not based on the player and must
//therefore be called every frame:
void Player::move(float frameTime)
{
	if(_isJumping)
		_distance.player.y = -(Y_VELOCITY * frameTime);
	else
		_distance.player.y = (Y_VELOCITY * frameTime);
}

void Player::move(Direction d, float frameTime)
{
	//Adjust the position vector:
	switch(d)
	{
		case LEFT:  _distance.player.x = LEFT *  (X_VELOCITY * frameTime); break;
		case RIGHT: _distance.player.x = RIGHT * (X_VELOCITY * frameTime); break;
	}
}

//Gives a distance to offset the movement by, given by a DynamicBlock:
void Player::move(DynamicBlock* b)
{
	//If the player is just standing on top of the block, then we can move
	//it as normal:
	if(b->isPlayerOnTop(_sprite))
		_distance.block += b->getDistanceMoved();
	else
	{
		//Otherwise, work out which axis we need to move in. This works the same
		//as collision detection - check the intersection and see which side is
		//longest:
		sf::FloatRect detectionBox = b->getDetectionBox(_sprite), intersection;
		if(_sprite.getGlobalBounds().intersects(detectionBox, intersection))
		{
			if(intersection.width < intersection.height)
				_distance.block.x += b->getDistanceMoved().x;
			else if(intersection.width > intersection.height)
				_distance.block.y += b->getDistanceMoved().y;
			else if(intersection.width == intersection.height)
				_distance.block += b->getDistanceMoved();
		}
	}
}

//Checks if the proposed movement will cause a collision, and intervenes if so:
void Player::handleCollision(sf::RectangleShape s)
{
	//Create a new Rect representing the player after the proposed movement:
	float x = (
		(_sprite.getGlobalBounds().left) + 
		(_distance.player.x + _distance.block.x)
	);
	float y = (
		(_sprite.getGlobalBounds().top) + 
		(_distance.player.y + _distance.block.y)
	);

	sf::FloatRect r(x, y,
		_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height
	);

	//Check if this new Rect collides with the given sprite:
	sf::FloatRect intersection;
	if(r.intersects(s.getGlobalBounds(), intersection))
	{
		//If there is a collision, we need to create another rect
		//representing the player after movement with one of the directions
		//cancelled out, as in many cases this will sort out the other
		//direction on it's own. Which direction to handle first is important,
		//and this is determined by taking the intersection rect. If it's
		//taller than it is wide, we do the x direction first, and vice-versa.
		if(intersection.height > intersection.width)
			_distance.offset.x += intersection.width;
		else
			_distance.offset.y += intersection.height;

		//Now we do the same again:
		x = (
			(_sprite.getGlobalBounds().left) +
			(_distance.player.x + _distance.block.x) -
			(_getDirection(_distance.player.x + _distance.block.x) * 
			_distance.offset.x)
		);
		y = (
			(_sprite.getGlobalBounds().top) +
			(_distance.player.y + _distance.block.y) -
			(_getDirection(_distance.player.y + _distance.block.y) * 
			_distance.offset.y)
		);

		r.left = x;
		r.top =  y;

		if(r.intersects(s.getGlobalBounds(), intersection))
		{
			if((_round(intersection.height) != 0) && (_round(intersection.width) != 0))
			{
				if(_distance.offset.x != 0)
					_distance.offset.y += intersection.height;
				else
					_distance.offset.x += intersection.width;
			}
		}
	}
}

//Checks if the proposed movement will cause the character to go offscreen:
void Player::handleCollision(sf::Window* window)
{
	//Create a new Rect representing the player after the proposed movement:
	float x = (
		(_sprite.getGlobalBounds().left) +
		(_distance.player.x + _distance.block.x) -
		(_getDirection(_distance.player.x + _distance.block.x) * 
		_distance.offset.x)
	);
	float y = (
		(_sprite.getGlobalBounds().top) +
		(_distance.player.y + _distance.block.y) -
		(_getDirection(_distance.player.y + _distance.block.y) * 
		_distance.offset.y)
	);

	sf::FloatRect r(x, y,
		_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height
	);

	//Check if any of the points are outside the screen:
	if(r.left < 0)
		_distance.offset.x += -r.left;
	else if((r.left + r.width) > window->getSize().x)
		_distance.offset.x += ((r.left + r.width) - window->getSize().x);
	else if(r.top < 0)
		_distance.offset.y += -r.top;
}

//Moves the player based on the values in the direction vector. This should be
//called last, after everything involving collisions and all that has been done:
void Player::handleMovement()
{
	_distance.total.x = (
		(_distance.player.x + _distance.block.x) -
		(_getDirection(_distance.player.x + _distance.block.x) * 
		_distance.offset.x)
	);
	_distance.total.y = (
		(_distance.player.y + _distance.block.y) -
		(_getDirection(_distance.player.y + _distance.block.y) * 
		_distance.offset.y)
	);

	//Move the player:
	_sprite.move(_round(_distance.total.x), _round(_distance.total.y));

	//If the player is jumping, add the distance jumped to the total distance
	//jumped so we know when to end the jump and start the player's descent:
	if(_isJumping)
	{
		_jumpDistanceCovered += -_distance.player.y;
		if((_jumpDistanceCovered >= _maxJumpHeight) ||
			(_round(_distance.offset.y) == _round(_distance.player.y)))
		{
			_isJumping = false;
			_jumpDistanceCovered = 0;
			_maxJumpHeight = MAX_JUMP_HEIGHT;
		}
	}

	//Check if we collided with a platform this frame and allow jumping if so:
	if((_round(_distance.offset.y) == _round(_distance.player.y)) && 
		(! _canJump))
		_canJump = true;

	//Flip the character if required:
	if(_distance.player.x != 0)
	{
		if(_facing != _getDirection(_distance.player.x))
		{
			//Do the flip:
			sf::IntRect rect = _sprite.getTextureRect();
			rect.left += rect.width;
			rect.width = -rect.width;
			_sprite.setTextureRect(rect);

			_facing = _getDirection(_distance.player.x);
		}
	}
	_resetVectors();
}

void Player::addPoint()
{
	_score++;
	_sfx.play(POINT);
}

void Player::kill()
{
	_sfx.play(DEATH);
}

bool Player::writeScoreToFile()
{
	std::ofstream file(HIGHSCORE_FILE);
	if(! file)
	{
		std::cerr << "Unable to write to '" << HIGHSCORE_FILE << "'\n";
		return false;
	}
	else
	{
		file << _score;
		file.close();
		return true;
	}
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

//Simplifies resetting the vectors as it's repeated quite a bit:
void Player::_resetVectors()
{
	//Reset the vectors:
	_distance.player.x = 0;
	_distance.player.y = 0;
	_distance.block.x = 0;
	_distance.block.y = 0;
	_distance.offset.x = 0;
	_distance.offset.y = 0;
	_distance.total.x = 0;
	_distance.total.y = 0;
}

Direction Player::_getDirection(float f)
{
	if(f > 0) return RIGHT; else return LEFT;
}

float Player::_round(float f)
{
	//<stackoverflow.com/questions/11208971/round-a-float-to-a-given-precision>
	return (float)(std::floor(f * (1.0 / 0.001) + 0.5) / (1.0 / 0.001));
}
