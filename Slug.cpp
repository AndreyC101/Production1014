#include "Slug.h"
#include "Game.h"

Slug::Slug(const std::vector<glm::vec2> m_Patrol) : m_PatrolPoints(m_Patrol)
{
	TheTextureManager::Instance()->load("../Assets/textures/Slug_Crawl.png", "slug", TheGame::Instance()->getRenderer());
	setPosition(m_Patrol[0]);
	setCollisionRadius(10);
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("slug");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
	setState(EnemyState::IDLE);
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


Slug::~Slug()
{
}

void Slug::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->modifiedDraw("slug", xComponent, yComponent, 6, imageOffset, TheGame::Instance()->getRenderer(), m_currentHeading, 255, true);
}

void Slug::moveTowardPoint()
{
	if (patrolPointIndex == m_PatrolPoints.size() - 1)
	{
		patrolPointIndex = 0;
	}

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
			//setVelocity(Util::normalize(getTargetPosition() - getPosition()));
		}
		glm::vec2 newPosition = getPosition() + getVelocity() * getMaxSpeed();
		setPosition(newPosition);
	}
}