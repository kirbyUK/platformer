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
#include "sound/sfx.h"
#include "interface/interface.h"

const sf::Color PURPLE(182, 48, 227);

int main()
{
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

	Player p;
	Interface interface(&window);

	StaticBlock b1(100, 250, 0, (400 - 250));
	StaticBlock b2(100, 250, (600 - 100), (400 - 250));
	StaticBlock* targets[2] = { &b1, &b2 };
	StaticBlock* target = targets[1];

	//This one is just for testing:
	StaticBlock b3(200, 100, 200, 150);

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
		}

		//Handle keypresses:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.move(LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p.move(RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			p.jump();

		//Handle the player's movement:
		for(int i = 0; i < 2; i++)
			p.handleCollision(targets[i]->getShape(), frameTime);
		p.handleCollision(b3.getShape(), frameTime);
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

		window.clear(PURPLE);
		window.draw(interface.getText(SCORE, p.getScore()));
		window.draw(interface.getText(HIGHSCORE, p.getHighScore()));
		window.draw(interface.getText(FPS, static_cast <unsigned>(1 / frameTime)));
		window.draw(b1.getShape());
		window.draw(b2.getShape());
		window.draw(b3.getShape());
		window.draw(p.getSprite());
		window.display();

		//Get the time of that frame:
		frameTime = fps.restart().asSeconds();
	}
	return 0;
}
