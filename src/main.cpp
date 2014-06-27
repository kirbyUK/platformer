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

const sf::Color PURPLE(182, 48, 227);

int main()
{
	if(! Player::init())
		return -1;

	if(! SoundEffect::init())
		return -1;

	sf::RenderWindow window(sf::VideoMode(600, 400), "Platformer");
	sf::Event event;
	sf::Clock fps;
	float frameTime = 0.016;

	Player p;
	SoundEffect sfx;

	StaticBlock b1(100, 250, 0, (400 - 250));
	StaticBlock b2(100, 250, (600 - 100), (400 - 250));

	//This one is just for testing:
	StaticBlock b3(100, 100, 250, 100);

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				//write highscore to file if needed
				window.close();
			}
		}

		//Handle keypresses:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.move(LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p.move(RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			p.jump();
			sfx.play(JUMP);
		}

		p.handleCollision(b1.getShape(), frameTime);
		p.handleCollision(b2.getShape(), frameTime);
		p.handleCollision(b3.getShape(), frameTime);
		p.handleCollision(&window, frameTime);
		p.handleMovement(frameTime);

		window.clear(PURPLE);
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
