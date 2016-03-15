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
#include "ByteOrder.h"
#include <string.h>

// Big Endian -> Host
void ByteOrder::BEToHost(SHORT &dst, const UBYTE src[2])
{
	dst = ((SHORT)src[1]) | ((SHORT)src[0] << 8);
}

void ByteOrder::BEToHost(INT &dst, const UBYTE src[4])
{
	dst = ((INT)src[3]) |
		  ((INT)src[2] << 8) |
		  ((INT)src[1] << 16) |
		  ((INT)src[0] << 24);
}

void ByteOrder::BEToHost(FLOAT &dst, const UBYTE src[4])
{
	INT v;
	BEToHost(v, src);
	memcpy((SBYTE *)&dst, &v, 4);
	//dst = *(FLOAT*)&v; (will break Strict Aliasing Rules)
}

/*
void ByteOrder::BEToHost(DOUBLE &dst, const UBYTE src[8])
{
	unsigned long long v;
	BEToHost(v, src);
	memcpy((SBYTE *)&dst, &v, 8);
}
*/