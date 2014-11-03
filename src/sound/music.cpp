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
#include "music.h"
#include <iostream>

sf::Music Music::_music;

//The filepath to the music, with backticks for Windows:
#ifdef _WIN32
	const std::string Music::MUSIC_PATH = 
		(((std::string)ASSETS) + ((std::string)"\\music\\music.wav"));
#else
	const std::string Music::MUSIC_PATH =
		(((std::string)ASSETS) + ((std::string)"/music/music.wav"));
#endif

//Attempts to open the music, must be called before the constructor:
bool Music::init()
{
	if(! _music.openFromFile(MUSIC_PATH))
	{
		std::cerr << "Unable to open '" << MUSIC_PATH << "'.\n";
		return false;
	}
	return true;
}

//Set the music properties:
Music::Music()
{
	_music.setVolume(70);
	_music.setLoop(true);
	_music.play();
	_isPaused = false;
}

//Pauses the music:
void Music::pause()
{
	if(! _isPaused)
	{
		_music.pause();
		_isPaused = true;
	}
}

//Resumes the music:
void Music::resume()
{
	if(_isPaused)
	{
		_music.play();
		_isPaused = false;
	}
}
