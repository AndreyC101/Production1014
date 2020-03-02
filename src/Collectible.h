#pragma once
#include "GameObject.h"

class Collectible : public GameObject {
private:
	ActiveState m_active;
public:
	Collectible(vec2 position, ObjectType type);
	~Collectible() {}
	ActiveState GetActiveState() { return m_active; }
	void SetActiveState(ActiveState newState) { m_active = newState; }
	void Update() {}
	void Draw();
	void Clean() {}
};