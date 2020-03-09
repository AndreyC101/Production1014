#pragma once
enum FSMState {
	TITLE,
	PAUSE,
	GAME,
	HIDE,
	GAME_OVER
};

enum PlayerState {
	ACTIVE,
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