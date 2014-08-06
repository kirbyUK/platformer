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
#ifndef LAYOUT_H
#define LAYOUT_H
#include <vector>
#include "../block/block.h"

//All the layouts are predifined, this returns them all in a vector:
std::vector <std::vector <Block*>* >* initLayouts();

//Cleans up by deleting everything made in 'initLayouts()':
void cleanup(std::vector <std::vector <Block*>* >*);

//Shuffles the layouts to generate a new one:
std::vector <Block*>* shuffleLayouts(std::vector <std::vector <Block*>* >*);

#endif
