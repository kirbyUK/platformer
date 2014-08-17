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
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "player/player.h"
#include "block/block.h"
#include "block/staticBlock.h"
#include "block/dynamicBlock.h"
#include "block/deathBlock.h"
#include "interface/text.h"
#include "interface/arrow.h"
#include "layout/layout.h"

//The height and width of the window:
const unsigned int WINDOW_X = 600;
const unsigned int WINDOW_Y = 400;

//The background colour:
const sf::Color BACKGROUND(182, 48, 227);

//Different functions for different 'screens'. Returns true if the player does
//not choose to quit the game:
bool pause(sf::RenderWindow*, sf::Event&);
bool gameOver(sf::RenderWindow*, sf::Event&, int, int);

int main()
{
	//Attempt to load all the nessecary files:
	if(! Player::init())
		return -1;

	if(! SoundEffect::init())
		return -1;

	if(! Text::init())
		return -1;

	if(! Arrow::init())
		return -1;

	//Seed the random number generator:
	std::srand(unsigned(std::time(0)));

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Platformer", sf::Style::Close);
	sf::Event event;
	sf::Clock frameTimer;
	float frameTime = 0.016;

	Player p;

	//Create the text items:
	Text fps("FPS: ", 16, TOP_LEFT, &window, 5, 5);
	Text score("SCORE: ", 16, TOP_RIGHT, &window, 5, 5);
	Text high("HIGH:  ", 16, TOP_RIGHT, &window, 5, 23);

	//Used to time the difference between the player pressing and releasing space,
	//allowing for 'short hops' if the player releases space bar quick enough:
	sf::Clock jumpTimer;

	//Initialises the two 'target' blocks that stand at either side of the
	//screen. These are the blocks the player must jump back and forth between
	//to score points. At any time, the 'target' block is stored in the pointer
	//with the same name:
	StaticBlock b1(100, 250, 0, (WINDOW_Y - 250));
	StaticBlock b2(100, 250, (WINDOW_X - 100), (WINDOW_Y - 250));
	StaticBlock* targets[2] = { &b1, &b2 };
	StaticBlock* target = targets[1];

	//The block at the bottom that kills the player on contact and ends the game:
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
					p.setMaxJumpHeight(jumpTimer.getElapsedTime().asSeconds());

			//If the window is resized, snap it back to what it should be:
			if(event.type == sf::Event::Resized)
				window.setSize(sf::Vector2u(WINDOW_X, WINDOW_Y));

			//If the window loses focus, pause the game:
			if(event.type == sf::Event::LostFocus)
			{
				if(! pause(&window, event))
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
			jumpTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if(! pause(&window, event))
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
		}

		//Handle the block events:
		for(unsigned int i = 0; i < layout->size(); i++)
			layout->at(i)->handleEvents(frameTime);

		//Check if the player is on a dynamicBlock, and move them if so:
		for(unsigned int i = 0; i < layout->size(); i++)
		{
			if(layout->at(i)->isPlayerOnTop(p.getSprite()))
			{
				DynamicBlock* b = dynamic_cast <DynamicBlock*>(layout->at(i));
				if(b != NULL)
					p.move(b->getDistanceMoved());
			}
		}

		//Handle the player's movement:
		//Check collisions for the static target blocks and the layout blocks:
		for(unsigned int i = 0; i < 2; i++)
			p.handleCollision(targets[i]->getShape(), frameTime);
		for(unsigned int i = 0; i < layout->size(); i++)
			p.handleCollision(layout->at(i)->getShape(), frameTime);
		p.handleCollision(&window, frameTime);
		p.handleMovement(frameTime);

		//Handle animation for the death block:
		deathBlock.handleEvents(0);

		//Check if the player has reached the target block:
		if(target->isPlayerOnTop(p.getSprite()))
		{
			//Give the player a point:
			p.addPoint();

			//Change the target block to the other one:
			if(target == targets[0])
				target++;
			else
				target--;

			layout = shuffleLayouts(layouts);
		}
		//Otherwise, check if the player is on top of the death block:
		else if(deathBlock.isPlayerOnTop(p.getSprite()))
		{
			//Kill the player:
			p.kill();

			//Write highscore to file if needed:
			if(p.getScore() > p.getHighScore())
			{
				if(! p.writeScoreToFile())
				{
					cleanup(layouts);
					return -1;
				}
			}
			if(gameOver(&window, event, p.getScore(), p.getHighScore()))
			{
				p.reset();
				target = targets[1];
				layout = shuffleLayouts(layouts);
			}
		}

		//Clear the screen and draw everything:
		window.clear(BACKGROUND);
		window.draw(deathBlock.getShape());
		window.draw(b1.getShape());
		window.draw(b2.getShape());
		window.draw(fps.updateText(static_cast <unsigned>(1 / frameTime)));
		window.draw(score.updateText(p.getScore()));
		window.draw(high.updateText(p.getHighScore()));
		if(p.getScore() == 0)
			window.draw(helpArrow1.getSprite());
		if(p.getScore() == 1)
			window.draw(helpArrow2.getSprite());
		for(unsigned int i = 0; i < layout->size(); i++)
			window.draw(layout->at(i)->getShape());
		window.draw(p.getSprite());
		window.display();

		//Get the time of that frame:
		frameTime = frameTimer.restart().asSeconds();
	}
	cleanup(layouts);
	return 0;
}

bool pause(sf::RenderWindow* w, sf::Event& event)
{
	//Create new text items:
	Text paused("PAUSED", 34, TOP_LEFT, w, 192, 125);
	Text cont("CONTINUE", 16, TOP_LEFT, w, 220, 200);
	Text quit("QUIT", 16, TOP_LEFT, w, 260, 230);
	Text* menu[2] = { &cont, &quit };
	Text* selected = menu[0];

	//Create arrows to point at the current selection:
	Arrow menuArrow1(EAST, 195, 211);
	Arrow menuArrow2(EAST, 195, 241);

	//Make a new loop for the paused screen:
	while(w->isOpen())
	{
		while(w->pollEvent(event))
		{
			//If the window is closed:
			if(event.type == sf::Event::Closed)
				w->close();

			//If the window is resized, snap it back to what it should be:
			if(event.type == sf::Event::Resized)
				w->setSize(sf::Vector2u(WINDOW_X, WINDOW_Y));
		}

		//If the user presses enter, continue or quit:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(selected == menu[0])
				return true;
			else
				w->close();
		}
		//Change the selection if the player presses an arrow key:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			if(selected == menu[1])
				selected = menu[0];

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			if(selected == menu[0])
				selected = menu[1];

		//Draw everything:
		w->clear(BACKGROUND);
		w->draw(paused.updateText());
		w->draw(cont.updateText());
		w->draw(quit.updateText());
		if(selected == menu[0])
			w->draw(menuArrow1.getSprite());
		else
			w->draw(menuArrow2.getSprite());
		w->display();
	}
	return false;
}

bool gameOver(sf::RenderWindow* w, sf::Event& event, int score, int highscore)
{
	//Create new text items:
	Text gameover("GAME OVER", 34, TOP_LEFT, w, 150, 125);
	Text scoreFinal("SCORE: ", 16, TOP_LEFT, w, 150, 165);
	Text highFinal("HIGH: ", 16, TOP_LEFT, w, 330, 165);
	Text retry("RETRY", 16, TOP_LEFT, w, 250, 220);
	Text quit("QUIT", 16, TOP_LEFT, w, 260, 250);
	Text* menu[2] = { &retry, &quit };
	Text* selected = menu[0];

	//Create arrows to point at the current selection:
	Arrow menuArrow1(EAST, 225, 231);
	Arrow menuArrow2(EAST, 225, 261);

	//Make a new loop for the game over screen:
	while(w->isOpen())
	{
		while(w->pollEvent(event))
		{
			//If the window is closed:
			if(event.type == sf::Event::Closed)
				w->close();

			//If the window is resized, snap it back to what it should be:
			if(event.type == sf::Event::Resized)
				w->setSize(sf::Vector2u(WINDOW_X, WINDOW_Y));
		}

		//If the user presses enter, restart or quit:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(selected == menu[0])
				return true;
			else
				w->close();
		}

		//Change the selection if the player presses an arrow key:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			if(selected == menu[1])
				selected = menu[0];

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			if(selected == menu[0])
				selected = menu[1];

		//Draw everything:
		w->clear(BACKGROUND);
		w->draw(gameover.updateText());
		w->draw(scoreFinal.updateText(score));
		w->draw(highFinal.updateText(highscore));
		w->draw(retry.updateText());
		w->draw(quit.updateText());
		if(selected == menu[0])
			w->draw(menuArrow1.getSprite());
		else
			w->draw(menuArrow2.getSprite());
		w->display();
	}
	return false;
}
