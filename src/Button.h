#pragma once
#include "GameObject.h"

class Button : public GameObject {
private:
	float m_radius;
	ButtonType m_buttonType;
	ButtonState m_buttonState;
public:
	Button(vec2 position);
	~Button() {}
	ButtonType GetButtonType() { return m_buttonType; }
	void SetButtonType(ButtonType newType) { m_buttonType = newType; }
	ButtonState GetButtonState() { return m_buttonState; }
	void SetButtonState(ButtonState newState) { m_buttonState = newState; }
	virtual void Execute() = 0;
	void Update();
};

class StartButton : public Button {
public:
	StartButton(vec2 position);
	~StartButton() {}
	void Execute();
	void Draw();
	void Clean() {}
};

class ResumeButton : public Button {
public:
	ResumeButton(vec2 position);
	~ResumeButton() {}
	void Execute();
	void Draw();
	void Clean() {}
};

class RestartButton : public Button {
public:
	RestartButton(vec2 position);
	~RestartButton() {}
	void Execute();
	void Draw();
	void Clean() {}
};

class QuitButton : public Button {
public:
	QuitButton(vec2 position);
	~QuitButton() {}
	void Execute();
	void Draw();
	void Clean() {}
};
