#include "Collectible.h"
#include "Engine.h"
#include "TextureManager.h"
#include "Util.h"

Collectible::Collectible(vec2 position, ObjectType type)
{
	SetPosition(position);
	SetObjectType(type);
	SetActiveState(ActiveState::ACTIVE);
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
		default:
			break;
		}
	}
}
