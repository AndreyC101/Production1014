#include "Player.h"
#include "Game.h"
#include "Wall.h"
#include "Pit.h"
#include "Enemy.h"
#include "Util.h"

Player::Player()
{
	TheTextureManager::Instance()->load("../Assets/textures/player.png", "player", TheGame::Instance()->getRenderer());
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("player");
	TheTextureManager::Instance()->load("../Assets/textures/lampLightTwo.png", "lampLightTwo", TheGame::Instance()->getRenderer());
	glm::vec2 lampSize = TheTextureManager::Instance()->getTextureSize("lampLightTwo");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);
}

Player::~Player()
{
}

void Player::draw()
{
	TheTextureManager::Instance()->draw("player", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Player::update()
{
	/*if (m_checkBounds()) {
		m_move();
	}
	else m_newPosition = getPosition();*/
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

void Player::drawLamp()
{
	TheTextureManager::Instance()->draw("lampLightTwo", lampPos.x, lampPos.y, TheGame::Instance()->getRenderer(), true);
}

void Player::getLampPos(int x, int y)
{
	glm::vec2 spawnPos = glm::vec2(getPosition().x - getWidth() / 2, getPosition().y - getHeight()/2);
	lampPos = spawnPos + (lightDistance * Util::normalize(glm::vec2(x - getPosition().x, y - getPosition().y)));
	std::cout << "lampPos is " << lampPos.x << " " << lampPos.y << std::endl;
	std::cout << "player Pos is " << getPosition().x << " " << getPosition().y << std::endl;
}
