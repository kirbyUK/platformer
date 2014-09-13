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
#include "layout.h"
#include "../block/staticBlock.h"
#include "../block/dynamicBlock.h"
#include "../movement/movementType.h"
#include "../movement/upDown.h"
#include "../movement/leftRight.h"
#include "../movement/square.h"
#include <algorithm>

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
			150, 145, 175, 200, 150, sf::Vector2i(-1, 0));
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
			160, 125, 150, 82.5, 120, sf::Vector2i(0, -1));
		MovementType* m2 = new Square(
			160, 312.5, 30, 82.5, 120, sf::Vector2i(0, 1));
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
	//The following have been contributed by Che-Hien Man (@Le-Che), thanks!
	{
		StaticBlock* b1 = new StaticBlock(50, 280, 275, 0);
		StaticBlock* b2 = new StaticBlock(60, 25, 120, 210);
		StaticBlock* b3 = new StaticBlock(60, 25, 165, 275);
		StaticBlock* b4 = new StaticBlock(60, 25, 210, 340);
		StaticBlock* b5 = new StaticBlock(60, 25, 330, 340);
		StaticBlock* b6 = new StaticBlock(60, 25, 375, 275);
		StaticBlock* b7 = new StaticBlock(60, 25, 420, 210);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
		v->push_back(b4);
		v->push_back(b5);
		v->push_back(b6);
		v->push_back(b7);
		layouts->push_back(v);
	}
	{
		MovementType* m1 = new LeftRight(175, 125, 395);
		StaticBlock* b1 = new StaticBlock(30, 170, 285, 0);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 120, 200, m1);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		layouts->push_back(v);
	}
/*	{ //Level 5.png - Ask about this!
		StaticBlock* b1 = new StaticBlock(30, 150, 150, 0);
		StaticBlock* b2 = new StaticBlock(30, 150, 450, 0);
		StaticBlock* b3 = new StaticBlock(30, 250, 285, 100);
//		StaticBlock* b4 = new StaticBlock(60, 25, 210, 340);
//		StaticBlock* b5 = new StaticBlock(60, 25, 330, 340);
//		StaticBlock* b6 = new StaticBlock(60, 25, 375, 275);
		StaticBlock* b7 = new StaticBlock(320, 25, 140, 335);
		std::vector <Block*>* v = new std::vector<Block*>;
		v->push_back(b1);
		v->push_back(b2);
		v->push_back(b3);
//		v->push_back(b4);
//		v->push_back(b5);
//		v->push_back(b6);
		v->push_back(b7);
		layouts->push_back(v);
	}*/
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
	std::random_shuffle(v->begin(), (v->end() - 1));
	return v->front();
}
