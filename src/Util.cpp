#include "Util.h"
#include "GLM/gtc/constants.hpp"
#include "GLM/gtx/norm.hpp"

const float Util::EPSILON = glm::epsilon<float>();
const float Util::Deg2Rad = glm::pi<float>() / 180.0f;
const float Util::Rad2Deg = 180.0f / glm::pi<float>();

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

float Util::Sign(float value)
{
	return (value < 0.0f) ? -1.0f : 1.0f;
}

float Util::Distance(glm::vec2 vecA, glm::vec2 vecB)
{
	float x = vecB.x - vecA.x;
	float y = vecB.y - vecA.y;
	return sqrt((x * x) + (y * y));
}

float Util::Clamp(float value, float min, float max)
{
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
	return value;
}

float Util::Dot(glm::vec2 lhs, glm::vec2 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Util::Angle(glm::vec2 from, glm::vec2 to)
{
	return acos(Util::Clamp(Util::Dot(Util::Normalize(from), Util::Normalize(to)), -1.0f, 1.0f)) * 57.29578f;
}

float  Util::SignedAngle(glm::vec2 from, glm::vec2 to)
{
	float unsigned_angle = Util::Angle(from, to);
	float sign = Util::Sign(from.x * to.y - from.y * to.x);
	return unsigned_angle * sign;
}

void Util::DrawLine(glm::vec2 start, glm::vec2 end, glm::vec4 colour)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	auto renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawRect(glm::vec2 position, int width, int height, glm::vec4 colour)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	SDL_Rect rectangle;
	rectangle.x = position.x;
	rectangle.y = position.y;
	rectangle.w = width;
	rectangle.h = height;

	auto renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCircle(glm::vec2 centre, int radius, glm::vec4 colour, ShapeType type)
{
	int r = floor(colour.r * 255.0f);
	int g = floor(colour.g * 255.0f);
	int b = floor(colour.b * 255.0f);
	int a = floor(colour.a * 255.0f);

	auto renderer = Engine::Instance().GetRenderer();

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	int diameter = floor(radius * 2.0f);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		switch (type)
		{
		case SEMI_CIRCLE_TOP:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			break;
		case SEMI_CIRCLE_BOTTOM:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y); // bottom left
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x); // bottom right
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x); // bottom left
			break;
		case SEMI_CIRCLE_LEFT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		case SEMI_CIRCLE_RIGHT:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			break;
		case SYMMETRICAL:
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
			SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
			SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);
			break;
		}


		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Util::DrawCapsule(glm::vec2 position, int width, int height, glm::vec4 colour)
{
	int diameter;
	int radius;
	int halfWidth = floor(width * 0.5f);
	int halfHeight = floor(height * 0.5f);
	if (width > height)
	{
		// Horizontal Capsule
		diameter = height;
		radius = halfHeight * 0.5f;
		DrawCircle(glm::vec2(position.x - halfWidth + halfHeight, position.y), halfHeight, colour, SEMI_CIRCLE_LEFT);
		DrawCircle(glm::vec2(position.x + halfWidth - halfHeight, position.y), halfHeight, colour, SEMI_CIRCLE_RIGHT);
		DrawLine(glm::vec2(position.x - halfWidth + halfHeight, position.y - halfHeight), glm::vec2(position.x + halfWidth - halfHeight, position.y - halfHeight));
		DrawLine(glm::vec2(position.x - halfWidth + halfHeight, position.y + halfHeight), glm::vec2(position.x + halfWidth - halfHeight, position.y + halfHeight));
	}
	else if (width < height)
	{
		// Vertical Capsule
		diameter = width;
		radius = halfWidth * 0.5f;
		DrawCircle(glm::vec2(position.x, position.y - halfHeight + radius), radius, colour, SEMI_CIRCLE_TOP);
		DrawCircle(glm::vec2(position.x, position.y + halfHeight - radius), radius, colour, SEMI_CIRCLE_BOTTOM);
		DrawLine(glm::vec2(position.x - radius, position.y - halfHeight + radius), glm::vec2(position.x - halfWidth * 0.5f, position.y + halfHeight * 0.5f));
		DrawLine(glm::vec2(position.x + radius, position.y - halfHeight + radius), glm::vec2(position.x + halfWidth * 0.5f, position.y + halfHeight * 0.5f));
	}
	else
	{
		// Circle
		diameter = floor(height * 2.0f);
		radius = width;
		DrawCircle(position, radius = halfWidth, colour);
	}
}
