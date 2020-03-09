#include <iostream>
#include "Engine.h"

bool Engine::Init(const char* title, int xposition, int yposition, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, xposition, yposition, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				if (IMG_Init(IMG_INIT_PNG) != 0)
				{

				}
				else return false; // Image init fail.
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000);
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_pFSM = new FSM();
	m_pFSM->LoadAssets();
	m_pFSM->ChangeState(new TitleState());
	m_bRunning = true;
	std::cout << "Init success!" << std::endl;
	srand(time(NULL));
	return true;
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Render()
{
	GetFSM().Render();
}

void Engine::Update()
{
	GetFSM().Update();
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				if (m_pFSM->GetStates().back()->GetCurrentState() != PAUSE) {
					m_pFSM->PushState(new PauseState());
				}
				else {
					m_pFSM->PopState();
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button >= 1 && event.button.button <= 3)
				m_MouseDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3)
				m_MouseDown = false;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
			break;
		}
	}
}

void Engine::Clean()
{
	std::cout << "Cleaning game." << std::endl;
	GetFSM().Clean();
	delete m_pFSM;
	m_pFSM = nullptr;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

int Engine::Run()
{
	if (m_bRunning)
		return -1;
	if (Init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning)
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}