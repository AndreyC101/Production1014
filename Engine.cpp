#include "Engine.h"
#include "CollisionManager.h"
#include "DebugManager.h"
#include "EventManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include <iostream>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine():m_running(false){ cout << "Engine class constructed!" << endl; }

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				EVMA::Init();
				SOMA::Init();
				TEMA::Init();
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	// Example specific initialization.
	void GameState::Enter ();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // Call this before any textures are created.
	m_pFSM = new StateManager();
	m_pFSM->PushState(new MenuState);
	TEMA::RegisterTexture("Img/PlayerShip.png", "player");
	TEMA::RegisterTexture("Img/Enemies.png", "enemy");
	m_pTarget = new Sprite({ 594,270,36,36 }, { width / 2.0f, height / 2.0f, 36.0f, 36.0f }, m_pRenderer, TEMA::GetTexture("player"));
	m_pEnemy = new Enemy({ 160,0,40,57 }, { 100.0f, 100.0f, 40.0f, 57.0f }, m_pRenderer, TEMA::GetTexture("enemy"), 4, 4, 4, m_pTarget->GetDstP());
	m_obstacles.push_back(new Sprite({ 282, 212, 61, 66 }, { 256, 256, 61, 66 }, m_pRenderer, TEMA::GetTexture("enemy")));
	m_obstacles.push_back(new Sprite({ 282, 212, 61, 66 }, { 768, 512, 61, 66 }, m_pRenderer, TEMA::GetTexture("enemy")));
	SOMA::Load("Aud/engines.wav", "engine", SOUND_SFX);
	SOMA::SetSoundVolume(32, 0);
	

void Engine::Render() 
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Draw anew.
	m_pTarget->Render();
	m_pEnemy->Render();
	for (unsigned i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->Render();
	SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	delete m_pTarget;
	delete m_pEnemy;
	for (unsigned i = 0; i < m_obstacles.size(); i++)
	{
		delete m_obstacles[i];
		m_obstacles[i] = nullptr; // Wrangle your dangle.
	}
	m_obstacles.clear();
	m_obstacles.shrink_to_fit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	DEMA::Quit();
	EVMA::Quit();
	FOMA::Quit();
	SOMA::Quit();
	STMA::Quit();
	TEMA::Quit();
	IMG_Quit();
	SDL_Quit();
}

int Engine::Run()
{
	if (m_running) // What does this do and what can it prevent?
		return -1; 
	if (Init("GAME1017 Engine Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_running) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_running)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }
bool& Engine::Running() { return m_running; }
std::vector<Sprite*>& Engine::GetObs() { return m_obstacles; }
