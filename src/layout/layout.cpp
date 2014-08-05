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
		MovementType* m1 = new UpDown(100, 200, 100);
		MovementType* m2 = new UpDown(100, 200, 100);
		DynamicBlock* b1 = new DynamicBlock(80, 25, 180, 100, m1);
		DynamicBlock* b2 = new DynamicBlock(80, 25, 340, 200, m2);
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
