#pragma once
#ifndef __TileComparators__
#define __TileComparators__

#include "Tile.h"

class ComparatorByValue
{
public:
	bool operator() (Tile * tile_a, Tile * tile_b) const
	{
		if(tile_a != nullptr)
		{
			if(tile_b != nullptr)
			{
				return tile_a->getTileValue() < tile_b->getTileValue();
			}

			return true;
		}
		return false;
	}
};

#endif /* defined (__TileComparators__) */
