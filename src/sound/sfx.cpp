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
#include "sfx.h"
#include <iostream>

#ifndef ASSETS
	#define ASSETS "./assets"
#endif

//The filepaths of the sound effects, with backslashes for Windows:
#ifdef _WIN32
	const std::string SoundEffect::SFX_PATHS[TOTAL_SFX] =
	{
		(((std::string)ASSETS) + ((std::string)("\\sfx\\jump.wav"))),
		(((std::string)ASSETS) + ((std::string)("\\sfx\\death.wav"))),
		(((std::string)ASSETS) + ((std::string)("\\sfx\\point.wav"))),
	};
#else
	const std::string SoundEffect::SFX_PATHS[TOTAL_SFX] =
	{
		(((std::string)ASSETS) + ((std::string)("/sfx/jump.wav"))),
		(((std::string)ASSETS) + ((std::string)("/sfx/death.wav"))),
		(((std::string)ASSETS) + ((std::string)("/sfx/point.wav"))),
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
