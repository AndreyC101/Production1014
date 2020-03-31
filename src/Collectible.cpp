#include "Collectible.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Util.h"

Collectible::Collectible(vec2 position, ObjectType type)
{
	SetPosition(position);
	SetObjectType(type);
	SetActiveState(ActiveState::ON);
	SetCollisionRadius(Util::Magnitude(TextureManager::Instance()->getTextureSize("bone"))/2);
}

void Collectible::Draw()
{
	if (GetActiveState() == ACTIVE) {
		switch (GetObjectType()) {
		case BONE:
			TextureManager::Instance()->draw("bone", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case RIB:
			TextureManager::Instance()->draw("rib", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case SKULL:
			TextureManager::Instance()->draw("skull", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case DEATHSKULL:
			TextureManager::Instance()->draw("dSkull", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case PRESENTBONE:
			TextureManager::Instance()->draw("pBone", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case FISHBONE:
			TextureManager::Instance()->draw("fishbone", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case CRACKSKULL:
			TextureManager::Instance()->draw("crackskull", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
			break;
		case CROSSBONE:
			TextureManager::Instance()->draw("crossbone", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
		default:
			break;
		}
	}
}
