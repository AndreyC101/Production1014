#include "Dog.h"
#include "Engine.h"

Dog::Dog(const std::vector<glm::vec2> m_Patrol) : m_PatrolPoints(m_Patrol)
{
	TextureManager::Instance()->load("../Assets/DogAnim.png", "dog", Engine::Instance().GetRenderer());
	SetPosition(m_Patrol[0]);
	SetCollisionRadius(10);
	glm::vec2 size = TextureManager::Instance()->getTextureSize("dog");
	SetWidth(size.x);
	SetHeight(size.y);
	//setIsColliding(false);
	//SetType(GameObjectType::ENEMY);
	//setState(EnemyState::IDLE);
	setMaxSpeed(2.0f);

	m_currentHeading = 0.0;
	m_turnRate = 5.0f;
	m_currentDirection = glm::vec2(1.0f, 0.0f);
	m_angleToTarget = 0.0f;

	m_frame = 0;
	m_frameMax = 8;
	m_Sprite = 0;
	m_SpriteMax = 6;

	patrolPointIndex = 0;
}

Dog::~Dog()
{
}

void Dog::Draw()
{
	int xComponent = GetPosition().x;
	int yComponent = GetPosition().y;

	TextureManager::Instance()->modifiedDraw("dog", xComponent, yComponent, 6, imageOffset, Engine::Instance().GetRenderer(), m_currentHeading, 255, true);
}


void Dog::moveTowardPoint()
{
	if (patrolPointIndex == m_PatrolPoints.size() - 1)
	{
		patrolPointIndex = 0;
	}

	if (patrolPointIndex <= m_PatrolPoints.size())
	{
		setTargetPosition(m_PatrolPoints[patrolPointIndex]);
		float distance = Util::Distance(GetPosition(), getTargetPosition());
		float radius = 6.0f;
		if (distance < radius)
		{
			SetVelocity(Util::Normalize(getTargetPosition() - GetPosition()) * getMaxSpeed() * (distance / radius));
		}
		else
		{
			//setVelocity(Util::normalize(getTargetPosition() - getPosition()));
		}
		glm::vec2 newPosition = GetPosition() + GetVelocity() * getMaxSpeed();
		SetPosition(newPosition);
	}
}

