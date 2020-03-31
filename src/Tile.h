#pragma once
#ifndef __TILE__
#define __TILE__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "Config.h"
#include "Label.h"
#include "Scene.h"

#include "TileState.h"
#include "TileNeighbour.h"
#include "Heuristic.h"

class Tile final : public DisplayObject
{
public:
	Tile(glm::vec2 world_position = glm::vec2(), glm::vec2 grid_position = glm::vec2());
	~Tile();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// get neighbours
	Tile* getUp();
	Tile* getDown();
	Tile* getRight();
	Tile* getLeft();

	// set neighbours
	void setUp(Tile* tile);
	void setDown(Tile* tile);
	void setRight(Tile* tile);
	void setLeft(Tile* tile);

	void setTileState(TileState state);
	TileState getTileState() const;

	void setTargetDistance(glm::vec2 goal_location);

	glm::vec2 getGridPosition() const;

	float getTileValue() const;
	void setTileValue(float new_value);

	void setTileStateLabel(const std::string& closed_open) const;

	std::vector<Tile*> getNeighbours() const;

	void setHeuristic(Heuristic heuristic);

	void displayTile();

private:
	float m_cost = Config::TILE_COST;
	float m_targetDist = 0.0f;
	float m_tileValue = 0.0f;
	TileState m_tileState;
	glm::vec2 m_gridPosition;

	// labels
	Label* m_pValueLabel;
	Label* m_pClosedOpenLabel;

	glm::vec2 m_goalLocation;
	std::vector<Tile*> m_pNeighbours;
	Heuristic m_heuristic;
};


#endif /* defined (__TILE__) */