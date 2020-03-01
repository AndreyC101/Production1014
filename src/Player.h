#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
	const float m_lightDistance = 10.0f;
	float m_moveSpeed, m_hideFrames;
	PlayerState m_state;
	vec2 m_newPosition;
	vec2 m_lampPosition;
public:
	Player(PlayerState state);
	~Player() {}
	PlayerState GetState() { return m_state; }
	void SetState(PlayerState newState) { m_state = newState; }
	vec2 GetNewPosition() { return m_newPosition; }
	float GetLightDistance() { return m_lightDistance; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
	float GetHideFrames() { return m_hideFrames; }
	void SetHideFrames(float frames) { m_hideFrames = frames; }
	void CalculateLampPosition();
	void SetNewPosition(vec2 position) { m_newPosition = position; }
	void CalculateNewPositionX();
	void CalculateNewPositionY();
	void MoveX();
	void MoveY();
	void Update();
	void Draw();
	void Clean() {}
};