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
#include "IDXData.h"

IDXData::IDXData(const DataType _dataType, const int _dimensions, const int *_sizes)
	: dataType(_dataType), dimensions(_dimensions)
{
	sizes = new int[dimensions];
	for (int i = 0; i < dimensions; i++)
		sizes[i] = _sizes[i];

	data = new unsigned char[getItemByteSize()];
}

IDXData::~IDXData()
{
	delete []data;
	delete []sizes;
}

int IDXData::getDataTypeSize(const DataType &type)
{
	switch (type)
	{
		case TYPE_UBYTE: return 1; break;
		case TYPE_SBYTE: return 1; break;
		case TYPE_SHORT: return 2; break;
		case TYPE_INT: return 4; break;
		case TYPE_FLOAT: return 4; break;
		case TYPE_DOUBLE: return 8; break;
	}

	// Should never reach here
	return -1;
}

int IDXData::getItemByteSize() const
{
	int result = 1;
	for (int i = 0; i < dimensions; i++)
		result *= sizes[i];

	return result * getDataTypeSize(dataType);
}