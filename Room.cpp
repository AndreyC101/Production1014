#include "Room.h"
#include "Game.h"

Room::Room(SDL_Rect triggerBox)
{
	m_outer = triggerBox;
}

Room::~Room()
{
}

GameObjectType Room::m_getType()
{
	return m_type;
}

SDL_Rect * Room::getCollisionType()
{
	return &m_outer;
}

void Room::draw()
{
}

void Room::update()
{
}

void Room::clean()
{
}
