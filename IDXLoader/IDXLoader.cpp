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
#include "IDXLoader.h"
#include "IDXData.h"
#include "ByteOrder.h"
#include <string.h>
#include <stdio.h>

IDXLoader::IDXLoader()
{
	strcpy(message, "");
}

static INT read32BE(FILE *f)
{
	// Read 4 bytes
	UBYTE bytes[4];
	fread(bytes, 1, 4, f);

	// Convert from Big Endian
	INT result;
	ByteOrder::BEToHost(result, bytes);

	// Return the result
	return result;
}

IDXData *IDXLoader::load(const char *filename)
{
	strcpy(message, "Ok");

	FILE *f = fopen(filename, "rb");
	if (!f)
	{
		sprintf(message, "Could not open file \"%s\"", filename);
		return NULL;
	}

	// Read the file size first
	fseek(f, 0, SEEK_END);
	const int actualFileSize = ftell(f);

	// Rewind the file pointer
	fseek(f, 0, SEEK_SET);

	// magic number: 4 bytes
	if (actualFileSize < 4)
	{
		sprintf(message, "File size is invalid");
		fclose(f);
		return NULL;
	}

	// Parse the magic number
	UBYTE magicNumberBytes[4];
	fread(magicNumberBytes, 1, 4, f);

	if (magicNumberBytes[0] != 0x00 || magicNumberBytes[1] != 0x00)
	{
		sprintf(message, "Invalid magic number");
		fclose(f);
		return NULL;
	}

	// Determine the data type
	IDXData::DataType dataType;
	switch (magicNumberBytes[2])
	{
		case IDXData::DataType::TYPE_SBYTE: { dataType = IDXData::DataType::TYPE_SBYTE;	break; }
		case IDXData::DataType::TYPE_UBYTE: { dataType = IDXData::DataType::TYPE_UBYTE;	break; }
		case IDXData::DataType::TYPE_INT: { dataType = IDXData::DataType::TYPE_INT;	break; }
		case IDXData::DataType::TYPE_SHORT: { dataType = IDXData::DataType::TYPE_SHORT;	break; }
		case IDXData::DataType::TYPE_FLOAT: { dataType = IDXData::DataType::TYPE_FLOAT;	break; }
		case IDXData::DataType::TYPE_DOUBLE: { dataType = IDXData::DataType::TYPE_DOUBLE; break; }
		default:
		{
			sprintf(message, "Invalid magic number data type");
			fclose(f);
			return NULL;
		}
	}

	// Determine the number of dimensions
	const UBYTE expectedDimensions = magicNumberBytes[3];
	if (expectedDimensions == 0)
	{
		sprintf(message, "Invalid dimensions");
		fclose(f);
		return NULL;
	}

	// Read the size for each dimension
	if (actualFileSize < 4 + 4 * expectedDimensions)
	{
		sprintf(message, "File format is invalid");
		fclose(f);
		return NULL;
	}

	// Read the sizes and also count the elements
	int elementCount = 1;
	int *sizes = new int[expectedDimensions];
	for (int i = 0; i < expectedDimensions; i++)
	{
		sizes[i] = read32BE(f);

		// Sizes for each dimension must be positive
		if (sizes[i] <= 0)
		{
			sprintf(message, "Size %d for dimension %d is invalid", sizes[i], i);
			delete []sizes;
			fclose(f);
			return NULL;
		}

		elementCount *= sizes[i];
	}

	// Compute the size in bytes of the elements
	const int dataSize = elementCount * IDXData::getDataTypeSize(dataType);

	// Compute the expected total file size
	const int expectedFileSize = 4 + 4 * expectedDimensions + dataSize;
	if (actualFileSize != expectedFileSize)
	{
		sprintf(message, "File format is invalid");
		fclose(f);
		delete []sizes;
		return NULL;
	}

	// Read the raw data
	IDXData *ret = new IDXData(dataType, expectedDimensions, sizes);
	fread(ret->getRawBuffer(), 1, dataSize, f);
	
	// Close the file
	fclose(f);

	// Free the temporary objects
	delete []sizes;

	// Success
	return ret;
}