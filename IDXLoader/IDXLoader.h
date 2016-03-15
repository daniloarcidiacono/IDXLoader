/*  Copyright 2016 Danilo Arcidiacono. All Rights Reserved.
*  This file is part of IDXLoader.
*
*  IDXLoader is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  IDXLoader is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with IDXLoader.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

// Forward declarations
class IDXData;

// IDXLoader instances IDXData reading from file.
//
// The expected file format is as follows:
//
// - Magic Number		(32 bit integer Big Endian)
// - Size in dimension 0 (32 bit integer Big Endian)
//	...
// - Size in dimension N (32 bit integer Big Endian)
// - data
//
// All the integers in the files are stored in the MSB first (high endian) format.
class IDXLoader
{
private:
	char message[1024];
	
public:
	IDXLoader();

	// Loads the IDX file.
	// Returns NULL on error.
	IDXData *load(const char *filename);

	// Get methods
	const char *getMessage() const { return message; }
};