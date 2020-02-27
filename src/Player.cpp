#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"

Player::Player(PlayerState state) {
	SetState(state);
	SetScale(vec2(30.0f, 30.0f));
	SetObjectType(ObjectType::PLAYER);
	SetMoveSpeed(3.5f);
	SetCollisionRadius(15);
}

void Player::CalculateLampPosition()
{
}

void Player::CalculateNewPosition()
{
	m_newPosition = vec2(GetPosition().x + GetVelocity().x, GetPosition().y + GetVelocity().y);
}

void Player::CheckCollisions()
{
}

void Player::CheckTriggers()
{
}

void Player::Move()
{
}

void Player::Update() {
	CalculateNewPosition();
	CheckTriggers();
}

void Player::Draw() {
	TextureManager::Instance()->draw("player", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
}