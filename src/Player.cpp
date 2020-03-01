#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player(PlayerState state) {
	SetState(state);
	SetScale(vec2(30.0f, 30.0f));
	SetObjectType(ObjectType::PLAYER);
	SetMoveSpeed(3.5f);
	SetCollisionRadius(15);
}

void Player::CalculateLampPosition()
{
	glm::vec2 spawnPos = glm::vec2(GetPosition().x - TextureManager::Instance()->getTextureSize("player").x / 2, GetPosition().y - TextureManager::Instance()->getTextureSize("player").y / 2);
	m_lampPosition = spawnPos + (m_lightDistance * Util::Normalize(glm::vec2(Engine::Instance().GetMousePosition().x - GetPosition().x, Engine::Instance().GetMousePosition().y - GetPosition().y)));
	std::cout << "lampPos is " << m_lampPosition.x << " " << m_lampPosition.y << std::endl;
	std::cout << "player Pos is " << GetPosition().x << " " << GetPosition().y << std::endl;
}

void Player::CalculateNewPositionX()
{
	m_newPosition.x = GetPosition().x + GetVelocity().x;
	
}
void Player::CalculateNewPositionY()
{
	m_newPosition.y = GetPosition().y + GetVelocity().y;

}

void Player::MoveX()
{
	SetPosition(vec2(m_newPosition.x, GetPosition().y));
}

void Player::MoveY()
{
	SetPosition(vec2(GetPosition().x, m_newPosition.y));
}

void Player::Update() {
	SetHideFrames(GetHideFrames() - 1);
	if (GetHideFrames() < 0) SetHideFrames(0);

	//TODO: animation
}

void Player::Draw() {
	TextureManager::Instance()->draw("player", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
	TextureManager::Instance()->draw("lamp", m_lampPosition.x, m_lampPosition.y, Engine::Instance().GetRenderer(), true);
}