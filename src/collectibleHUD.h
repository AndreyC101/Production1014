#pragma once
#include "GameObject.h"
#include "Collectible.h"
#include "Player.h"

class collectibleHUD : public GameObject {
private:
	ActiveState m_active;
	glm::vec2 lineStart, lineEnd;
	int m_frame,
		m_frameMax,
		m_sprite,
		m_spriteMax;
	int imageOffset = 0;

	Player* playerLine;
	Collectible* m_coll;

public:
	collectibleHUD(Player* player);
	~collectibleHUD() {}
	ActiveState GetActiveState() { return m_active; }
	void SetActiveState(ActiveState newState) { m_active = newState; }
	void Update();
	void Draw();
	void calcPosition();
	void m_animate();
	void setCollectible(Collectible* collectible);
	Collectible* getCollectible();
	void Clean() {}
	void checkBounds();
};