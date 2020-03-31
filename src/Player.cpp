#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player(PlayerState state) {
	SetState(state);
	SetScale(vec2(25.0f, 25.0f));
	SetObjectType(ObjectType::PLAYER);
	SetMoveSpeed(2.5f);
	SetCollisionRadius(12);
	setActive(true);

	m_frame = 0;
	m_frameMax = 8;
	m_Sprite = 0;
	m_SpriteMax = 1;
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
	m_newPosition.x = GetPosition().x + GetVelocity().x * GetMoveSpeed();
	
}
void Player::CalculateNewPositionY()
{
	m_newPosition.y = GetPosition().y + GetVelocity().y * GetMoveSpeed();

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
	CalculateLampPosition();
	SetHideFrames(GetHideFrames() - 1);
	if (GetHideFrames() < 0) SetHideFrames(0);

	//TODO: animation
}

void Player::Draw() {
	switch (getMovementSprite())
	{
	case 1:
		spriteString = "player1";
		break;
	case 2:
		spriteString = "player2";
		break;
	case 3:
		spriteString = "player3";
		break;
	case 4:
		spriteString = "player4";
		break;
	default:
		break;
	}
	TextureManager::Instance()->modifiedDraw(spriteString, GetPosition().x, GetPosition().y, m_SpriteMax, imageOffset, Engine::Instance().GetRenderer(), 0, 255, true);
	TextureManager::Instance()->draw("lamp_light", m_lampPosition.x, m_lampPosition.y, Engine::Instance().GetRenderer(), true);
}