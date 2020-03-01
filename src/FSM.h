#pragma once
#include <vector>
#include "Button.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelObjects.h"

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
	vector<Player*> m_vPlayer;
	vector<GameObject*> m_vObjects; //placeholder vector for enemies
	vector<Wall*> m_vWalls;
	vector<Door*> m_vDoors;
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
	vector<Player*> m_vPlayer;
	vector<Wall*> m_vWalls;
	vector<Door*>m_vDoor;
public:
	HideState() {}
	~HideState() {}
	void Enter(); // 0-Up, 1-Down, 2-Left, 3-Right
	void Update();
	void Render();
	void Exit();
	vector<Wall*>& GetWalls() { return m_vWalls; }
	bool CheckCollisions();
	bool CheckTriggers();
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