#pragma once
#include <math.h>
#include "Player.h"

class Util {
public:

	static const float EPSILON;
	static const float Deg2Rad;
	static const float Rad2Deg;

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

	static float Dot(glm::vec2 lhs, glm::vec2 rhs);
	static float Clamp(float value, float min, float max);
	static float Sign(float value);
	static float Angle(glm::vec2 from, glm::vec2 to);
	static float SignedAngle(glm::vec2 from, glm::vec2 to);
	static float Distance(glm::vec2 vecA, glm::vec2 vecB);
};