#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Player : public GameObject {
public:
	Player();
	~Player();

	void draw();
	void update();
	void clean();
	void m_move();
	bool m_checkBounds();
	void kill();
	bool heartBeatCheck();
	void getLampPos(int x, int y);
	void drawLamp();
	glm::vec2 mousePos;
	const float lightDistance = 10.0f;
	bool hideCheck();
	void hide();
private:
	bool m_isAlive;
	bool m_isHiding;
	glm::vec2 lampPos = glm::vec2(0, 0);

};


#endif /* defined (__Player__) */