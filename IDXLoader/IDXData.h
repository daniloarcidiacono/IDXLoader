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
#include <stdarg.h>

// Reprsents the data of an IDX file (an n-dimensional matrix).
// (http://yann.lecun.com/exdb/mnist/)
class IDXData
{
public:
	enum DataType { TYPE_UBYTE = 0x08, 
					TYPE_SBYTE = 0x09,
					TYPE_SHORT = 0x0B,
					TYPE_INT = 0x0C,
					TYPE_FLOAT = 0x0D,
					TYPE_DOUBLE = 0x0E };
private:
	// Type of data
	const DataType dataType;

	// Number of dimensions of the data
	const int dimensions;

	// Sizes for each dimension
	/* const */ int *sizes;

	// Raw data
	// The data is stored like in a C array, i.e. the index in the last dimension changes the fastest. 
	unsigned char *data;
	
	// Returns the size in bytes of data, i.e. sizes[0] * ... * sizes[dimensions - 1] * sizeof(dataType)
	int getItemByteSize() const;

public:
	IDXData(const DataType _dataType, const int _dimensions, const int *_sizes);
	virtual ~IDXData();

	// Returns the size in bytes of the given data type
	static int getDataTypeSize(const DataType &type);
	
	// Get methods
	template <class T> T *slice(const int idx0)
	{
		int offset = 1;
		for (int i = 1; i < dimensions; i++)
			offset *= sizes[i];

		return (T *)(data + idx0 * offset);
	}

	template <class T> T *slice(const int idx0, const int idx1)
	{
		int offset = 1;
		for (int i = 2; i < dimensions; i++)
			offset *= sizes[i];

		return (T *)(data + idx0 * (offset * sizes[1]) + idx1 * offset);
	}

	template <class T> T *slice(const int idx0, const int idx1, const int idx2)
	{
		int offset = 1;
		for (int i = 3; i < dimensions; i++)
			offset *= sizes[i];

		return (T *)(data + idx0 * (offset * sizes[1] * sizes[2]) + idx1 * (offset * sizes[2]) + idx2 * offset);
	}

	template <class T> T *slice(const int *idx, const int nIndexes)
	{
		int offset = 1;
		for (int i = nIndexes; i < dimensions; i++)
			offset *= sizes[i];

		unsigned char *ret = data;
		for (int i = nIndexes - 1; i >= 0; i--)
		{
			ret += idx[i] * offset;
			offset *= sizes[i];
		}

		return (T *)ret;
	}

	const DataType &getDataType() const { return dataType; }
	const int getDimensions() const { return dimensions; }
	const int getDimensionSize(const int dimension) { return sizes[dimension]; }
	unsigned char *getRawBuffer() { return data; }
};
