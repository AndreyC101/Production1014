#include "Enemy.h"
#include "Game.h"
#include "Util.h"

Enemy::Enemy(const std::vector<glm::vec2> m_Patrol) : m_PatrolPoints(m_Patrol){
	TheTextureManager::Instance()->load("../Assets/textures/dog.png", "enemy", TheGame::Instance()->getRenderer());
	setPosition(m_Patrol[0]);
	setCollisionRadius(10);
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
	setState(EnemyState::IDLE);

	setMaxSpeed(2.0f);
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Enemy::update()
{
	move();
	check_Destination();
}

void Enemy::move() 
{
	if (patrolPointIndex <= m_PatrolPoints.size())
	{
		setTargetPosition(m_PatrolPoints[patrolPointIndex]);

		float distance = Util::distance(getPosition(), getTargetPosition());
		float radius = 6.0f;

		if (distance < radius)
		{
			setVelocity(Util::normalize(getTargetPosition() - getPosition()) * getMaxSpeed() * (distance / radius));
		}
		else
		{
			setVelocity(Util::normalize(getTargetPosition() - getPosition()));
		}

		glm::vec2 newPosition = getPosition() + getVelocity() * getMaxSpeed();
		setPosition(newPosition);
	}
}

void Enemy::check_Destination()
{
	if (patrolPointIndex < m_PatrolPoints.size() -1)
	{
		if (getPosition() == getTargetPosition())
		{
			patrolPointIndex++;
		}
	}
	
	else
	{
		patrolPointIndex = 0;
	}
}

void Enemy::clean()
{
}

float Enemy::getMaxSpeed()
{
	return m_maxSpeed;
}

glm::vec2 Enemy::getTargetPosition()
{
	return m_targetPosition;
}

void Enemy::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Enemy::setTargetPosition(glm::vec2 newTargetPosition)
{
	m_targetPosition = newTargetPosition;
}


EnemyState Enemy::getState() {
	return m_State;
}

void Enemy::setState(EnemyState m_State) {
	this->m_State = m_State;
}


