#include "Player.h"
#include "Game.h"
#include "Wall.h"
#include "Pit.h"
#include "Enemy.h"

Player::Player()
{
	TheTextureManager::Instance()->load("../Assets/textures/Bob_M3.png", "player", TheGame::Instance()->getRenderer());
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);

	m_currentHeading = 0.0;

	m_frame = 0;
	m_frameMax = 8;
	m_Sprite = 0;
	m_SpriteMax = 6;
}

Player::~Player()
{
}

void Player::draw()
{
	TheTextureManager::Instance()->modifiedDraw("player", getPosition().x, getPosition().y, 6, imageOffset, TheGame::Instance()->getRenderer(), m_currentHeading, 255, true);
}

void Player::update()
{
	m_animate();
}

void Player::m_animate()
{
	if (m_frame == m_frameMax)
	{
		m_frame = 0;
		m_Sprite++;
		if (m_Sprite == m_SpriteMax)
		{
			m_Sprite = 0;
		}
		imageOffset = (getWidth() / m_SpriteMax) * m_Sprite;
	}
	m_frame++;

}

void Player::clean()
{
}

void Player::m_move()
{ 
	setPosition(getNewPosition());
}

bool Player::m_checkBounds()
{
	return true;
}

void Player::kill()
{
	m_isAlive = false;
}

bool Player::heartBeatCheck()
{
	return m_isAlive;
}
