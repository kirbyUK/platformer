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
