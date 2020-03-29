#pragma once
#include <vector>
#include "Button.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelObjects.h"
#include "Collectible.h"

static int m_entry;

class State {
protected:
	FSMState m_currentState;
public:
	State() {}
	~State() {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Resume() {}
	virtual void Exit() = 0;
	FSMState GetCurrentState() { return m_currentState; }
	void SetCurrentState(FSMState state) { m_currentState = state; }
};

class TitleState : public State {
private:
	vector<Button*> m_vButtons;
public:
	TitleState() {}
	~TitleState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class PlayState : public State {
private:
	CurrentLevel m_currentLevel;
	string m_map, m_mapCompleted;
	bool m_completed, m_hiding, m_exiting;
	int m_collectibleCounter, m_indexOfActiveDoor;
	Player* m_pPlayer;
	vector<GameObject*> m_vObjects;
	vector<Wall*> m_vWalls;
	vector<Door*> m_vDoors;
	vector<Collectible*> m_vCollectibles;
	//enemies
	vector<glm::vec2> e1Points;
	vector<glm::vec2> e2Points;
	vector<glm::vec2> e3Points;
	vector<glm::vec2> e4Points;
	vector<glm::vec2> e5Points;
	vector<glm::vec2> e6Points;

	vector<Enemy*> m_enemies;

public:
	void GenerateLevel(int level);
	PlayState() {}
	~PlayState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
	bool CheckCollisions();
	int CheckTriggers(); //0-no collision, 1-exit trigger, 2, 3, 4, 5-alcove entries(+2) --add other triggers here
	CurrentLevel GetCurrentLevel() { return m_currentLevel; }
	void SetCurrentLevel(CurrentLevel newLevel) { m_currentLevel = newLevel; }
	int GetCollectibleCounter() { return m_collectibleCounter; }
	void SetCollectibleCounter(int newCounter) { m_collectibleCounter = newCounter; }
	int GetIndexOfActiveDoor() { return m_indexOfActiveDoor; }
	void SetIndexOfActiveDoor(int index) { m_indexOfActiveDoor = index; }
	void MovePlayerToActiveDoor();
	bool GetCompleted() { return m_completed; }
	void SetCompleted(bool check) { m_completed = check; }
	bool GetHiding() { return m_hiding; }
	void SetHiding(bool check) { m_hiding = check; }
	bool GetExiting() { return m_exiting; }
	void SetExiting(bool check) { m_exiting = check; }
	bool CheckEnemies();
	string GetMapString() { return m_map; }
	string GetMapCompletedString() { return m_mapCompleted; }
	void SetMapStrings(string map, string mapCompleted) { m_map = map; m_mapCompleted = mapCompleted; }
	void EmptyLevel();
	void ChangeLevel();
};

class PauseState : public State {
private:
	vector<Button*> m_vButtons;
public:
	PauseState() {}
	~PauseState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class HideState : public State {
private:
	SDL_Rect m_backGround;
	Player* m_pPlayer;
	vector<Wall*> m_vWalls;
	vector<Door*> m_vDoor;
	bool m_exiting;
	PlayState* m_pActivePlayState;
public:
	HideState(PlayState* activePlayState) { m_pActivePlayState = activePlayState; }
	~HideState() {}
	void Enter(); // 0-Up, 1-Down, 2-Left, 3-Right
	void Update();
	void Render();
	void Exit();
	vector<Wall*>& GetWalls() { return m_vWalls; }
	bool CheckCollisions();
	bool CheckTriggers();
	bool GetExiting() { return m_exiting; }
	void SetExiting(bool exiting) { m_exiting = exiting; }
	static void SetEntry(int entry) { m_entry = entry; }
};

class WinState : public State {
private:
	vector<Button*> m_vButtons;
public:
	WinState() {}
	~WinState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class DeathState : public State {
private:
	vector<Button*> m_vButtons;
public:
	DeathState() {}
	~DeathState() {}
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class FSM {
private:
	std::vector<State*> m_vStates;
public:
	static FSM& Instance() {
		static FSM s_Instance = FSM();
		return s_Instance;
	}
	FSM() {}
	~FSM() {}
	void Update();
	void Render();
	void ChangeState(State* pState);
	void PushState(State* pState);
	void PopState();
	void Clean();
	static void LoadAssets();
	vector<State*>& GetStates() { return m_vStates; }
};