#include "Button.h"
#include "Util.h"
#include "Engine.h"
#include "TextureManager.h"
#include <iostream>

Button::Button(vec2 position)
{
	SetPosition(position);
	SetButtonType(ButtonType::NONE);
}

void Button::Update()
{
	if (this != nullptr) {
		if (Util::PointCircle(Engine::Instance().GetMouseVector(), this)) {
			cout << "Collision Detected" << endl;
			SetButtonState(SELECTED);
			if (Engine::Instance().GetMouseDown()) {
				Execute();
			}
		}
		else SetButtonState(IDLE);
	}
}

StartButton::StartButton(vec2 position) : Button(position)
{
	SetCollisionRadius(TextureManager::Instance()->getTextureSize("start_button").x / 2); // collision radius is width of texture / 2
	SetButtonType(START);
}

void StartButton::Execute()
{
	//TODO: play button press sounds effect
	Engine::Instance().GetFSM().ChangeState(new PlayState);
}

void StartButton::Draw()
{
	//TODO: check state, draw relevant png
	TextureManager::Instance()->draw("start_button", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
}

RestartButton::RestartButton(vec2 position) : Button(position) 
{
	SetCollisionRadius(TextureManager::Instance()->getTextureSize("restart_button").x / 2);
	SetButtonType(RESTART);
}

void RestartButton::Execute()
{
	//TODO: play button press sound effect
	Engine::Instance().GetFSM().ChangeState(new PlayState);
}

void RestartButton::Draw()
{
	//TODO: check state, draw relevant png
	TextureManager::Instance()->draw("restart_button", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
}

QuitButton::QuitButton(vec2 position) : Button(position)
{
	SetCollisionRadius(TextureManager::Instance()->getTextureSize("quit_button").x / 2);
	SetButtonType(QUIT);
}

void QuitButton::Execute()
{
	//TODO: play button press sound effect
	Engine::Instance().Quit();
}

void QuitButton::Draw()
{
	//TODO: check state, draw relevant png
	TextureManager::Instance()->draw("quit_button", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
}

ResumeButton::ResumeButton(vec2 position) : Button(position)
{
	SetCollisionRadius(TextureManager::Instance()->getTextureSize("restart_button").x / 2);
	SetButtonType(RESUME);
}

void ResumeButton::Execute()
{
	//TODO: play button press sound effect
	Engine::Instance().GetFSM().PopState();
}

void ResumeButton::Draw()
{
	//TODO: check state, draw relevant png
	TextureManager::Instance()->draw("start_button", GetPosition().x, GetPosition().y, Engine::Instance().GetRenderer(), true);
}
