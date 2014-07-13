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
#include <SFML/Graphics.hpp>
#include "player/player.h"
#include "block/block.h"
#include "block/staticBlock.h"
#include "block/dynamicBlock.h"
#include "movement/movementType.h"
#include "movement/upDown.h"
#include "movement/leftRight.h"
#include "sound/sfx.h"
#include "interface/interface.h"
#include <vector>
#include <iostream>

const sf::Color PURPLE(182, 48, 227);

int main()
{
	//Attempt to load all the nessecary files:
	if(! Player::init())
		return -1;

	if(! SoundEffect::init())
		return -1;

	if(! Interface::init())
		return -1;

	sf::RenderWindow window(sf::VideoMode(600, 400), "Platformer");
	sf::Event event;
	sf::Clock fps;
	float frameTime = 0.016;

	//Creates guidlines every 35 pixels, offset to match the top of the player:
	std::vector <sf::RectangleShape*> guidelines;
	for(unsigned int i = 0; i < window.getSize().y / 35; i++)
	{
		sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(window.getSize().x, 1)); 
		line->setPosition(0, (i * 35) - 15);
		line->setOutlineColor(sf::Color::Red);
		line->setFillColor(sf::Color::Red);
		guidelines.push_back(line);
	}

	Player p;
	Interface interface(&window);

	//Used to time the difference between the player pressing and releasing space,
	//allowing for 'short hops' if the player releases space bar quick enough:
	sf::Clock jumpTimer;

	//Initialises the two 'target' blocks that stand at either side of the
	//screen. These are the blocks the player must jump back and forth between
	//to score points. At any time, the 'target' block is stored in the pointer
	//with the same name:
	StaticBlock b1(100, 250, 0, (400 - 250));
	StaticBlock b2(100, 250, (600 - 100), (400 - 250));
	StaticBlock* targets[2] = { &b1, &b2 };
	StaticBlock* target = targets[1];

	//This one is just for testing:
//	MovementType* m = new UpDown(100, 50, 250);
//	DynamicBlock b3(200, 100, 200, 150, m);
//	MovementType* m = new LeftRight(100, 100, 400);
//	DynamicBlock b3(100, 50, 100, 150, m);
	StaticBlock b3(100, 50, 166, 150);
	StaticBlock b4(100, 50, 332, 150);

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				//Write highscore to file if needed:
				if(p.getScore() > p.getHighScore())
				{
					if(! p.writeScoreToFile())
						return -1;
				}
				window.close();
			}
			if(event.type == sf::Event::KeyReleased)
				if(event.key.code == sf::Keyboard::Space)
					p.setMaxJumpHeight(jumpTimer.getElapsedTime().asSeconds());
		}

/*		b3.handleEvents(frameTime);
		if(b3.isPlayerOnTop(p.getSprite()))
			p.move(b3.getDistanceMoved());*/

		//Handle keypresses:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.move(LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p.move(RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			p.jump();
			jumpTimer.restart();
		}

		//Handle the player's movement:
		for(int i = 0; i < 2; i++)
			p.handleCollision(targets[i]->getShape(), frameTime);
		p.handleCollision(b3.getShape(), frameTime);
		p.handleCollision(b4.getShape(), frameTime);
		p.handleCollision(&window, frameTime);
		p.handleMovement(frameTime);

		//Check if the player has reached the target block:
		if(target->isPlayerOnTop(p.getSprite()))
		{
			p.addPoint();
			if(target == targets[0])
				target++;
			else
				target--;
		}

		//Clear the screen and draw everything:
		window.clear(PURPLE);
		window.draw(interface.getText(SCORE, p.getScore()));
		window.draw(interface.getText(HIGHSCORE, p.getHighScore()));
		window.draw(interface.getText(FPS, static_cast <unsigned>(1 / frameTime)));
		window.draw(b1.getShape());
		window.draw(b2.getShape());
		window.draw(b3.getShape());
		window.draw(b4.getShape());
		window.draw(p.getSprite());
		for(unsigned int i = 0; i < guidelines.size(); i++)
			window.draw(*guidelines[i]);
		window.display();

		//Get the time of that frame:
		frameTime = fps.restart().asSeconds();
	}
	//Cleanup the guidelines:
	for(unsigned int i = 0; i < guidelines.size(); i++)
		delete guidelines[i];

	return 0;
}
