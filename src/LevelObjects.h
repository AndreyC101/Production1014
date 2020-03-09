#pragma once
#include "GameObject.h"
#include "Types.h"

class Wall {
private:
	SDL_Rect m_collider;
	ObjectType m_type;
	void SetCollider(SDL_Rect bounds);
public:
	Wall(SDL_Rect bounds);
	~Wall() {}
	SDL_Rect GetCollider() { return m_collider; }
	ObjectType GetType() { return m_type; }
	void SetType(ObjectType newType) { m_type = newType; }
};

class Door : public Wall {
private:
	vec2 m_trigger;
	DoorState m_state;
	int m_entry;
public:
	Door(SDL_Rect bounds, int entry, ObjectType type);
	~Door() {}
	vec2 GetTrigger() { return m_trigger; }
	void SetTrigger(vec2 newTrigger) { m_trigger = newTrigger; }
	DoorState GetState() { return m_state; }
	void SetState(DoorState newState) { m_state = newState; }
	int GetEntry() { return m_entry; }
	void SetEntry(int entry) { m_entry = entry; }
};