/* Copyright (c) Alex Kerr 2014
* This file is part of 'platformer'
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
* SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
* OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
* CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "block/block.h"
#include "block/deathBlock.h"
#include "block/dynamicBlock.h"
#include "block/staticBlock.h"
#include "interface/arrow.h"
#include "interface/screens.h"
#include "interface/text.h"
#include "interface/timer.h"
#include "layout/layout.h"
#include "player/player.h"
#include "sound/music.h"
#include "system/lockfile.h"

int main()
{
	//Attempt to load all the nessecary files:
	if(! Player::init())
		return -1;

	if(! SoundEffect::init())
		return -1;

	if(! Music::init())
		return -1;

	if(! Text::init())
		return -1;

	if(! Arrow::init())
		return -1;

	//Create the lockfile:
	if(! createLockfile())
		return -1;

	//Seed the random number generator:
	std::srand(unsigned(std::time(0)));

	//Make the window and set the icon:
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Platformer",
		sf::Style::Close);
	window.setIcon(25, 25, Player::getPixelsPointer());
	window.setFramerateLimit(60);

	sf::Event event;
	sf::Clock frameTimer;
	sf::Clock delay;
	float delayTotal = 0.0;
	float frameTime = 0.016;

	Player p;
	Music music;
	bool death = false;

	//Create the text items:
	Text score("SCORE: ", 16, TOP_RIGHT, &window, 5, 5);
	Text high("HIGH:  ", 16, TOP_RIGHT, &window, 5, 23);
	Timer timer(240, 5, 20, BACKGROUND);

	//Used to time the difference between the player pressing and releasing
	//space, allowing for 'short hops' if the player releases space bar quick
	//enough:
	sf::Clock jumpTimer;

	//Initialises the two 'target' blocks that stand at either side of the
	//screen. These are the blocks the player must jump back and forth between
	//to score points. At any time, the 'target' block is stored in the pointer
	//with the same name:
	StaticBlock b1(100, 250, 0, (WINDOW_Y - 250));
	StaticBlock b2(100, 250, (WINDOW_X - 100), (WINDOW_Y - 250));
	StaticBlock* targets[2] = { &b1, &b2 };
	StaticBlock* target = targets[1];

	//The block at the bottom that kills the player and ends the game:
	DeathBlock deathBlock(600, 15, 0, 385);

	//Two arrows to teach the player at the beginning of the game:
	Arrow helpArrow1(SOUTH, (WINDOW_X - 50), (WINDOW_Y - 280));
	Arrow helpArrow2(SOUTH, 50, (WINDOW_Y - 280));

	//The master layouts vector, containing all possible combinations of blocks
	//that go in the middle. A pointer is used to reference the currently 
	//selected layout:
	std::vector <std::vector<Block*>* >* layouts = initLayouts();
	std::vector <Block*>* layout = layouts->front();

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			//If the window is closed:
			if(event.type == sf::Event::Closed)
			{
				//Write highscore to file if needed:
				if(p.getScore() > p.getHighScore())
				{
					if(! p.writeScoreToFile())
					{
						cleanup(layouts);
						return -1;
					}
				}
				window.close();
			}

			//If the spacebar is released:
			if(event.type == sf::Event::KeyReleased)
				if(event.key.code == sf::Keyboard::Space)
					p.setMaxJumpHeight(jumpTimer.getElapsedTime().asSeconds(),
						frameTime);

			//If the window is resized, snap it back to what it should be:
			if(event.type == sf::Event::Resized)
				window.setSize(sf::Vector2u(WINDOW_X, WINDOW_Y));

			//If the window loses focus, pause the game:
			if(event.type == sf::Event::LostFocus)
			{
				delay.restart();
				music.pause();
				if(! pause(&window, event, false))
				{
					//Write highscore to file if needed:
					if(p.getScore() > p.getHighScore())
					{
						if(! p.writeScoreToFile())
						{
							cleanup(layouts);
							return -1;
						}
					}
				}
				music.resume();
				delayTotal += delay.getElapsedTime().asSeconds();
			}
		}

		//Handle the block events:
		for(unsigned int i = 0; i < layout->size(); i++)
			layout->at(i)->handleEvents(frameTime);

		//Handle keypresses:
		//Pausing:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			delay.restart();
			music.pause();
			if(! pause(&window, event, true))
			{
				//Write highscore to file if needed:
				if(p.getScore() > p.getHighScore())
				{
					if(! p.writeScoreToFile())
					{
						cleanup(layouts);
						return -1;
					}
				}
			}
			music.resume();
			delayTotal += delay.getElapsedTime().asSeconds();
		}
		//Jumping:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			p.jump();
			jumpTimer.restart();
		}
		//Movement:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p.move(LEFT, frameTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p.move(RIGHT, frameTime);
		p.move(frameTime);

		//Check if the player is in range of a DynamicBlock, and move them:
		for(unsigned int i = 0; i < layout->size(); i++)
		{
			DynamicBlock* b = dynamic_cast <DynamicBlock*>(layout->at(i));
			if(b != NULL)
				p.move(b);
		}

		//Handle the player's movement:
		//Check collisions for the static target blocks and the layout blocks:
		for(unsigned int i = 0; i < 2; i++)
			p.handleCollision(targets[i]->getShape());
		for(unsigned int i = 0; i < layout->size(); i++)
			p.handleCollision(layout->at(i)->getShape());
		p.handleCollision(&window);
		p.handleMovement();

		//Handle animation for the death block:
		deathBlock.handleEvents(0);

		//Check if the player has reached the target block:
		if(target->isPlayerOnTop(p.getSprite()))
		{
			//Give the player a point:
			p.addPoint();

			//Reset the timer, decreasing the amount of time allowed:
			timer.reset(p.getScore());

			//Change the target block to the other one:
			if(target == targets[0])
				target++;
			else
				target--;

			layout = shuffleLayouts(layouts);
		}

		//Check if the player is on any death blocks contained in the layout:
		for(unsigned int i = 0; i < layout->size(); i++)
		{
			DeathBlock* d = dynamic_cast <DeathBlock*>(layout->at(i));
			if(d != NULL)
			{
				if(d->isPlayerOnTop(p.getSprite()))
					death = true;
			}
		}

		//Otherwise, check if the player is on top of the death block, or runs
		//out of time:
		if((deathBlock.isPlayerOnTop(p.getSprite()))
			|| ((timer.getTimeRemaining(delayTotal)) <= 0) || (death))
		{
			//Kill the player:
			p.kill();

			death = false;

			//Write highscore to file if needed:
			if(p.getScore() > p.getHighScore())
			{
				if(! p.writeScoreToFile())
				{
					cleanup(layouts);
					return -1;
				}
			}
			delay.restart();
			if(gameOver(&window, event, p.getScore(), p.getHighScore()))
			{
				p.reset();
				timer.reset(0);
				target = targets[1];
				layout = shuffleLayouts(layouts);
			}
			delayTotal += delay.getElapsedTime().asSeconds();
		}

		//Clear the screen and draw everything:
		window.clear(BACKGROUND);
		window.draw(deathBlock.getShape());
		window.draw(b1.getShape());
		window.draw(b2.getShape());
		window.draw(score.updateText(p.getScore()));
		window.draw(high.updateText(p.getHighScore()));
		if(target == targets[1])
			window.draw(helpArrow1.getSprite());
		else
			window.draw(helpArrow2.getSprite());
		for(unsigned int i = 0; i < layout->size(); i++)
			window.draw(layout->at(i)->getShape());
		window.draw(timer.getBackground());
		window.draw(timer.getTimer());
		window.draw(p.getSprite());
		window.display();

		//Get the time of that frame:
		frameTime = frameTimer.restart().asSeconds() - delayTotal;
		delayTotal = 0.0;
	}
	removeLockfile();
	cleanup(layouts);
	return 0;
}
