#pragma once
#ifndef __SLUG__
#define __SLUG__

#include "Enemy.h"
#include "Util.h"

class Slug: public Enemy
{
public:
	Slug(const std::vector<glm::vec2> m_Patrol);
	~Slug();

	void draw();
	void moveTowardPoint();


private:
	std::vector<glm::vec2> m_PatrolPoints;

};


#endif /* defined (__SLUG__) */