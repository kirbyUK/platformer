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
#include "timer.h"
#include <cmath>

const float Timer::STARTING_TIME = 10;
const float Timer::MINIMUM_TIME = 4;

Timer::Timer(float x, float y) : _text(20, x, y)
{
	_delay = 0;
	_time = STARTING_TIME;
}

float Timer::getTimeRemaining(float delay)
{
	_delay += delay;
	return ((_time - _timer.getElapsedTime().asSeconds()) + _delay);
}

void Timer::reset(float mod)
{
	_timer.restart();
	_delay = 0;

	//Set the amount of time given, based on the modifier.
	//The formula (where y is time remaining, and x is the player's score) is
	//y = -0.07x + 10
	//Meaning it takes 100 points to reach 3 seconds, the minimum:
	_time = (-0.07 * mod) + 10;
	if(STARTING_TIME < MINIMUM_TIME)
		_time = MINIMUM_TIME;
}

sf::Text& Timer::getTimer()
{
	float t = getTimeRemaining(0);
	unsigned int seconds = floor(t);
	unsigned int milliseconds = ((t - floor(t)) * 1000);
	return _text.updateText(seconds, milliseconds);
}
