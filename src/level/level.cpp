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
#include "level.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <dirent.h>
#include <json/json.h>
#include "../block/staticBlock.h"
#include "../movement/movementType.h"
#include "../movement/leftRight.h"
#include "../movement/upDown.h"
#include "../movement/square.h"

#include <iostream>

#ifndef ASSETS
	#define ASSETS "assets"
#endif

#ifdef _WIN32
	const std::string Level::LEVEL_DIR = (
		static_cast <std::string>(ASSETS) + "\\levels\\");
#else
	const std::string Level::LEVEL_DIR = (
		static_cast <std::string>(ASSETS) + "/levels/");
#endif

//Reads in the levels contained in 
std::vector <Level> Level::init()
{
	std::vector <Level> levels;
	DIR* dir = opendir(LEVEL_DIR.c_str());
	if(dir == NULL)
	{
		//throw error
	}
	else
	{
		std::vector <std::string> filepaths;
		for(dirent* dir_c = readdir(dir); dir_c != NULL; dir_c = readdir(dir))
		{
			//Get the name:
			std::string name = dir_c->d_name;

			//Skip the iteration if we're reading "." or "..":
			if((name == ".") || (name == ".."))
				continue;

			//Otherwise, add the filename:
			filepaths.push_back(LEVEL_DIR + name);
		}
		//Sort the filenames so we get them in the right order:
		std::sort(filepaths.begin(), filepaths.end());

		//Make the levels:
		for(auto i = filepaths.begin(); i != filepaths.end(); i++)
		{
			Level level(*i);
			levels.push_back(level);
		}
	}
	return levels;
}

//Deletes all the dynamically-allocated blocks:
/*void Level::cleanup(std::vector <Level>& v)
{
	for(auto i = v.begin(); i != v.end(); i++)
		for(auto j = i->begin(); j != i->end(); i++)
			delete *j;
}*/

Level::~Level()
{
	std::cout << "Deleting level: " << this << std::endl;
	for(auto& i : _level)
		delete i;
}

//Shuffles the array of levels, and returns the front element:
Level* Level::shuffle(std::vector <Level>& v)
{
	//Move the current layout to the back:
	v.push_back(v.front());
	v.erase(v.begin());

	//Shuffle all the rest of the layouts and pick a new one:
	std::random_shuffle(v.begin(), (v.end() - (std::floor(v.size() / 3))));
	return &v.front();
}

//Reads the JSON from the passed file, and constructs a vector of Blocks:
Level::Level(std::string filename)
{
	std::ifstream in(filename);
	if(! in)
	{
		//error lol
	}

	Json::Reader reader;
	Json::Value root;
	if(! reader.parse(in, root))
	{
		//error lol
	}

	for(auto& i : root)
	{
		//Get what type of item this is:
		std::string type = i.get("type", "none").asString();

		//Make a StaticBlock:
		if(type == "static")
		{
			StaticBlock* b = new StaticBlock(
				i.get("width", 0).asFloat(),
				i.get("height", 0).asFloat(),
				i.get("x", 0).asFloat(),
				i.get("y", 0).asFloat()
			);
			_level.push_back(b);
		}
		//Make a DynamicBlock:
		else if(type == "dynamic")
		{
			//First we need the MovementType, so check for that and make it:
			Json::Value movement = i.get("movement", Json::Value());
			if(movement.empty())
			{
				//error lol
			}
			MovementType* m = NULL;
			std::string m_type = movement.get("type", "none").asString();
			if(type == "LeftRight")
			{
				m = new LeftRight(
					i.get("velocity", 0).asFloat(),
					i.get("boundary1", 0).asFloat(),
					i.get("boundary2", 0).asFloat()
				);
			}
			else if(type == "UpDown")
			{
				m = new UpDown(
					i.get("velocity", 0).asFloat(),
					i.get("boundary1", 0).asFloat(),
					i.get("boundary2", 0).asFloat()
				);
			}
			else if(type == "Square")
			{
				sf::Vector2i start(
					i.get("startx", 0).asInt(),
					i.get("starty", 0).asInt()
				);
				m = new Square(
					i.get("velocity", 0).asFloat(),
					i.get("x", 0).asFloat(),
					i.get("y", 0).asFloat(),
					i.get("width", 0).asFloat(),
					i.get("height", 0).asFloat(),
					static_cast <Direction>(i.get("direction", 0).asFloat()),
					start
				);
			}
			else
			{
				//error lol
			}

			//Now make the actual block:
			DynamicBlock* b = new DynamicBlock(
				i.get("width", 0).asFloat(),
				i.get("height", 0).asFloat(),
				i.get("x", 0).asFloat(),
				i.get("y", 0).asFloat(),
				m
			);
			_level.push_back(b);
		}
		//Make a DeathBlock:
		else if(type == "death")
		{
			DeathBlock* b = new DeathBlock(
				i.get("width", 0).asFloat(),
				i.get("height", 0).asFloat(),
				i.get("x", 0).asFloat(),
				i.get("y", 0).asFloat()
			);
			_level.push_back(b);
		}
		else
		{
			//error lol
		}
	}
}

//Handles events for all blocks:
void Level::handleEvents(float frameTime)
{
	for(auto& i : _level)
		i->handleEvents(frameTime);
}

//Returns every RectangleShape:
std::vector <sf::RectangleShape> Level::getRectangleShapes()
{
	std::vector <sf::RectangleShape> shapes;
	for(auto &i : _level)
		shapes.push_back(i->getShape());
	return shapes;
}

//Returns every DynamicBlock:
std::vector <DynamicBlock*> Level::getDynamicBlocks()
{
	std::vector <DynamicBlock*> blocks;
	for(auto& i : _level)
	{
		DynamicBlock* b = dynamic_cast <DynamicBlock*>(i);
		if(b != NULL)
			blocks.push_back(b);
	}
	return blocks;
}

//Returns every DynamicBlock:
std::vector <DeathBlock*> Level::getDeathBlocks()
{
	std::vector <DeathBlock*> blocks;
	for(auto &i : _level)
	{
		DeathBlock* b = dynamic_cast <DeathBlock*>(i);
		if(b != NULL)
			blocks.push_back(b);
	}
	return blocks;
}
