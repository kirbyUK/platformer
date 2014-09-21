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
#include "lockfile.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef LOCKFILE
	#define LOCKFILE = "lockfile"
#endif

const char* LOCKFILE_PATH = LOCKFILE;

bool createLockfile()
{
	//Check if the lockfile doesn't exist, and make it if so:
	struct stat buffer;
	if(stat(LOCKFILE, &buffer) != 0)
	{
		std::ofstream out(LOCKFILE);
		if(! out)
		{
			std::cerr << "Cannot write to '" << LOCKFILE << "'\n";
			return false;
		}
		out << "lock" << std::endl;
		out.close();
		return true;
	}
	else
	{
		std::cerr << "'platformer' is already running.\n";
		return false;
	}
}

bool removeLockfile()
{
	//Attempt to delete the lockfile:
	return (std::remove(LOCKFILE) == 0);
}
