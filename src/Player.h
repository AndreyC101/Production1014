#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
	Player();
	~Player() {}
	static Player* s_pInstance;
	const float m_lightDistance = 50.0f;
	float m_moveSpeed, m_hideFrames;
	PlayerState m_state;
	vec2 m_newPosition;
	vec2 m_lampPosition;
	double m_lampAngle;
	int m_frame,
		m_frameMax,
		m_Sprite,
		m_SpriteMax,
		m_spriteMax2;
	int imageOffset = 0;
	string spriteString;
	string spriteStringTwo;
	int m_movementSprite = 4;
	int m_lightSprite = 8;
	void m_animate();
	bool m_lightActive;
public:
	static Player* Instance() {
		if (s_pInstance == nullptr){
			s_pInstance = new Player();
			return s_pInstance;
		}
		return s_pInstance;
	}
 	PlayerState GetState() { return m_state; }
	void SetState(PlayerState newState) { m_state = newState; }
	vec2 GetNewPosition() { return m_newPosition; }
	float GetLightDistance() { return m_lightDistance; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveSpeed(float speed) { m_moveSpeed = speed; }
	float GetHideFrames() { return m_hideFrames; }
	void SetHideFrames(float frames) { m_hideFrames = frames; }
	void CalculateLampPosition();
	void calcCollectibles();
	void SetNewPosition(vec2 position) { m_newPosition = position; }
	void CalculateNewPositionX();
	void CalculateNewPositionY();
	void setMovementSprite(int spriteNum) { m_movementSprite = spriteNum; }
	int getMovementSprite() { return m_movementSprite; }
	void setLightSprite(int spriteNum) { m_lightSprite = spriteNum;  }
	int getLightSprite() { return m_lightSprite; }
	void MovementInput();
	bool GetLightActive() { return m_lightActive; }
	void SetLightActive(bool active) { m_lightActive = active; }
	void MoveX();
	void MoveY();
	void Update();
	void Draw();
	void Clean() {}

	/*std::vector<glm::vec2> collectibleHUD;
	std::vector<Collectible*>* m_collectibles;
	int numCollectibles;*/
};