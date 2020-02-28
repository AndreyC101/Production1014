#pragma once
#ifndef __DOG__
#define __DOG__
#include <string>
#include "Enemy.h"
#include "Util.h"


class Dog : public Enemy
{
public:
	Dog(const std::vector<glm::vec2> m_Patrol);
	~Dog();

	void draw();
	void moveTowardPoint();
	

private:
	std::vector<glm::vec2> m_PatrolPoints;

};



#endif /* defined (__DOG__) */