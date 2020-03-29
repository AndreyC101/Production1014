#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Util.h"

Player* Player::s_pInstance;

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
		imageOffset = (GetWidth() / m_SpriteMax) * m_Sprite;
	}
	m_frame++;
}

Player::Player() {
	SetState(PlayerState::INACTIVE);
	SetScale(vec2(25.0f, 25.0f));
	SetObjectType(ObjectType::PLAYER);
	SetMoveSpeed(2.5f);
	SetCollisionRadius(10);

	m_frame = 0;
	m_frameMax = 8;
	m_Sprite = 0;
	m_SpriteMax = 1;
	m_spriteMax2 = 8;
}

void Player::CalculateLampPosition()
{
	m_lampPosition = GetPosition() + (m_lightDistance * Util::Normalize(glm::vec2(Engine::Instance().GetMousePosition().x - GetPosition().x, Engine::Instance().GetMousePosition().y - GetPosition().y)));
	m_lampAngle = Util::SignedAngle(GetPosition(), m_lampPosition);
	//std::cout << "lampPos is " << m_lampPosition.x << " " << m_lampPosition.y << std::endl;
	//std::cout << "player Pos is " << GetPosition().x << " " << GetPosition().y << std::endl;
}

void Player::calcCollectibles()
{
	//glm::vec2 spawnPos = glm::vec2(GetPosition().x - TextureManager::Instance()->getTextureSize("player").x / 2, GetPosition().y - TextureManager::Instance()->getTextureSize("player").y / 2);
	//for (int i = 0; i < numCollectibles; i++)
	//{
	//	collectibleHUD[i] = spawnPos + ((float)1000 * Util::Normalize(glm::vec2(/*vector of collectibles*/));
	//	if (collectibleHUD[i].x < 0)
	//		collectibleHUD[i].x = 0;
	//	if (collectibleHUD[i].y < 0)
	//		collectibleHUD[i].y = 0;
	//	if (collectibleHUD[i].x > WIDTH)
	//		collectibleHUD[i].x = WIDTH;
	//	if (collectibleHUD[i].y > HEIGHT)
	//		collectibleHUD[i].x = HEIGHT;
	//}
}

void Player::CalculateNewPositionX()
{
	m_newPosition.x = GetPosition().x + GetVelocity().x * GetMoveSpeed();
	
}
void Player::CalculateNewPositionY()
{
	m_newPosition.y = GetPosition().y + GetVelocity().y * GetMoveSpeed();

}

void Player::MovementInput()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {
		SetVelocity(GetVelocity() + vec2(0.0f, -1.0f));
		setMovementSprite(1);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		SetVelocity(GetVelocity() + vec2(0.0f, 1.0f));
		setMovementSprite(2);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		SetVelocity(GetVelocity() + vec2(-1.0f, 0.0f));
		setMovementSprite(3);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		SetVelocity(GetVelocity() + vec2(1.0f, 0.0f));
		setMovementSprite(4);
	}
	SetVelocity(Util::Normalize(GetVelocity()));
}

void Player::MoveX()
{
	SetPosition(vec2(GetNewPosition().x, GetPosition().y));
}

void Player::MoveY()
{
	SetPosition(vec2(GetPosition().x, GetNewPosition().y));
}

void Player::Update() {
	if (GetState() == PlayerState::ACTIVE || GetState() == PlayerState::HIDDEN)
	{
		MovementInput();
		CalculateLampPosition();
		if (GetState() == PlayerState::ACTIVE) {
			SetHideFrames(GetHideFrames() - 1);
			if (GetHideFrames() < 0) SetHideFrames(0);
		}
		m_animate();
	}
}

void Player::Draw() {
	if (GetState() == PlayerState::ACTIVE || GetState() == PlayerState::HIDDEN)
	{
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
		TextureManager::Instance()->modifiedDraw("light", GetPosition().x, GetPosition().y, m_spriteMax2, imageOffset, Engine::Instance().GetRenderer(), 0, 200, true);
	}
}