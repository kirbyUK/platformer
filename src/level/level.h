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
#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <exception>
#include "../block/block.h"
#include "../block/dynamicBlock.h"
#include "../block/deathBlock.h"

class Level
{
	private:
		//The directory containing the levels:
		static const std::string LEVEL_DIR;

		//The level is basically just a vector of blocks:
		std::vector <std::shared_ptr<Block>> _level;

		//An exception class for if we fail to read the level correctly:
		class LevelError : public std::exception
		{
			private:
				std::string _error;

			public:
				LevelError(std::string e) { _error = e; }
				virtual const char* what() const throw() { return _error.c_str(); }
		};

	public:
		//Creates all the nessecary level objects:
		static std::vector <Level> init();

		//Shuffles the array of levels, returns the front one:
		static Level* shuffle(std::vector <Level>&);

		//Deletes all the levels:
//		static void cleanup(std::vector <Level>&);

		//Creates the individual level object, with the given filename:
		Level(std::string);
		~Level();

		//Handles events for all blocks:
		void handleEvents(float);

		//Gets the shape object of every block:
		std::vector <sf::RectangleShape> getRectangleShapes();

		//Gets every [x]Block:
		std::vector <std::shared_ptr<DynamicBlock>> getDynamicBlocks();
		std::vector <std::shared_ptr<DeathBlock>> getDeathBlocks();
};

#endif
