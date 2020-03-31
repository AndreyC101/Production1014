#pragma once
#ifndef __TILE_STATE__
#define __TILE_STATE__
enum TileState {
	NO_PATH,
	OPEN,
	CLOSED,
	START,
	GOAL,
	UNVISITED,
	IMPASSABLE,
	NUM_OF_TILE_STATES
};
#endif /* defined (__TILE_STATE__) */