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

const int SPRITES = 5;

class Player
{
	private:
		static sf::Image _sprites[SPRITES];
		sf::Texture _texture;
		sf::Sprite _sprite;

		bool _isJumping;
		Direction _facing;

		unsigned int _score;
		unsigned int _highScore;

	public:
		//Load the sprites:
		static bool init();

		//Constructor:
		Player();

		//Check for a collision between the player and the given sprite:
		bool checkCollision(sf::Sprite&) const;

		//Signal the player to jump:
		void jump();

		//Signal the player to move in the given direction:
		void move(Direction);

		//Process events at the end of the frame:
		void handleMovement(float);
		void handleAnimation(float);

		//Getters:
		sf::Sprite& getSprite();
		unsigned int getScore();
		unsigned int getHighScore();
};

#endif
