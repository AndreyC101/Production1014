#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
	const float m_lightDistance = 10.0f;
	float m_moveSpeed;
	PlayerState m_state;
	vec2 m_newPosition;
	vec2 m_lampPosition;
public:
	Player(PlayerState state);
	~Player() {}
	PlayerState GetState() { return m_state; }
	void SetState(PlayerState newState) { m_state = newState; }
	float GetLightDistance() { return m_lightDistance; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
	void CalculateLampPosition();
	void CalculateNewPosition();
	void CheckCollisions();
	void CheckTriggers();
	void Move();
	void Update();
	void Draw();
	void Clean() {}
};