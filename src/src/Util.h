#pragma once
#include <math.h>
#include "Player.h"

class Util {
public:
	static bool AABB(SDL_Rect obj1, SDL_Rect obj2);
	static bool CircleCircle(GameObject* obj1, GameObject* obj2);
	static bool CircleRect(GameObject* obj1, SDL_Rect obj2);
	static bool CircleRectExtrapolate(Player* obj1, SDL_Rect obj2);
	static bool PointCircle(vec2 point, GameObject* obj);
	static bool PointCircleExtrapolate(vec2 point, Player* obj);
	static bool PointRect(vec2 point, SDL_Rect obj);
	static float Magnitude(vec2 vector);
	static vec2 Limit(vec2 vector, float magnitude);
	static vec2 Normalize(vec2 vector);
};