#include "FSM.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Engine.h"
#include "Util.h"

void FSM::Update()
{
	if (!m_vStates.empty())
		m_vStates.back()->Update();
}

void FSM::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render();
}

void FSM::ChangeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	PushState(pState);
}

void FSM::PushState(State* pState)
{
	m_vStates.push_back(pState);
	m_vStates.back()->Enter();
}

void FSM::PopState()
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::Clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

void FSM::LoadAssets()
{
	TextureManager::Instance()->load("../Assets/player.png", "player", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/dog.png", "dog", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/dungeon1.png", "dungeon1", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/dungeon1_complete.png", "dungeon1_complete", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/start_menu.png", "start_menu", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/pause_menu.png", "pause_menu", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/death_menu.png", "death_menu", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/win_menu.png", "win_menu", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/start_button.png", "start_button", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/restart_button.png", "restart_button", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/quit_button.png", "quit_button", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/lamp_light.png", "lamp_light", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/alcove.png", "alcove", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/QuitButtonSelected.png", "quit_button_selected", Engine::Instance().GetRenderer());

	//ADD ALL AUDIO FILES HERE USING SoundManager::Instance()->load()

	srand(time(NULL));
}

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void TitleState::Enter()
{
	FSM::LoadAssets();
	SetCurrentState(TITLE);
	m_vButtons.push_back(new StartButton(vec2(240, 490)));
	m_vButtons.push_back(new QuitButton(vec2(760, 490)));
}

void TitleState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Update();
	}
}

void TitleState::Render()
{
	std::cout << "Rendering Title..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	TextureManager::Instance()->draw("start_menu", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Draw();
	}
	State::Render();
}

void TitleState::Exit()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	std::cout << "Exiting Title..." << std::endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

void PauseState::Enter()
{
	SetCurrentState(PAUSE);
	m_vButtons.push_back(new StartButton(vec2(340, 470)));
	m_vButtons.push_back(new RestartButton(vec2(515, 470)));
	m_vButtons.push_back(new QuitButton(vec2(694, 470)));
}

void PauseState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Update();
	}
}

void PauseState::Render()
{
	std::cout << "Rendering Pause Screen..." << std::endl;
	Engine::Instance().GetFSM().GetStates().front()->Render();
	TextureManager::Instance()->draw("pause_menu", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Draw();
	}
	State::Render();
}

void PauseState::Exit()
{
	std::cout << "Exiting Pause Screen..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

void PlayState::GenerateLevel(int level)
{
	switch (level) {
	case 1:
		m_vObjects.push_back(new Player(ACTIVE)); //m_vObjects.front will always be player
		m_vObjects[0]->SetPosition(vec2(60, 380));
		//TODO: populate m_vObjects with enemies and set patrol points here
		break;
		//Other cases to impletent new levels
	default:
		break;
	}
}

void PlayState::Enter()
{
	GenerateLevel(1);
}

void PlayState::Update() // *PLAY LOOP RUNS HERE*
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(0.0f, -1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(0.0f, 1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(-1.0f, 1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(1.0f, 0.0f));
	}
	m_vObjects[0]->SetVelocity(Util::Normalize(m_vObjects[0]->GetVelocity()));
	m_vObjects[0]->Update();
	m_vObjects[0]->SetVelocity(vec2(0.0f, 0.0f));

	//TODO: Update enemies here
}

void PlayState::Render()
{
	std::cout << "Rendering Game..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	TextureManager::Instance()->draw("dungeon1", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_vObjects.size(); i++)
	{
		m_vObjects[i]->Draw();
	}
	if (dynamic_cast<PlayState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void PlayState::Exit()
{
	for (int i = 0; i < (int)m_vObjects.size(); i++)
	{
		delete m_vObjects[i];
		m_vObjects[i] = nullptr;
	}
	m_vObjects.clear();
	m_vObjects.shrink_to_fit();
	for (int i = 0; i < (int)m_vWalls.size(); i++)
	{
		delete m_vWalls[i];
		m_vWalls[i] = nullptr;
	}
	m_vWalls.clear();
	m_vWalls.shrink_to_fit();
	for (int i = 0; i < (int)m_vDoors.size(); i++)
	{
		delete m_vDoors[i];
		m_vDoors[i] = nullptr;
	}
	m_vDoors.clear();
	m_vDoors.shrink_to_fit();

	//TODO: Delete enemies
}

void DeathState::Enter()
{
	m_vButtons.push_back(new RestartButton(vec2(380, 480)));
	m_vButtons.push_back(new QuitButton(vec2(590, 480)));
}

void DeathState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Update();
	}
}

void DeathState::Render()
{
	std::cout << "Rendering Death Screen..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	TextureManager::Instance()->draw("death_menu", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Draw();
	}
	State::Render();
}

void DeathState::Exit()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	std::cout << "Exiting Death Screen..." << std::endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

void HideState::Enter(int entry) // Player Enters the hidden alcove
{
	m_vObjects.push_back(new Player(ACTIVE));
	m_entry = entry;
	m_backGround = SDL_Rect{ 0, 0, WIDTH, HEIGHT };
	switch (m_entry) {
	case 0: //Entry from above
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 280, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 482, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 540, 160, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 222, 128, 259 }));
		m_vWalls.push_back(new Door(SDL_Rect{ 477, 160, 64, 64 }, 1, EXIT));
		m_vObjects[0]->SetPosition(vec2(530, 260));
		break;
	case 1: //Entry from below
		m_vWalls.push_back(new Wall(SDL_Rect{ 543, 488, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 286, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 547, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 222, 128, 259 }));
		m_vWalls.push_back(new Door(SDL_Rect{ 477, 160, 64, 64 }, 0, EXIT));
		m_vObjects[0]->SetPosition(vec2(495, 500));
		break;
	case 2: //Entry from left
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 415, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 408, 479, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 610, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 160, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 348, 160, 263, 128 }));
		m_vWalls.push_back(new Door(SDL_Rect{ 288, 354, 64, 64 }, 3, EXIT));
		m_vObjects[0]->SetPosition(vec2(390, 360));
		break;
	case 3: //Entry from right
		m_vWalls.push_back(new Wall(SDL_Rect{ 615, 160, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 414, 159, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 675, 411, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 413, 480, 263, 128 }));
		m_vWalls.push_back(new Door(SDL_Rect{ 672, 349, 64, 64 }, 2, EXIT));
		m_vObjects[0]->SetPosition(vec2(630, 405));
		break;
	default:
		break;
	}
}

void HideState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(0.0f, -1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(0.0f, 1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(-1.0f, 1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		m_vObjects[0]->SetVelocity(m_vObjects[0]->GetVelocity() + vec2(1.0f, 0.0f));
	}
	m_vObjects[0]->SetVelocity(Util::Normalize(m_vObjects[0]->GetVelocity()));
	m_vObjects[0]->Update();
	m_vObjects[0]->SetVelocity(vec2(0.0f, 0.0f));
}

void HideState::Render()
{
	std::cout << "Rendering Alcove..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_backGround); // use opaque background to block view of map
	switch (m_entry) {
	case 0:
		TextureManager::Instance()->draw("alcove", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), 270, 255, true, SDL_FLIP_NONE);
		break;
	case 1:
		TextureManager::Instance()->draw("alcove", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), 90, 255, true, SDL_FLIP_NONE);
		break;
	case 2:
		TextureManager::Instance()->draw("alcove", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), 180, 255, true, SDL_FLIP_NONE);
		break;
	case 3:
		TextureManager::Instance()->draw("alcove", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
		break;
	default:
		break;
	}
	for (int i = 0; i < (int)m_vObjects.size(); i++) {
		m_vObjects[i]->Draw();
	}
}

void HideState::Exit()
{
	std::cout << "Exiting Alcove..." << std::endl;
	for (int i = 0; i < (int)m_vWalls.size(); i++) {
		delete m_vWalls[i];
		m_vWalls[i] = nullptr;
	}
	m_vWalls.clear();
	m_vWalls.shrink_to_fit();
	for (int i = 0; i < (int)m_vObjects.size(); i++) {
		delete m_vObjects[i];
		m_vObjects[i] = nullptr;
	}
	m_vObjects.clear();
	m_vObjects.shrink_to_fit();
}

void WinState::Enter()
{
	m_vButtons.push_back(new RestartButton(vec2(370, 560)));
	m_vButtons.push_back(new QuitButton(vec2(690, 560)));
}

void WinState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Update();
	}
}

void WinState::Render()
{
	std::cout << "Rendering Win Screen..." << std::endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Draw();
	}
}

void WinState::Exit()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	std::cout << "Exiting Win Screen..." << std::endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
