#include "Game.h"
#include<iostream>

Game* Game::s_pInstance = 0;

SDL_Renderer * Game::getRenderer()
{
	return m_pRenderer;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::createGameObjects()
{
	m_pLevel = new Level(0);
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour
	m_pLevel->draw(m_pRenderer);

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	m_pLevel->update();
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;
	m_pLevel->clearLevel();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				m_bRunning = false;
				break;
			case SDLK_w:
				m_pLevel->getPlayer()->setVelocity(glm::vec2((m_pLevel->getPlayer())->getVelocity().x, -1.0f));
				break;
			case SDLK_s:
				(m_pLevel->getPlayer())->setVelocity(glm::vec2((m_pLevel->getPlayer())->getVelocity().x, 1.0f));
				break;

			case SDLK_a:
				(m_pLevel->getPlayer())->setVelocity(glm::vec2(-1.0f, (m_pLevel->getPlayer())->getVelocity().y));
				break;
			case SDLK_d:
				(m_pLevel->getPlayer())->setVelocity(glm::vec2(1.0f, (m_pLevel->getPlayer())->getVelocity().y));
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if ((m_pLevel->getPlayer())->getVelocity().y < 0.0f) {
					(m_pLevel->getPlayer())->setVelocity(glm::vec2((m_pLevel->getPlayer())->getVelocity().x, 0.0f));
				}
				break;

			case SDLK_s:
				if ((m_pLevel->getPlayer())->getVelocity().y > 0.0f) {
					(m_pLevel->getPlayer())->setVelocity(glm::vec2((m_pLevel->getPlayer())->getVelocity().x, 0.0f));
				}
				break;

			case SDLK_a:
				if ((m_pLevel->getPlayer())->getVelocity().x < 0.0f) {
					(m_pLevel->getPlayer())->setVelocity(glm::vec2(0.0f, (m_pLevel->getPlayer())->getVelocity().y));
				}
				break;
			case SDLK_d:
				if ((m_pLevel->getPlayer())->getVelocity().x > 0.0f) {
					(m_pLevel->getPlayer())->setVelocity(glm::vec2(0.0f, (m_pLevel->getPlayer())->getVelocity().y));
				}
				break;
			default:
				break;
			}
		}
	}
}