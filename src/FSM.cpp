#include "FSM.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Engine.h"
#include "Util.h"
#include "Dog.h"
#include "Slug.h"

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
	TextureManager::Instance()->load("../Assets/Bob_Up.png", "player1", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/Bob_Down.png", "player2", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/Bob_Left.png", "player3", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/Bob_Right.png", "player4", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/player.png", "player", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/dog.png", "dog", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/rib.png", "rib", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/skull.png", "skull", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/bone.png", "bone", Engine::Instance().GetRenderer());
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
		SetCollectibleCounter(3);
		m_vPlayer.push_back(new Player(PlayerState::ALIVE)); 
		m_vPlayer.back()->SetPosition(vec2(60, 360));

		m_vDoors.push_back(new Door({ 132, 126, 32, 32 }, 2, ALCOVE)); //test alcove door
		m_vDoors.push_back(new Door({ 96, 126, 32, 32 }, 2, ALCOVE));
		m_vDoors.push_back(new Door({ 345, 96, 32, 32 }, 3, ALCOVE));
		m_vDoors.push_back(new Door({ 96, 610, 32, 32 }, 3, ALCOVE));
		m_vDoors.push_back(new Door({ 640, 126, 32, 32 }, 2, ALCOVE));
		m_vDoors.push_back(new Door({ 320, 448, 32, 32 }, 1, ALCOVE));
		m_vDoors.push_back(new Door({ 448, 640, 32, 32 }, 2, ALCOVE));
		m_vDoors.push_back(new Door({ 832, 580, 32, 32 }, 3, ALCOVE));

		m_vDoors.push_back(new Door({ 0, 360, 32, 32 }, 3, EXIT));
		m_vDoors.push_back(new Door({ 996, 352, 32, 64 }, 2, EXIT));

		m_vWalls.push_back(new Wall({ 0, 0, int(1280 * 0.8), int(33 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, int(927 * 0.8), int(1280 * 0.8), int(33 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, 0, int(33 * 0.8), int(960 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1247 * 0.8), 0, int(33 * 0.8), int(960 * 0.8) }));

		m_vWalls.push_back(new Wall({ int(86 * 0.8), int(85 * 0.8), int(148 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(165 * 0.8), int(90 * 0.8), int(65 * 0.8), int(230 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(285 * 0.8), int(85 * 0.8), int(149 * 0.8), int(228 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(485 * 0.8), int(85 * 0.8), int(70 * 0.8), int(150 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(725 * 0.8), int(85 * 0.8), int(70 * 0.8), int(270 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(845 * 0.8), int(85 * 0.8), int(70 * 0.8), int(149 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1125 * 0.8), int(85 * 0.8), int(70 * 0.8), int(230 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(86 * 0.8), int(205 * 0.8), int(100 * 0.8), int(110 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, int(364 * 0.8), int(114 * 0.8), int(71 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, int(485 * 0.8), int(114 * 0.8), int(110 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, int(646 * 0.8), int(114 * 0.8), int(290 * 0.8) }));
		m_vWalls.push_back(new Wall({ 0, 710, int(555 * 0.8), int(55 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(165 * 0.8), int(366 * 0.8), int(70 * 0.8), int(468 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(165 * 0.8), int(765 * 0.8), int(270 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(605 * 0.8), 0, int(70 * 0.8), int(200 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(485 * 0.8), int(165 * 0.8), int(190 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(405 * 0.8), int(285 * 0.8), int(109 * 0.8), int(190 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(725 * 0.8), int(285 * 0.8), int(190 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(846 * 0.8), int(285 * 0.8), int(70 * 0.8), int(149 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(965 * 0.8), int(245 * 0.8), int(70 * 0.8), int(189 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(965 * 0.8), int(245 * 0.8), int(170 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1085 * 0.8), int(365 * 0.8), int(70 * 0.8), int(230 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1085 * 0.8), int(365 * 0.8), int(165 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1085 * 0.8), int(525 * 0.8), int(109 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(965 * 0.8), int(645 * 0.8), int(110 * 0.8), int(149 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(965 * 0.8), int(845 * 0.8), int(109 * 0.8), int(110 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(965 * 0.8), int(645 * 0.8), int(230 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(285 * 0.8), int(645 * 0.8), int(150 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(285 * 0.8), int(525 * 0.8), int(270 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(365 * 0.8), int(645 * 0.8), int(70 * 0.8), int(190 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(485 * 0.8), int(525 * 0.8), int(70 * 0.8), int(365 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(605 * 0.8), int(525 * 0.8), int(70 * 0.8), int(349 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(725 * 0.8), int(405 * 0.8), int(70 * 0.8), int(229 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(725 * 0.8), int(805 * 0.8), int(190 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(845 * 0.8), int(485 * 0.8), int(70 * 0.8), int(445 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1125 * 0.8), int(645 * 0.8), int(70 * 0.8), int(230 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1125 * 0.8), int(805 * 0.8), int(130 * 0.8), int(70 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(1195 * 0.8), int(205 * 0.8), int(60 * 0.8), int(30 * 0.8) }));
		m_vWalls.push_back(new Wall({ int(285 * 0.8), int(830 * 0.8), int(30 * 0.8), int(60 * 0.8) }));

		m_vCollectibles.push_back(new Collectible(vec2(980, 130), ObjectType::BONE));
		m_vCollectibles.push_back(new Collectible(vec2(960, 720), ObjectType::RIB));
		m_vCollectibles.push_back(new Collectible(vec2(280, 690), ObjectType::SKULL));

		e1Points.push_back(glm::vec2(48, 48));
		e1Points.push_back(glm::vec2(208, 48));
		e1Points.push_back(glm::vec2(208, 272));
		e1Points.push_back(glm::vec2(48, 272));
		e1Points.push_back(glm::vec2(0, 0));

		e2Points.push_back(glm::vec2(208, 304));
		e2Points.push_back(glm::vec2(208, 400));
		e2Points.push_back(glm::vec2(304, 400));
		e2Points.push_back(glm::vec2(304, 304));
		e2Points.push_back(glm::vec2(0, 0));

		e3Points.push_back(glm::vec2(432, 208));
		e3Points.push_back(glm::vec2(560, 208));
		e3Points.push_back(glm::vec2(560, 400));
		e3Points.push_back(glm::vec2(432, 400));
		e3Points.push_back(glm::vec2(0, 0));

		e4Points.push_back(glm::vec2(656, 48));
		e4Points.push_back(glm::vec2(880, 48));
		e4Points.push_back(glm::vec2(880, 160));
		e4Points.push_back(glm::vec2(752, 160));
		e4Points.push_back(glm::vec2(752, 208));
		e4Points.push_back(glm::vec2(656, 208));
		e4Points.push_back(glm::vec2(0, 0));

		e5Points.push_back(glm::vec2(560, 400));
		e5Points.push_back(glm::vec2(560, 718));
		e5Points.push_back(glm::vec2(464, 718));
		e5Points.push_back(glm::vec2(464, 400));
		e5Points.push_back(glm::vec2(0, 0));

		e6Points.push_back(glm::vec2(752, 368));
		e6Points.push_back(glm::vec2(752, 480));
		e6Points.push_back(glm::vec2(848, 480));
		e6Points.push_back(glm::vec2(848, 368));
		e6Points.push_back(glm::vec2(0, 0));

		m_enemies.push_back(new Dog(e1Points));
		m_enemies.push_back(new Slug(e2Points));
		m_enemies.push_back(new Dog(e3Points));
		m_enemies.push_back(new Slug(e4Points));
		m_enemies.push_back(new Dog(e5Points));
		m_enemies.push_back(new Slug(e6Points));
		break;
		//Other cases to impletent new levels
	default:
		break;
	}
}

void PlayState::Enter()
{
	GenerateLevel(1);
	SetExiting(false);
	SetCompleted(false);
}

void PlayState::Update() // *PLAY LOOP RUNS HERE*
{
	
	bool earlyHalt = false;
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(0.0f, -1.0f));
		m_vPlayer[0]->setMovementSprite(1);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(0.0f, 1.0f));
		m_vPlayer[0]->setMovementSprite(2);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(-1.0f, 0.0f));
		m_vPlayer[0]->setMovementSprite(3);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(1.0f, 0.0f));
		m_vPlayer[0]->setMovementSprite(4);
	}
	m_vPlayer[0]->SetVelocity(Util::Normalize(m_vPlayer[0]->GetVelocity()));
	m_vPlayer[0]->Update();
	m_vPlayer[0]->CalculateNewPositionX();
	if (!CheckCollisions()) {
		int trigger = CheckTriggers();
		if (trigger == 0)
			m_vPlayer[0]->MoveX();
		else if (trigger == 1) {
			earlyHalt = true;
			SetExiting(true);
		}
		else if (trigger > 1 && trigger < 6) {
			if (m_vPlayer[0]->GetHideFrames() <= 0) {
				m_vPlayer[0]->SetHideFrames(20);
				HideState::SetEntry(trigger - 2);
				Engine::Instance().GetFSM().PushState(new HideState());
			}
			else m_vPlayer[0]->MoveX();
		}
	}
	if (!earlyHalt) {
		m_vPlayer[0]->CalculateNewPositionY();
		if (!CheckCollisions()) {
			int trigger = CheckTriggers();
			if (trigger == 0)
				m_vPlayer[0]->MoveY();
			else if (trigger == 1) {
				SetExiting(true);
			}
			else if (trigger > 1 && trigger < 6) {
				if (m_vPlayer[0]->GetHideFrames() <= 0) {
					m_vPlayer[0]->SetHideFrames(20);
					HideState::SetEntry(trigger - 2);
					Engine::Instance().GetFSM().PushState(new HideState());
				}
				else m_vPlayer[0]->MoveY();
			}
		}
	}
	m_vPlayer[0]->SetVelocity(vec2(0.0f, 0.0f));

	if (GetExiting()) {
		Engine::Instance().GetFSM().ChangeState(new WinState());
	}
	//enemies
	for (int i = 0; i < (int)m_enemies.size(); i++)
	{
		m_enemies[i]->Update();
	}
}

void PlayState::Render()
{
	std::cout << "Rendering Game..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	if (!GetCompleted())
		TextureManager::Instance()->draw("dungeon1", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	else 
		TextureManager::Instance()->draw("dungeon1_complete", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_enemies.size(); i++)
	{
		m_enemies[i]->Draw();
	}
	for (int i = 0; i < (int)m_vCollectibles.size(); i++)
	{
		m_vCollectibles[i]->Draw();
	}
	for (int i = 0; i < (int)m_vPlayer.size(); i++)
	{
		m_vPlayer[i]->Draw();
	}
	//TODO: draw enemies and objects
	if (dynamic_cast<PlayState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();

}

void PlayState::Exit()
{
	for (int i = 0; i < (int)m_vPlayer.size(); i++)
	{
		delete m_vPlayer[i];
		m_vPlayer[i] = nullptr;
	}
	m_vPlayer.clear();
	m_vPlayer.shrink_to_fit();
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
	for (int i = 0; i < (int)m_vCollectibles.size(); i++)
	{
		delete m_vCollectibles[i];
		m_vCollectibles[i] = nullptr;
	}
	m_vCollectibles.clear();
	m_vCollectibles.shrink_to_fit();
	for (int i = 0; i < (int)m_enemies.size(); i++)
	{
		delete m_enemies[i];
		m_enemies[i] = nullptr;
	}
	m_enemies.clear();
	m_enemies.shrink_to_fit();
}

bool PlayState::CheckCollisions()
{
	for(int i = 0; i < (int)m_vWalls.size(); i++) {
		if (Util::CircleRectExtrapolate(m_vPlayer[0], m_vWalls[i]->GetCollider()))
			return true;
	}
	for (int i = 0; i < (int)m_vDoors.size(); i++) {
		if (m_vDoors[i]->GetState() == CLOSED && Util::CircleRectExtrapolate(m_vPlayer[0], m_vDoors[i]->GetCollider()))
			return true;
	}
	for (int i = 0; i < (int)m_vCollectibles.size(); i++) {  // collectibles collector
		if (Util::CircleCircle(m_vPlayer[0], m_vCollectibles[i])) {
			if (m_vCollectibles[i]->GetActiveState() == ACTIVE) {
				SetCollectibleCounter(GetCollectibleCounter() - 1);
				m_vCollectibles[i]->SetActiveState(ActiveState::INACTIVE);
				cout << "collision with collectible" << endl;
				if (GetCollectibleCounter() == 0) {
					for (int j = 0; j < (int)m_vDoors.size(); j++) {
						m_vDoors[j]->SetState(DoorState::OPEN);
					}
					SetCompleted(true);
				}
			}
		}
	}
	return false;
}

int PlayState::CheckTriggers()//0-no collision, 1-exit trigger, 2-alcove door trigger upper, 3-alcove door trigger lower, 4-alcove door trigger left, 5-alcove door trigger right --add other triggers here
{
	for (int i = 0; i < (int)m_vDoors.size(); i++) {
		if (Util::PointCircle(m_vDoors[i]->GetTrigger(), m_vPlayer[0])) {
			switch (m_vDoors[i]->GetType()) {
			case EXIT:
				return 1;
			case ALCOVE:
				return m_vDoors[i]->GetEntry() + 2; 
			default:
				cout << "unspecified trigger reached" << endl;
				break;
			}
		}
	}
	return 0;
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

void HideState::Enter() // Player Enters the hidden alcove
{
	m_vPlayer.push_back(new Player(PlayerState::ALIVE));
	m_backGround = SDL_Rect{ 0, 0, WIDTH, HEIGHT };;
	switch (m_entry) {
	case 0: //Entry from above
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 280, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 482, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 540, 160, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 222, 128, 259 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 477, 160, 64, 64 }, 1, EXIT));
		m_vPlayer[0]->SetPosition(vec2(530, 260));
		m_vPlayer[0]->SetNewPosition(vec2(530, 260));
		break;
	case 1: //Entry from below
		m_vWalls.push_back(new Wall(SDL_Rect{ 543, 488, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 286, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 547, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 222, 128, 259 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 477, 160, 64, 64 }, 0, EXIT));
		m_vPlayer[0]->SetPosition(vec2(495, 500));
		m_vPlayer[0]->SetNewPosition(vec2(495, 500));
		break;
	case 2: //Entry from left
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 415, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 408, 479, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 610, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 160, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 348, 160, 263, 128 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 288, 354, 64, 64 }, 3, EXIT));
		m_vPlayer[0]->SetPosition(vec2(390, 360));
		m_vPlayer[0]->SetNewPosition(vec2(390, 360));
		break;
	case 3: //Entry from right
		m_vWalls.push_back(new Wall(SDL_Rect{ 615, 160, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 414, 159, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 675, 411, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 413, 480, 263, 128 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 672, 349, 64, 64 }, 2, EXIT));
		m_vPlayer[0]->SetPosition(vec2(630, 405));
		m_vPlayer[0]->SetNewPosition(vec2(630, 405));
		break;
	default:
		break;
	}
}

void HideState::Update()
{
	bool earlyExit = false;
	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(0.0f, -1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(0.0f, 1.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(-1.0f, 0.0f));
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		m_vPlayer[0]->SetVelocity(m_vPlayer[0]->GetVelocity() + vec2(1.0f, 0.0f));
	}
	m_vPlayer[0]->SetVelocity(Util::Normalize(m_vPlayer[0]->GetVelocity()));
	m_vPlayer[0]->Update();
	m_vPlayer[0]->CalculateNewPositionX();
	if (!CheckCollisions()) {
		int trigger = CheckTriggers();
		if (trigger == 0) {
			m_vPlayer[0]->MoveX();
		}
		else {
			earlyExit = true;
			Engine::Instance().GetFSM().PopState();
		}
	}
	if (!earlyExit && m_vPlayer.size()!=0) {
		m_vPlayer.back()->CalculateNewPositionY();
		if (!CheckCollisions()) {
			if (!CheckCollisions()) {
				int trigger = CheckTriggers();
				if (trigger == 0)
					m_vPlayer.back()->MoveY();
				else
					Engine::Instance().GetFSM().PopState();
			}
		}
	}
	if (!earlyExit && m_vPlayer.size() != 0)
		m_vPlayer.back()->SetVelocity(vec2(0.0f, 0.0f));
}

void HideState::Render()
{
	std::cout << "Rendering Alcove..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
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
	for (int i = 0; i < (int)m_vPlayer.size(); i++) {
		m_vPlayer[i]->Draw();
	}
	State::Render();
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
	for (int i = 0; i < (int)m_vDoor.size(); i++) {
		delete m_vDoor[i];
		m_vDoor[i] = nullptr;
	}
	m_vDoor.clear();
	m_vDoor.shrink_to_fit();
	for (int i = 0; i < (int)m_vPlayer.size(); i++) {
		delete m_vPlayer[i];
		m_vPlayer[i] = nullptr;
	}
	m_vPlayer.clear();
	m_vPlayer.shrink_to_fit();
}

bool HideState::CheckCollisions()
{
	for (int i = 0; i < (int)m_vWalls.size(); i++) {
		if (Util::CircleRectExtrapolate(m_vPlayer[0], m_vWalls[i]->GetCollider()))
			return true;
	}
	return false;
}

bool HideState::CheckTriggers()
{
	for (int i = 0; i < (int)m_vDoor.size(); i++) {
		if (Util::PointCircle(m_vDoor[i]->GetTrigger(), m_vPlayer[0])) {
			return true;
		}
	}
	return false;
}

void WinState::Enter()
{
	SetCurrentState(WIN);
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
	SDL_RenderClear(Engine::Instance().GetRenderer());
	TextureManager::Instance()->draw("win_menu", WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_vButtons.size(); i++) {
		m_vButtons[i]->Draw();
	}
	State::Render();
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
