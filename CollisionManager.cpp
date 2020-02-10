#include "CollisionManager.h"

int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject* object1, GameObject* object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getCollisionRadius() + object2->getCollisionRadius()) * 0.5;

	if (glm::distance(P1, P2) < halfHeights) {
		if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
			if (!object2->getIsColliding()) {
				object2->setIsColliding(true);
				return true;
			}
			return false;
		}
	}
}

bool CollisionManager::CircleToRectCollision(GameObject* ob1, SDL_Rect* ob2)
{
	float testX = ob1->getNewPosition().x, testY = ob1->getNewPosition().y, distanceX, distanceY, distance;
	if (ob1->getNewPosition().x < ob2->x)
	{
		testX = ob2->x;
	}
	else if (ob1->getNewPosition().x > ob2->x + ob2->w)
	{
		testX = ob2->x + ob2->w;
	}
	if (ob1->getNewPosition().y < ob2->y)
	{
		testY = ob2->y;
	}
	else if (ob1->getNewPosition().y > ob2->y + ob2->h)
	{
		testY = ob2->y + ob2->h;
	}


	distanceX = ob1->getNewPosition().x - testX;
	distanceY = ob1->getNewPosition().y - testY;
	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= ob1->getCollisionRadius())
	{
		return true;
	}
	return false;
}

bool CollisionManager::CircleToCircleCollistion(GameObject* object1, GameObject* object2)
{
	if (sqrt((object2->getPosition().x - object1->getPosition().x) * (object2->getPosition().x - object1->getPosition().x) + (object2->getPosition().y - object1->getPosition().y) * (object2->getPosition().y - object1->getPosition().y)) < (object1->getCollisionRadius() + object2->getCollisionRadius())) {
		return true;
	}
	return false;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
