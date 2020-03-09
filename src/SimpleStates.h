#pragma once
enum FSMState {
	TITLE,
	PAUSE,
	GAME,
	HIDE,
	GAME_OVER,
	WIN
};

enum PlayerState {
	ALIVE,
	HIDDEN,
	DEAD
};

enum EnemyState {
	PATROL,
	CHASE
};

enum ButtonState {
	IDLE,
	SELECTED
};

enum DoorState {
	OPEN,
	CLOSED
};

enum ActiveState {
	ACTIVE,
	INACTIVE
};

