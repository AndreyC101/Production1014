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
	if (m_vStates.back()->GetCurrentState() == FSMState::HIDE)
		m_vStates.front()->Update();
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
	TextureManager::Instance()->load("../Assets/P_bone.png", "pBone", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/crossbone.png", "crossbone", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/deathSkull.png", "dSkull", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/fishbone.png", "fishbone", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/crackskull.png", "crackskull", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/dungeon1_alternate.png", "dungeon1", Engine::Instance().GetRenderer());
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
	TextureManager::Instance()->load("../Assets/light.png", "HUDlight", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/tutorial_map_closed.png", "tutorial", Engine::Instance().GetRenderer());
	TextureManager::Instance()->load("../Assets/tutorial_map_open.png", "tutorial_complete", Engine::Instance().GetRenderer());

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
	case 0:
		SetMapStrings("tutorial", "tutorial_complete");
		m_pPlayer->SetPosition(vec2(60, 368));

		m_vWalls.push_back(new Wall({ 0, 0, 30, 768 }));
		m_vWalls.push_back(new Wall({ 0, 0, 1024, 30 }));
		m_vWalls.push_back(new Wall({ 994, 0, 30, 169 }));
		m_vWalls.push_back(new Wall({ 994, 213, 30, 121 }));
		m_vWalls.push_back(new Wall({ 994, 390, 30, 378 }));
		m_vWalls.push_back(new Wall({ 0, 738, 1024, 30 }));

		m_vDoors.push_back(new Door({ 988,352,32,32 }, 2, EXIT));
		m_vDoors.push_back(new Door({ 988,176,32,32 }, 2, ALCOVE));

		m_vCollectibles.push_back(new Collectible(vec2(330, 310), ObjectType::BONE));
		m_vCollectibles.push_back(new Collectible(vec2(405, 310), ObjectType::RIB));
		m_vCollectibles.push_back(new Collectible(vec2(480, 310), ObjectType::SKULL));
		SetCollectibleCounter((int)m_vCollectibles.size());

		break;
	case 1:
		SetMapStrings("dungeon1", "dungeon1_complete");
		m_pPlayer->SetPosition(vec2(60, 360));

		m_vDoors.push_back(new Door({ 126, 128, 32, 32 }, 2, ALCOVE)); //test alcove door
		m_vDoors.push_back(new Door({ 64, 607, 32, 32 }, 3, ALCOVE));
		m_vDoors.push_back(new Door({ 319, 449, 32, 32 }, 1, ALCOVE));
		m_vDoors.push_back(new Door({ 320, 96, 32, 32 }, 3, ALCOVE));
		m_vDoors.push_back(new Door({ 672, 127, 32, 32 }, 2, ALCOVE));
		m_vDoors.push_back(new Door({ 478, 639, 32, 32 }, 2, ALCOVE));
		m_vDoors.push_back(new Door({ 833, 575, 32, 32 }, 3, ALCOVE));
		m_vDoors.push_back(new Door({ 961, 286, 32, 32 }, 0, ALCOVE));

		m_vDoors.push_back(new Door({ 0, 351, 32, 32 }, 3, EXIT));
		m_vDoors.push_back(new Door({ 992, 367, 32, 32 }, 2, EXIT));

		m_vWalls.push_back(new Wall({ 0, 0, 1024, 28 }));
		m_vWalls.push_back(new Wall({ 0, 740, 1024, 29 }));
		m_vWalls.push_back(new Wall({ 0, 0, 27, 348 }));
		m_vWalls.push_back(new Wall({ 0, 388, 92, 88 }));
		m_vWalls.push_back(new Wall({ 0, 476, 28, 40 }));
		m_vWalls.push_back(new Wall({ 0, 516, 92, 85 }));
		m_vWalls.push_back(new Wall({ 0, 600, 62, 40 }));
		m_vWalls.push_back(new Wall({ 0, 644, 92, 94 }));
		m_vWalls.push_back(new Wall({ 92, 708, 353, 28 }));
		m_vWalls.push_back(new Wall({ 228, 668, 24, 40 }));
		m_vWalls.push_back(new Wall({ 132, 611, 216, 58 }));
		m_vWalls.push_back(new Wall({ 132, 292, 56, 376 }));
		m_vWalls.push_back(new Wall({ 68, 168, 120, 88 }));
		m_vWalls.push_back(new Wall({ 68, 68, 120, 56 }));
		m_vWalls.push_back(new Wall({ 166, 122, 22, 43 }));
		m_vWalls.push_back(new Wall({ 228, 68, 90, 184 }));
		m_vWalls.push_back(new Wall({ 319, 68, 29, 22 }));
		m_vWalls.push_back(new Wall({ 320, 135, 28, 100 }));
		m_vWalls.push_back(new Wall({ 324, 228, 88, 152 }));
		m_vWalls.push_back(new Wall({ 228, 420, 88, 57 }));
		m_vWalls.push_back(new Wall({ 316, 420, 37, 26 }));
		m_vWalls.push_back(new Wall({ 352, 420, 92, 56 }));
		m_vWalls.push_back(new Wall({ 388, 475, 56, 265 }));
		m_vWalls.push_back(new Wall({ 484, 420, 56, 214 }));
		m_vWalls.push_back(new Wall({ 484, 672, 56, 29 }));
		m_vWalls.push_back(new Wall({ 512, 638, 28, 34 }));
		m_vWalls.push_back(new Wall({ 388, 68, 56, 120 }));
		m_vWalls.push_back(new Wall({ 484, 28, 56, 160 }));
		m_vWalls.push_back(new Wall({ 444, 132, 40, 56 }));
		m_vWalls.push_back(new Wall({ 580, 68, 56, 216 }));
		m_vWalls.push_back(new Wall({ 636, 228, 40, 56 }));
		m_vWalls.push_back(new Wall({ 676, 228, 56, 120 }));
		m_vWalls.push_back(new Wall({ 580, 324, 56, 184 }));
		m_vWalls.push_back(new Wall({ 580, 644, 101, 56 }));
		m_vWalls.push_back(new Wall({ 676, 388, 56, 352 }));
		m_vWalls.push_back(new Wall({ 772, 676, 88, 64 }));
		m_vWalls.push_back(new Wall({ 676, 68, 56, 56 }));
		m_vWalls.push_back(new Wall({ 676, 160, 56, 28 }));
		m_vWalls.push_back(new Wall({ 706, 125, 26, 35 }));
		m_vWalls.push_back(new Wall({ 900, 68, 56, 184 }));
		m_vWalls.push_back(new Wall({ 828, 196, 72, 56 }));
		m_vWalls.push_back(new Wall({ 772, 196, 56, 152 }));
		m_vWalls.push_back(new Wall({ 956, 164, 40, 24 }));
		m_vWalls.push_back(new Wall({ 868, 292, 56, 128 }));
		m_vWalls.push_back(new Wall({ 868, 420, 88, 56 }));
		m_vWalls.push_back(new Wall({ 924, 292, 36, 56 }));
		m_vWalls.push_back(new Wall({ 958, 322, 66, 26 }));
		m_vWalls.push_back(new Wall({ 996, 28, 29, 292 }));
		m_vWalls.push_back(new Wall({ 996, 415, 29, 325 }));
		m_vWalls.push_back(new Wall({ 900, 644, 96, 57 }));
		m_vWalls.push_back(new Wall({ 900, 516, 56, 128 }));
		m_vWalls.push_back(new Wall({ 772, 516, 128, 54 }));
		m_vWalls.push_back(new Wall({ 772, 572, 60, 64 }));
		m_vWalls.push_back(new Wall({ 832, 608, 28, 28 }));
		m_vWalls.push_back(new Wall({ 228, 516, 120, 56 }));
		m_vWalls.push_back(new Wall({ 292, 572, 56, 40 }));
		m_vWalls.push_back(new Wall({ 28, 292, 63, 50 }));

		m_vCollectibles.push_back(new Collectible(vec2(50, 50), ObjectType::CROSSBONE));
		m_vCollectibles.push_back(new Collectible(vec2(980, 130), ObjectType::BONE));
		m_vCollectibles.push_back(new Collectible(vec2(960, 720), ObjectType::RIB));
		m_vCollectibles.push_back(new Collectible(vec2(280, 690), ObjectType::SKULL));
		m_vCollectibles.push_back(new Collectible(vec2(500, 300), ObjectType::CRACKSKULL));
		m_vCollectibles.push_back(new Collectible(vec2(650, 720), ObjectType::FISHBONE));
		SetCollectibleCounter((int)m_vCollectibles.size());

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
	default:
		break;
	}
}

void PlayState::Enter()
{
	SetCurrentState(GAME);
	SetCurrentLevel(TUTORIAL);
	m_pPlayer = Player::Instance();
	GenerateLevel(0);
	SetExiting(false);
	SetCompleted(false);
	SetHiding(false);
	m_pPlayer->SetState(ACTIVE);
	m_pPlayer->SetLightActive(false);
	SetIndexOfActiveDoor((int)m_vDoors.size());
}

void PlayState::Update() // *PLAY LOOP RUNS HERE*
{
	std::cout << "Updating Play State" << endl;
	m_pPlayer->Update();
	int trigger;
 	if (m_pPlayer->GetState() == PlayerState::ACTIVE) {
		bool movePlayerX = false, movePlayerY = false;
		m_pPlayer->CalculateNewPositionX();
		if (!CheckCollisions()) {
			movePlayerX = true;
		}
		m_pPlayer->CalculateNewPositionY();
		if (!CheckCollisions()) {
			movePlayerY = true;
		}
		trigger = CheckTriggers();
		if (trigger == 1) SetExiting(true);
		else if (trigger > 1 && trigger < 6 && m_pPlayer->GetHideFrames() == 0) SetHiding(true);
		if (movePlayerX) m_pPlayer->MoveX();
		if (movePlayerY) m_pPlayer->MoveY();
		if (GetHiding()) {
			HideState::SetEntry(trigger - 2);
			Engine::Instance().GetFSM().PushState(new HideState(this));
		}
		Player::Instance()->SetVelocity(vec2(0.0f, 0.0f));
	}

	//enemies
	for (int i = 0; i < (int)m_enemies.size(); i++)
	{
		m_enemies[i]->Update();
	}
	if (CheckEnemies()) {
		if (m_pPlayer->GetState() == ACTIVE)
			m_pPlayer->SetState(DEAD);
	}
	if (m_pPlayer->GetState() == PlayerState::ACTIVE && GetExiting()) {
		ChangeLevel();
	}
	else if (m_pPlayer->GetState() == PlayerState::DEAD)
		Engine::Instance().GetFSM().ChangeState(new DeathState());
}

void PlayState::Render()
{
	std::cout << "Rendering Game..." << std::endl;
	SDL_RenderClear(Engine::Instance().GetRenderer());
	if (!GetCompleted())
		TextureManager::Instance()->draw(GetMapString(), WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	else 
		TextureManager::Instance()->draw(GetMapCompletedString(), WIDTH / 2, HEIGHT / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < (int)m_enemies.size(); i++)
	{
		m_enemies[i]->Draw();
	}
	for (int i = 0; i < (int)m_vCollectibles.size(); i++)
	{
		m_vCollectibles[i]->Draw();
	}
	m_pPlayer->Draw();
	/*for (int i = 0; i < (int)m_vWalls.size(); i++)
	{
		m_vWalls[i]->Debug();
	}
	for (int i = 0; i < (int)m_vDoors.size(); i++)
	{
		m_vDoors[i]->Debug();
	}*/
	if (dynamic_cast<PlayState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void PlayState::Exit()
{
	EmptyLevel();
	m_pPlayer = nullptr;
}

bool PlayState::CheckCollisions()
{
	for(int i = 0; i < (int)m_vWalls.size(); i++) {
		if (Util::CircleRectExtrapolate(m_pPlayer, m_vWalls[i]->GetCollider()))
			return true;
	}
	for (int i = 0; i < (int)m_vDoors.size(); i++) {
		if (m_vDoors[i]->GetState() == CLOSED && Util::CircleRectExtrapolate(m_pPlayer, m_vDoors[i]->GetCollider()))
			return true;
	}
	for (int i = 0; i < (int)m_vCollectibles.size(); i++) {  // collectibles collector
		if (Util::CircleCircle(m_pPlayer, m_vCollectibles[i])) {
			if (m_vCollectibles[i]->GetActiveState() == ACTIVE) {
				SetCollectibleCounter(GetCollectibleCounter() - 1);
				m_vCollectibles[i]->SetActiveState(ActiveState::OFF);
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
		if (Util::PointCircle(m_vDoors[i]->GetTrigger(), m_pPlayer) && m_indexOfActiveDoor != i) {
			if (m_pPlayer->GetHideFrames() == 0) SetIndexOfActiveDoor(i);
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
void PlayState::MovePlayerToActiveDoor()
{
	m_pPlayer->SetPosition(m_vDoors[GetIndexOfActiveDoor()]->GetTrigger());
}

bool PlayState::CheckEnemies()
{
	for (int i = 0; i < (int)m_enemies.size(); i++) {
		if (Util::CircleCircle(m_pPlayer, m_enemies[i])) {
			return true;
		}
	}
	return false;
}

void PlayState::EmptyLevel()
{
	SetMapStrings("", "");
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

void PlayState::ChangeLevel()
{
	switch (GetCurrentLevel()) {
	case TUTORIAL:
		EmptyLevel();
		GenerateLevel(1);
		SetExiting(false);
		SetCompleted(false);
		SetHiding(false);
		SetIndexOfActiveDoor((int)m_vDoors.size());
		SetCurrentLevel(LEVEL_1);
		m_pPlayer->SetLightActive(true);
		break;
	case LEVEL_1:
		Engine::Instance().GetFSM().ChangeState(new WinState());
		break;
	}
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
	SetCurrentState(HIDE);
	m_pPlayer = Player::Instance();
	m_pPlayer->SetState(HIDDEN);
	SetExiting(false);
	m_backGround = SDL_Rect{ 0, 0, WIDTH, HEIGHT };
	switch (m_entry) {
	case 0: //Entry from above
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 280, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 482, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 540, 160, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 222, 128, 259 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 477, 160, 64, 64 }, 1, EXIT));
		m_pPlayer->SetPosition(vec2(530, 260));
		m_pPlayer->SetNewPosition(vec2(530, 260));
		break;
	case 1: //Entry from below
		m_vWalls.push_back(new Wall(SDL_Rect{ 543, 488, 192, 121 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 608, 286, 129, 202 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 448, 126 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 547, 197, 61 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 289, 285, 128, 255 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 479, 543, 64, 64 }, 0, EXIT));
		m_pPlayer->SetPosition(vec2(495, 500));
		m_pPlayer->SetNewPosition(vec2(495, 500));
		break;
	case 2: //Entry from left
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 415, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 408, 479, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 610, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 287, 160, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 348, 160, 263, 128 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 288, 354, 64, 64 }, 3, EXIT));
		m_pPlayer->SetPosition(vec2(390, 360));
		m_pPlayer->SetNewPosition(vec2(390, 360));
		break;
	case 3: //Entry from right
		m_vWalls.push_back(new Wall(SDL_Rect{ 615, 160, 121, 193 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 414, 159, 203, 130 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 288, 160, 126, 448 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 675, 411, 62, 197 }));
		m_vWalls.push_back(new Wall(SDL_Rect{ 413, 480, 263, 128 }));
		m_vDoor.push_back(new Door(SDL_Rect{ 672, 349, 64, 64 }, 2, EXIT));
		m_pPlayer->SetPosition(vec2(630, 405));
		m_pPlayer->SetNewPosition(vec2(630, 405));
		break;
	default:
		cout << "no valid entry parameter" << endl;
		Engine::Instance().GetFSM().PopState();
		break;
	}
}

void HideState::Update()
{
	bool movePlayerX = false, movePlayerY = false;
	m_pPlayer->Update();
	m_pPlayer->CalculateNewPositionX();
	if (!CheckCollisions()) {
		movePlayerX = true;
	}
	m_pPlayer->CalculateNewPositionY();
	if (!CheckCollisions()) {
		movePlayerY = true;
	}
	if (CheckTriggers() != 0) SetExiting(true);
	if (movePlayerX) m_pPlayer->MoveX();
	if (movePlayerY) m_pPlayer->MoveY();
	m_pPlayer->SetVelocity(vec2(0.0f, 0.0f));
	if (GetExiting()) {
		m_pPlayer->SetHideFrames(60);
		m_pActivePlayState->MovePlayerToActiveDoor();
		m_pActivePlayState->SetHiding(false);
		m_pActivePlayState->SetIndexOfActiveDoor(999);
		m_pPlayer->SetState(PlayerState::ACTIVE);
		Engine::Instance().GetFSM().PopState();
	}
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
	m_pPlayer->Draw();
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
	m_pPlayer = nullptr;
	m_pActivePlayState = nullptr;
}

bool HideState::CheckCollisions()
{
	for (int i = 0; i < (int)m_vWalls.size(); i++) {
		if (Util::CircleRectExtrapolate(m_pPlayer, m_vWalls[i]->GetCollider()))
			return true;
	}
	return false;
}

bool HideState::CheckTriggers()
{
	for (int i = 0; i < (int)m_vDoor.size(); i++) {
		if (Util::PointCircle(m_vDoor[i]->GetTrigger(), m_pPlayer)) {
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
