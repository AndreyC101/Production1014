#include "LevelObjects.h"
#include "Engine.h"

void Wall::SetCollider(SDL_Rect bounds)
{
	m_collider = bounds;
}

Wall::Wall(SDL_Rect bounds)
{
	SetCollider(bounds);
}

void Wall::Debug()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &GetCollider());
}

Door::Door(SDL_Rect bounds, int entry, ObjectType type) : Wall(bounds)
{
	SetEntry(entry);
	SetType(type);
	if (GetType() == ALCOVE) SetState(OPEN);
	else SetState(CLOSED);
	switch (entry) {
	case 0: // Entry from above, trigger is near bottom of collider
		SetTrigger(vec2(GetCollider().x + GetCollider().w / 2, GetCollider().y + (GetCollider().h / 4) * 3));
		break;
	case 1: // Entry from below, trigger is near top of collider
		SetTrigger(vec2(GetCollider().x + GetCollider().w / 2, GetCollider().y + GetCollider().h / 4));
		break;
	case 2: // Entry from left, trigger is near right side of collider
		SetTrigger(vec2(GetCollider().x + (GetCollider().w / 4) * 3, GetCollider().y + GetCollider().h / 2));
		break;
	case 3: // Entry from right, trigger is near left side of collider
		SetTrigger(vec2(GetCollider().x + GetCollider().w / 4, GetCollider().y + GetCollider().h / 2));
		break;
	default:
		break;
	}
}

void Door::Debug()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 100);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &GetCollider());
}
