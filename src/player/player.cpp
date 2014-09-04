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
	_distance.block.x = 0;
	_distance.block.y = 0;
	_distance.total.x = 0;
	_distance.total.y = 0;
	_direction.block.x = 1;
	_direction.block.y = 1;
	_direction.player.x = 0;
	_direction.player.y = 1;
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
	_distance.block.x = 0;
	_distance.block.y = 0;
	_distance.total.x = 0;
	_distance.total.y = 0;
	_direction.block.x = 1;
	_direction.block.y = 1;
	_direction.player.x = 0;
	_direction.player.y = 1;
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
void Player::setMaxJumpHeight(float f)
{
	if(_isJumping)
	{
		f *= 420;
		_maxJumpHeight = MAX_JUMP_HEIGHT * f;
		if(_maxJumpHeight < MIN_JUMP_HEIGHT)
			_maxJumpHeight = MIN_JUMP_HEIGHT;
		else if(_maxJumpHeight > MAX_JUMP_HEIGHT)
			_maxJumpHeight = MAX_JUMP_HEIGHT;
	}
}

void Player::move(Direction d)
{
	//Adjust the position vector:
	switch(d)
	{
		case LEFT:  if(_direction.player.x > -1) _direction.player.x--; break;
		case RIGHT: if(_direction.player.x < 1)  _direction.player.x++; break;
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
void Player::handleCollision(sf::RectangleShape s, float frameTime)
{
	//We start with just movement caused by the player, as this is likely to be
	//bigger due to the player generally having a larger velocity:
	{
		float x = 	(_sprite.getGlobalBounds().left + 
					(_direction.player.x * (frameTime * X_VELOCITY)));
		float y = 	(_sprite.getGlobalBounds().top + 
					(_direction.player.y * (frameTime * Y_VELOCITY)));

		//Create a new Rect representing the player after the proposed movement:
		sf::FloatRect r(x, y,
			_sprite.getGlobalBounds().width,
			_sprite.getGlobalBounds().height
		);

		//Check if this new Rect collides with the given sprite:
		sf::FloatRect intersection;
		if(r.intersects(s.getGlobalBounds(), intersection))
		{
			//If there is a collision, we have to check which direction it's in.
			//This is done by taking the rectangle created by the intersection 
			//and looking at the sides. If it it taller than it is wide, it's in
			//the x direction. If it's the opposite, it's the y. If they're the 
			//same, it's both:
			if(intersection.width < intersection.height)
				_direction.player.x = 0;
			else if(intersection.width > intersection.height)
				_direction.player.y = 0;
			else if(intersection.width == intersection.height)
			{
				_direction.player.x = 0;
				_direction.player.y = 0;
			}

			//Now we have to check again, to see we aren't missing any collisions
			//in the other direction:
			x = 	(_sprite.getGlobalBounds().left + 
					(_direction.player.x * (frameTime * X_VELOCITY)));
			y = 	(_sprite.getGlobalBounds().top + 
					(_direction.player.y * (frameTime * Y_VELOCITY)));
			r.left = x;
			r.top = y;

			//At this point, there will be no movement, so just zero everything:
			if(r.intersects(s.getGlobalBounds()))
			{
				_direction.player.x = 0;
				_direction.player.y = 0;
			}
		}
	}
	//We now repeat the process, but with the block's movement added in as well:
	{
		float x = 	(_sprite.getGlobalBounds().left + 
					(_direction.player.x * (frameTime * X_VELOCITY)) +
					(_distance.block.x));
		float y = 	(_sprite.getGlobalBounds().top + 
					(_direction.player.y * (frameTime * Y_VELOCITY)) +
					(_distance.block.y));

		//Create a new Rect representing the player after the proposed movement:
		sf::FloatRect r(x, y,
			_sprite.getGlobalBounds().width,
			_sprite.getGlobalBounds().height
		);

		//Check if this new Rect collides with the given sprite:
		sf::FloatRect intersection;
		if(r.intersects(s.getGlobalBounds(), intersection))
		{
			//If there is a collision, we have to check which direction it's in.
			//This is done by taking the rectangle created by the intersection 
			//and looking at the sides. If it it taller than it is wide, it's in
			//the x direction. If it's the opposite, it's the y. If they're the 
			//same, it's both:
			if(intersection.width < intersection.height)
				_direction.block.x = 0;
			else if(intersection.width > intersection.height)
				_direction.block.y = 0;
			else if(intersection.width == intersection.height)
			{
				_direction.block.x = 0;
				_direction.block.y = 0;
			}

			//Now we have to check again, to see we aren't missing any collisions
			//in the other direction:
			x = 	(_sprite.getGlobalBounds().left + 
					(_direction.player.x * (frameTime * X_VELOCITY)) +
					(_distance.block.x));
			y = 	(_sprite.getGlobalBounds().top + 
					(_direction.player.y * (frameTime * Y_VELOCITY)) +
					(_distance.block.y));
			r.left = x;
			r.top = y;

			//At this point, there will be no movement, so just zero everything:
			if(r.intersects(s.getGlobalBounds()))
			{
				_direction.block.x = 0;
				_direction.block.y = 0;
			}
		}
	}
}

//Checks if the proposed movement will cause the character to go offscreen:
void Player::handleCollision(sf::Window* window, float frameTime)
{
	float x = 	(_sprite.getGlobalBounds().left + 
				(_direction.player.x * (frameTime * X_VELOCITY)) +
				_distance.block.x);
	float y =	(_sprite.getGlobalBounds().top +
				(_direction.player.y * (frameTime * Y_VELOCITY)) +
				_distance.block.y);

	//Create a new Rect representing the player after the proposed movement:
	sf::FloatRect r(x, y,
		_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height
	);

	//Check if any of the points are outside the screen:
	if((r.left < 0) || ((r.left + r.width) > window->getSize().x))
		_direction.player.x = 0;
	if((r.top < 0) || ((r.top + r.height) > window->getSize().y))
		_direction.player.y = 0;
}

//Moves the player based on the values in the direction vector. This should be
//called last, after everything involving collisions and all that has been done:
void Player::handleMovement(float frameTime)
{
	//Work out the final distance to move and move the player that distance:
	_distance.total.x = (
		(_direction.player.x * (frameTime * X_VELOCITY)) + 
		(_direction.block.x * _distance.block.x));

	_distance.total.y = (
		(_direction.player.y * (frameTime * Y_VELOCITY)) + 
		(_direction.block.y * _distance.block.y));

	_sprite.move(_distance.total.x, _distance.total.y);

	//If the player is jumping, add the distance jumped to the total distance
	//jumped so we know when to end the jump and start the player's descent:
	if(_isJumping)
	{
		_jumpDistanceCovered += (Y_VELOCITY * frameTime);
		if(_jumpDistanceCovered >= _maxJumpHeight)
		{
			_isJumping = false;
			_jumpDistanceCovered = 0;
			_maxJumpHeight = MAX_JUMP_HEIGHT;
		}
	}

	//Check if we collided with a platform this frame and allow jumping if so:
	if(_direction.player.y == 0)
		_canJump = true;
	else
		_canJump = false;

	//Flip the character if required:
	if(_direction.player.x != 0)
	{
		if(static_cast <int>(_facing) != _direction.player.x)
		{
			//Do the flip:
			sf::IntRect rect = _sprite.getTextureRect();
			rect.left += rect.width;
			rect.width = -rect.width;
			_sprite.setTextureRect(rect);

			_facing = static_cast <Direction>(_direction.player.x);
		}
	}

	//Reset the vectors:
	_distance.block.x = 0;
	_distance.block.y = 0;
	_distance.total.x = 0;
	_distance.total.y = 0;
	_direction.block.x = 1;
	_direction.block.y = 1;
	_direction.player.x = 0;
	if(_isJumping)
		_direction.player.y = -1;
	else
		_direction.player.y = 1;
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
