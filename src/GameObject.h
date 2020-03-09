#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include "Types.h"
#include "SimpleStates.h"

using namespace std;
using namespace glm;

class GameObject {
private:
	vec2 m_position;
	vec2 m_velocity;
	vec2 m_rotation;
	vec2 m_scale;
	ObjectType m_type;
	float m_collisionRadius;
	int m_width;
	int m_height;
public:
	GameObject();
	~GameObject() {}
	vec2 GetPosition() { return m_position; }
	void SetPosition(vec2 newPosition) { m_position = newPosition; }
	vec2 GetVelocity() { return m_velocity; }
	void SetVelocity(vec2 newVelocity) { m_velocity = newVelocity; }
	vec2 GetRotation() { return m_rotation; }
	void SetRotation(vec2 newRotation) { m_rotation = newRotation; }
	vec2 GetScale() { return m_scale; }
	void SetScale(vec2 newScale) { m_scale = newScale; }
	ObjectType GetObjectType() { return m_type; }
	void SetObjectType(ObjectType type) { m_type = type; }
	float GetCollisionRadius() { return m_collisionRadius; }
	void SetCollisionRadius(float radius) { m_collisionRadius = radius; }
	int GetWidth() { return m_width; };
	int GetHeight() { return m_height; };
	void SetWidth(int newWidth) { m_width = newWidth; };
	void SetHeight(int newHeight) { m_height = newHeight; };
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
};