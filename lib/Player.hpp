#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Common.hpp"
#include "State.hpp"

// Handles Player input

enum class PlayerInput {
	None=0,
	UpArrow=1,
	DownArrow =2,
	LeftArrow=3,
	RightArrow=4,
};
struct Player {

	bool IsAdvancedInputSupported();
	PlayerInput GetKeyboardInput();
	void GetInput(Settings settings);
};

#endif // !PLAYER_H_
