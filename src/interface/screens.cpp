#include "screens.h"
#include "text.h"
#include "arrow.h"

bool pause(sf::RenderWindow* w, sf::Event& event, bool haveFocus)
{
	//Create new text items:
	Text paused("PAUSED", 34, TOP_LEFT, w, 198, 125);
	Text cont("CONTINUE", 16, TOP_LEFT, w, 236, 200);
	Text quit("QUIT", 16, TOP_LEFT, w, 268, 230);
	Text* menu[2] = { &cont, &quit };
	Text* selected = menu[0];

	//Create arrows to point at the current selection:
	Arrow menuArrow1(EAST, 195, 207);
	Arrow menuArrow2(EAST, 195, 237);

	//Make a new loop for the paused screen:
	while(w->isOpen())
	{
		while(w->pollEvent(event))
		{
			//If the window is closed:
			if(event.type == sf::Event::Closed)
				w->close();

			//If the window gains focus, we can use the keyboard:
			if(event.type == sf::Event::GainedFocus)
				haveFocus = true;

			//If the window loses focus, we cannot use the keyboard:
			if(event.type == sf::Event::LostFocus)
				haveFocus = false;

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
		if(haveFocus)
		{
			//Change the selection if the player presses an arrow key:
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				if(selected == menu[1])
					selected = menu[0];

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				if(selected == menu[0])
					selected = menu[1];
		}

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
	Arrow menuArrow1(EAST, 225, 227);
	Arrow menuArrow2(EAST, 225, 257);

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
