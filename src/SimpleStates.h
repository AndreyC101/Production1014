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
	ACTIVE,
	HIDDEN,
	DEAD,
	INACTIVE
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
	ON,
	OFF
};

