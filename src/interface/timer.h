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

	public:
		//Constructor, takes the x and y position of the timer:
		Timer(float x, float y);

		float getTimeRemaining() const;
		void reset(float);
		sf::Text& getTimer();
};

#endif
