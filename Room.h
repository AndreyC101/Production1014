#pragma once
#ifndef __ROOM__
#define __ROOM__


#include "GameObject.h"

class Room : public GameObject
{
public:
	Room(SDL_Rect triggerBox);
	~Room();
	GameObjectType m_getType();
	SDL_Rect * getCollisionType();
	void draw();
	void update();
	void clean();

private:
	SDL_Rect m_outer;
	GameObjectType m_type;
};
#endif // !__ROOM__
