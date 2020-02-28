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
private:
	bool m_isAlive;

	float m_currentHeading;

	//Animations
	int m_frame,
		m_frameMax,
		m_Sprite,
		m_SpriteMax;

	int imageOffset = 0;
	void m_animate();
};


#endif /* defined (__Player__) */