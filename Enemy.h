#pragma once
#ifndef __Enemy__
#define __Enemy__

#include<vector>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

enum EnemyState {
	IDLE,
	PATROL,
	CHASE,
	RETURN,
};

class Enemy : public GameObject {
public:
	//Enemy(const std::vector<glm::vec2> m_Patrol); //m_SpawnPosition and m_PatrolPoints to be obtained from level manager
	Enemy();
	~Enemy();
	virtual void draw();
	void update();
	void clean();

	void move();
	void check_Destination();

	//Movement Functions 
	virtual void moveTowardPoint();
	void turnLeft();
	void turnRight();

	EnemyState getState();
	void setState(EnemyState m_State);
	glm::vec2 getNextPatrolPoint();

	//Getters 
	float getMaxSpeed();
	glm::vec2 getTargetPosition();
	glm::vec2 getCurrentDirection();

	//Setters 
	void setMaxSpeed(float newSpeed);
	void setTargetPosition(glm::vec2 newTargetPosition);
	void setCurrentDirection(glm::vec2 newDirection);


protected:
	EnemyState m_State;
	std::vector<glm::vec2> m_PatrolPoints;
	glm::vec2 m_destination;

	int patrolPointIndex = 0;

	//Speed Variables 
	float m_maxSpeed;

	//Target Info
	glm::vec2 m_targetPosition;
	glm::vec2 m_targetDirection;

	//Movement Variables
	float m_turnRate;
	float m_currentHeading;
	float m_angleToTarget;
	glm::vec2 m_currentDirection;

	//Functions
	void m_changeDirection();
	void m_computeTargetDirection();

	//Animations
	int m_frame,
		m_frameMax,
		m_Sprite,
		m_SpriteMax;

	int imageOffset = 0;
	void m_animate();

};
#endif /* defined (__ENEMY__) */