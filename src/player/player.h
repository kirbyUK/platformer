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
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>
#include "../sound/sfx.h"
#include "../block/dynamicBlock.h"

extern float timed;

enum Direction { LEFT = -1, NONE = 0, RIGHT = 1 };

class Player
{
	private:
		//Static members relating to the loading of the image files for use
		//as textures for the sprite:
		static const short int SPRITES = 1;
		static const std::string SPRITE_PATHS[SPRITES];
		static const sf::Color COLOUR_MASK;
		static sf::Image _sprites[SPRITES];

		//The texture and the sprite:
		sf::Texture _texture;
		sf::Sprite _sprite;

		//The maximum and minium height in pixels the character can go up 
		//before they start to fall back to the ground:
		static const float MAX_JUMP_HEIGHT, MIN_JUMP_HEIGHT;
		float _maxJumpHeight;
		float _jumpDistanceCovered;
		bool _isJumping;
		bool _canJump;

		Direction _facing;

		//These vectors contain the total distance moved by the player, split
		//across the input from the player, input from a DynamicBlock, and an
		//offset that is subtracted if there is a collision:
		static const float X_VELOCITY, Y_VELOCITY;
		struct Distance { sf::Vector2f player, block, offset, total; } _distance;
		void _resetVectors();

		//Score related variables:
		static const char* HIGHSCORE_FILE;
		unsigned int _score;
		unsigned int _highscore;

		//Sound effects:
		SoundEffect _sfx;

		//A function for converting a floating point number to a Direction:
		static Direction _getDirection(float);

		//A function to round decimal numbers to a different precision:
		static float _round(float);

	public:
		//Load the images:
		static bool init();

		//Return the array of pixels, for the icon:
		static const sf::Uint8* getPixelsPointer();

		//Constructor:
		Player();

		//Resets the player back to how it was if it had just been made:
		void reset();

		//Signal the player to jump:
		void jump();

		//Set the maximum jump height to a fraction of the actual maximum:
		void setMaxJumpHeight(float, float);

		//Signal the player to move in the given direction:
		void move(float); 			//Handles y-direction movement.
		void move(Direction, float);//Handles x-direction movement.
		void move(DynamicBlock*);	//Handles movement from a DynamicBlock.

		//Process events at the end of the frame:
		void handleCollision(sf::RectangleShape, sf::RenderWindow*);
		void handleCollision(sf::Window*);
		void handleMovement();

		//Give the player a point:
		void addPoint();

		//Kill the player:
		void kill();

		//Write the highscore to the highscore file:
		bool writeScoreToFile();

		//Getters:
		sf::Sprite& getSprite();
		unsigned int getScore() const;
		unsigned int getHighScore() const;
};

#endif
