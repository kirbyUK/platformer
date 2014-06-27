/*
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
#include "sfx.h"
#include <iostream>

//The filepaths of the sound effects, with backslashes for Windows:
#ifdef _WIN32
	const std::string SoundEffect::SFX_PATHS[TOTAL_SFX] =
	{
		"assets\\sfx\\jump.wav",
		"assets\\sfx\\death.wav",
		"assets\\sfx\\point.wav",
	};
#else
	const std::string SoundEffect::SFX_PATHS[TOTAL_SFX] =
	{
		"assets/sfx/jump.wav",
		"assets/sfx/death.wav",
		"assets/sfx/point.wav",
	};
#endif

sf::SoundBuffer SoundEffect::_soundBuffers[TOTAL_SFX];

bool SoundEffect::init()
{
	for(int i = 0; i < TOTAL_SFX; i++)
	{
		if(! _soundBuffers[i].loadFromFile(SFX_PATHS[i]))
		{
			std::cerr << "Unable to open '" << SFX_PATHS[i] << "'\n";
			return false;
		}
	}
	return true;
}

SoundEffect::SoundEffect()
{
	for(int i = 0; i < TOTAL_SFX; i++)
		_sfx[i].setBuffer(_soundBuffers[i]);
}

void SoundEffect::play(SFX s)
{
	_sfx[s].play();
}
