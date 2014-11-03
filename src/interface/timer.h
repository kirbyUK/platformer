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
#ifndef TIMER_H
#define TIMER_H
#include <SFML/Graphics.hpp>
#include "text.h"

class Timer
{
	private:
		//The actual timer. It counts up, however, and we want it to count down,
		//so we'll need some class magic:
		sf::Clock _timer;

		//The time to start counting down from (in seconds):
		static const float STARTING_TIME;
		static const float MINIMUM_TIME;
		float _time;

		//The text to display the timer:
		Text _text;

		//The background so the text is always visible:
		sf::RectangleShape _background;

		//The delay from things like pausing to take into account:
		float _delay;

	public:
		//Constructor, takes the x and y position of the timer, the character
		//size and the colour of the background:
		Timer(float, float, unsigned int, sf::Color);

		float getTimeRemaining(float);
		void reset(float);
		sf::Text& getTimer();
		sf::RectangleShape& getBackground();
};

#endif
