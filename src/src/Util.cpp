#include "Util.h"

bool Util::AABB(SDL_Rect obj1, SDL_Rect obj2)
{
	if (
		obj1.x < obj2.x + obj1.w &&
		obj1.x + obj1.w > obj2.x&&
		obj1.y < obj2.y + obj2.h &&
		obj1.y + obj1.h > obj2.y
		) {
		return true;
	}
	return false;
}

bool Util::CircleCircle(GameObject* obj1, GameObject* obj2)
{
	if (sqrt((obj2->GetPosition().x - obj1->GetPosition().x) * (obj2->GetPosition().x - obj1->GetPosition().x) + (obj2->GetPosition().y - obj1->GetPosition().y) * (obj2->GetPosition().y - obj1->GetPosition().y)) < (obj1->GetCollisionRadius() + obj2->GetCollisionRadius())) {
		return true;
	}
	return false;
}

bool Util::CircleRect(GameObject* obj1, SDL_Rect obj2)
{
	float testX = obj1->GetPosition().x, testY = obj1->GetPosition().y, distanceX, distanceY, distance;
	if (obj1->GetPosition().x < obj2.x)
	{
		testX = obj2.x;
	}
	else if (obj1->GetPosition().x > obj2.x + obj2.w)
	{
		testX = obj2.x + obj2.w;
	}
	if (obj1->GetPosition().y < obj2.y)
	{
		testY = obj2.y;
	}
	else if (obj1->GetPosition().y > obj2.y + obj2.h)
	{
		testY = obj2.y + obj2.h;
	}

	distanceX = obj1->GetPosition().x - testX;
	distanceY = obj1->GetPosition().y - testY;
	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= obj1->GetCollisionRadius())
	{
		return true;
	}
	return false;
}

bool Util::CircleRectExtrapolate(Player* obj1, SDL_Rect obj2)
{
	float testX = obj1->GetNewPosition().x, testY = obj1->GetNewPosition().y, distanceX, distanceY, distance;
	if (obj1->GetNewPosition().x < obj2.x)
	{
		testX = obj2.x;
	}
	else if (obj1->GetNewPosition().x > obj2.x + obj2.w)
	{
		testX = obj2.x + obj2.w;
	}
	if (obj1->GetNewPosition().y < obj2.y)
	{
		testY = obj2.y;
	}
	else if (obj1->GetNewPosition().y > obj2.y + obj2.h)
	{
		testY = obj2.y + obj2.h;
	}

	distanceX = obj1->GetNewPosition().x - testX;
	distanceY = obj1->GetNewPosition().y - testY;
	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= obj1->GetCollisionRadius())
	{
		return true;
	}
	return false;
}

bool Util::PointCircle(vec2 point, GameObject* obj)
{
	if (sqrt((point.x - obj->GetPosition().x) * (point.x - obj->GetPosition().x) + (point.y - obj->GetPosition().y) * (point.y - obj->GetPosition().y)) < (obj->GetCollisionRadius())) {
		return true;
	}
	return false;
}

bool Util::PointCircleExtrapolate(vec2 point, Player* obj)
{
	if (sqrt((point.x - obj->GetNewPosition().x) * (point.x - obj->GetNewPosition().x) + (point.y - obj->GetNewPosition().y) * (point.y - obj->GetNewPosition().y)) < (obj->GetCollisionRadius())) {
		return true;
	}
	return false;
}

bool Util::PointRect(vec2 point, SDL_Rect obj)
{
	if (point.x < (obj.x + obj.w) && point.x > obj.x &&
		point.y < (obj.y + obj.h) && point.y > obj.y) {
		return true;
	}
	return false;
}

float Util::Magnitude(vec2 vector)
{
	float x = vector.x;
	float y = vector.y;
	return sqrt((x * x) + (y * y));
}

vec2 Util::Limit(vec2 vector, float magnitude)
{
	float length = Util::Magnitude(vector);

	if (length > magnitude) {
		float limiter = magnitude / length;
		vector.x *= limiter;
		vector.y *= limiter;
		return vector;
	}
	else {
		return vector;
	}
}

vec2 Util::Normalize(vec2 vector)
{
	vec2 normalized;
	float x = vector.x;
	float y = vector.y;
	float length = (x * x) + (y * y);
	if (length > 0) {
		length = 1.0 / sqrt(length);
		normalized.x = vector.x * length;
		normalized.y = vector.y * length;
	}
	return normalized;
}
