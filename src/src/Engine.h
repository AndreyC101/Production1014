#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <time.h>
#include "FSM.h"

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60

class Engine {
private:
	bool m_bRunning;
	const Uint8* m_iKeystates;
	Uint32 m_start, m_end, m_delta, m_fps;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	FSM* m_pFSM;
	SDL_Point m_mousePosition;
	bool m_MouseDown = 0;
	Engine() : m_bRunning(false), m_mousePosition({ 0,0 }) {}
	bool Init(const char* title, int xposition, int yposition, int width, int height, int flags);
	void Sleep();
	void Wake();
	void Render();
	void Update();
	void HandleEvents();
	void Clean();

public:
	static Engine& Instance() {
		static Engine s_Instance;
		return s_Instance;
	}
	~Engine() { delete m_pFSM; }
	int Run();
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	FSM& GetFSM() { return *m_pFSM; }
	SDL_Point& GetMousePosition() { return m_mousePosition; }
	vec2 GetMouseVector() { return vec2(GetMousePosition().x, GetMousePosition().y); }
	bool GetMouseDown() { return m_MouseDown; }
	void Quit() { m_bRunning = false; }
};