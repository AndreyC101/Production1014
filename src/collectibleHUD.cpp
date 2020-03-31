#include "collectibleHUD.h"
#include "Engine.h"
#include "Util.h"
#include "TextureManager.h"

collectibleHUD::collectibleHUD(Player* player)
{
	m_frame = 0;
	m_frameMax = 8;
	m_sprite = 0;
	m_spriteMax = 8;

	playerLine = player;
}

void collectibleHUD::Update()
{
	calcPosition();
	checkBounds();
	m_animate();
}

void collectibleHUD::Draw()
{
	TextureManager::Instance()->modifiedDraw("HUDlight", GetPosition().x, GetPosition().y, m_spriteMax, imageOffset, Engine::Instance().GetRenderer(), 0, 200, true);

	//TextureManager::Instance()->draw("HUDlight", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
	cout << "drawing HUD" << endl;
}

void collectibleHUD::calcPosition()
{
	SetPosition(playerLine->GetPosition() + ((float)100 * Util::Normalize(glm::vec2(getCollectible()->GetPosition().x - playerLine->GetPosition().x, getCollectible()->GetPosition().y - playerLine->GetPosition().y))));
	cout << "position on x is " << GetPosition().x;
	cout << "position on Y is " << GetPosition().y;
}

void collectibleHUD::m_animate()
{
	if (m_frame == m_frameMax)
	{
		m_frame = 0;
		m_sprite++;
		if (m_sprite == m_spriteMax)
		{
			m_sprite = 0;
		}
		imageOffset = (32 / m_spriteMax) * m_sprite;
	}
	m_frame++;
}

void collectibleHUD::setCollectible(Collectible * collectible)
{
	m_coll = collectible;
}

Collectible* collectibleHUD::getCollectible()
{
	return m_coll;
}

void collectibleHUD::checkBounds()
{
	if (GetPosition().x < 0)
		SetPosition(glm::vec2(32, GetPosition().y));
	if (GetPosition().x > WIDTH)
		SetPosition(glm::vec2((WIDTH - 32), GetPosition().y));
	if (GetPosition().y < 0)
			SetPosition(glm::vec2(GetPosition().x, 32));
	if (GetPosition().y > HEIGHT)
		SetPosition(glm::vec2(GetPosition().x, HEIGHT - 32));
}