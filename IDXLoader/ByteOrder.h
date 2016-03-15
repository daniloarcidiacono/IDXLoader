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
#include "PrimitiveTypes.h"

class ByteOrder
{
public:
	// Big Endian -> Host
	static void BEToHost(SHORT &dst, const UBYTE src[2]);
	static void BEToHost(INT &dst, const UBYTE src[4]);
	static void BEToHost(FLOAT &dst, const UBYTE src[4]);
	//static void BEToHost(DOUBLE &dst, const UBYTE src[8]);
};
