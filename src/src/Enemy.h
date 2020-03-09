#pragma once
#include<vector>
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(const std::vector<glm::vec2> m_Patrol); //m_SpawnPosition and m_PatrolPoints to be obtained from level manager
	~Enemy();
	void draw();
	void update();
	void clean();
	void move();
	void check_Destination();

	EnemyState getState() { return m_State; }
	void setState(EnemyState newState) { m_State = newState; }
	glm::vec2 getNextPatrolPoint();

	//Getters 
	float getMaxSpeed();
	glm::vec2 getTargetPosition();

	//Setters 
	void setMaxSpeed(float newSpeed);
	void setTargetPosition(glm::vec2 newTargetPosition);


private:
	EnemyState m_State;
	std::vector<glm::vec2> m_PatrolPoints;
	glm::vec2 m_destination;

	int patrolPointIndex = 0;

	//Speed Variables 
	float m_maxSpeed;

	//Target Info
	glm::vec2 m_targetPosition;

};