#pragma once
#ifndef __CollisionManager__
#define __CollisionManager__

#include <iostream>

#include "GameObject.h"
#include "SDL.h"
#include <GLM/gtx/norm.hpp>
#include "SoundManager.h"
#include <math.h>

class CollisionManager
{
public:
	static int squaredDistance(glm::vec2 P1, glm::vec2 P2);
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);
	static bool CircleToRectCollision(GameObject* ob1, SDL_Rect* ob2);
	static bool CircleToCircleCollistion(GameObject* object1, GameObject* object2);
private:
	CollisionManager();
	~CollisionManager();
};

typedef CollisionManager Collision;

#endif /* defined (__CollisionManager__) */
