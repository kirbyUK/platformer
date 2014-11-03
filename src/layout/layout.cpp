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
#include "layout.h"
#include "../block/staticBlock.h"
#include "../block/dynamicBlock.h"
#include "../block/deathBlock.h"
#include "../movement/movementType.h"
#include "../movement/upDown.h"
#include "../movement/leftRight.h"
#include "../movement/square.h"
#include <algorithm>
#include <cmath>

//Creates all the layouts, sticks them all in a vector array and returns it:
std::vector <std::vector<Block*>* >* initLayouts()
{
	std::vector <std::vector<Block*>* >* layouts =
		new std::vector <std::vector<Block*>* >;

	//This is going to be a long function...
	{
		StaticBlock* b = new StaticBlock(300, 100, 150, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(50, 250, 200, 150);
		StaticBlock* b2 = new StaticBlock(50, 250, 350, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(80, 25, 180, 150);
		StaticBlock* b2 = new StaticBlock(80, 25, 340, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(57, 25, 157, 150);
		StaticBlock* b2 = new StaticBlock(57, 25, 271, 120);
		StaticBlock* b3 = new StaticBlock(57, 25, 385, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new UpDown(150, 230, 70);
		MovementType* m2 = new UpDown(150, 230, 70);
		DynamicBlock* b1 = new DynamicBlock(80, 25, 180, 70, m1);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 340, 230, m2);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	{
		MovementType* m = new LeftRight(150, 120, 380);
		DynamicBlock* b = new DynamicBlock(80, 25, 150, 150, m);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b);
		layouts->push_back(v);
	}
	{
		MovementType* m = new Square(
			150, 145, 175, 200, 150, CLOCKWISE, sf::Vector2i(-1, 0));
		DynamicBlock* b = new DynamicBlock(80, 25, 250, 325, m);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new UpDown(150, 325, 100);
		MovementType* m2 = new UpDown(150, 325, 100);
		StaticBlock* b1 = new StaticBlock(75, 250, 262.5, 100);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 180.5, 100, m1);
		DynamicBlock* b3 = new DynamicBlock(80, 25, 339.5, 325, m2);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new LeftRight(175, 125, 395);
		DynamicBlock* b1 = new DynamicBlock(80, 25, 260, 200, m1);
		StaticBlock* b2 = new StaticBlock(50, 250, 275, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new Square(
			160, 125, 150, 82.5, 120, CLOCKWISE, sf::Vector2i(0, -1));
		MovementType* m2 = new Square(
			160, 312.5, 30, 82.5, 120, CLOCKWISE, sf::Vector2i(0, 1));
		DynamicBlock* b1 = new DynamicBlock(80, 25, 125, 150, m1);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 395, 150, m2);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(30, 30, 141.6, 150);
		StaticBlock* b2 = new StaticBlock(30, 30, 213.6, 190);
		StaticBlock* b3 = new StaticBlock(30, 30, 285.2, 150);
		StaticBlock* b4 = new StaticBlock(30, 30, 356.8, 110);
		StaticBlock* b5 = new StaticBlock(30, 30, 428.4, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		v->push_back(b4);
		v->push_back(b5);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(77, 25, 137, 150);
		DeathBlock* b2 = new DeathBlock(77, 25, 251, 150);
		StaticBlock* b3 = new StaticBlock(77, 25, 365, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new Square(
			150, 150, 100, 225, 200, CLOCKWISE, sf::Vector2i(1, 0));
		MovementType* m2 = new Square(
			150, 150, 100, 225, 200, ANTI_CLOCKWISE, sf::Vector2i(1, 0));
		DynamicBlock* b1 = new DynamicBlock(70, 25, 260, 100, m1);
		DynamicBlock* b2 = new DynamicBlock(70, 25, 260, 100, m2);
		StaticBlock* b3 = new StaticBlock(30, 150, 285, 0);
		StaticBlock* b4 = new StaticBlock(60, 125, 270, 275);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		v->push_back(b4);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(45, 250, 170, 150);
		StaticBlock* b2 = new StaticBlock(45, 290, 277.5, 110);
		StaticBlock* b3 = new StaticBlock(45, 250, 385, 150);
		StaticBlock* b4 = new StaticBlock(45, 100, 170, 0);
		StaticBlock* b5 = new StaticBlock(45, 60, 277.5, 0);
		StaticBlock* b6 = new StaticBlock(45, 100, 385, 0);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		v->push_back(b4);
		v->push_back(b5);
		v->push_back(b6);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new UpDown(125, 200, 100);
		MovementType* m2 = new UpDown(139, 180, 80);
		MovementType* m3 = new UpDown(121, 234, 97);
		DynamicBlock* b1 = new DynamicBlock(50, 320, 162.5, 150, m1);
		DynamicBlock* b2 = new DynamicBlock(50, 320, 275, 178, m2);
		DynamicBlock* b3 = new DynamicBlock(50, 320, 387.5, 201, m3);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		layouts->push_back(v);
	}
	{
		StaticBlock* b1 = new StaticBlock(115, 25, 100, 150);
		StaticBlock* b2 = new StaticBlock(115, 25, 385, 150);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	//The following have been contributed by Che-Hien Man (@Le-Che), thanks!
	{
		MovementType* m1 = new LeftRight(175, 125, 395);
		StaticBlock* b1 = new StaticBlock(30, 170, 285, 0);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 120, 200, m1);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
	return layouts;
}

//Delete everything to free up memory again:
void cleanup(std::vector <std::vector<Block*>* >* v)
{
	for(unsigned int i = 0; i < v->size(); i++)
	{
		for(unsigned int j = 0; j < v->at(i)->size(); j++)
			delete v->at(i)->at(j);
		delete v->at(i);
	}
	delete v;
}

//Shuffles the layouts to generate a new one:
std::vector <Block*>* shuffleLayouts(std::vector <std::vector <Block*>* >* v)
{
	//Move the current layout to the back:
	v->push_back(v->front());
	v->erase(v->begin());

	//Shuffle all the rest of the layouts and pick a new one:
	std::random_shuffle(v->begin(), (v->end() - (std::floor(v->size() / 3))));
	return v->front();
}
