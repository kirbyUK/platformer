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
#ifndef SFX_H
#define SFX_H
#include <SFML/Audio.hpp>
#include <string>

enum SFX
{
	JUMP,
	DEATH,
	POINT,
	TOTAL_SFX
};

class SoundEffect
{
	private:
		static const std::string SFX_PATHS[TOTAL_SFX];
		static sf::SoundBuffer _soundBuffers[TOTAL_SFX];
		sf::Sound _sfx[TOTAL_SFX];
	public:
		//Load the sound effects:
		static bool init();

		SoundEffect();
		void play(SFX);
};

#endif
