#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "State.hpp"

#if defined(__has_include) && __has_include(<termios.h>)
#include<termios.h>
#endif

// Handles Player input

enum class AdvancedPlayerInput {
	None = 0,
	UpArrow = 1,
	DownArrow = 2,
	LeftArrow = 3,
	RightArrow = 4,
	Select = 5,
	Escape = 6,
	Save = 7,
	MarkBomb = 8,
	Reveal = 9,
};

struct SimplePlayerInput {
	ushort num1;
	ushort num2;
	char cmd[COMMAND_MAX_LENGTH];
	char ingameCmd;
	bool isValidCmd;
};

struct Player {
	Player() {
		AdvancedInput = AdvancedPlayerInput::None;
		SimpleInput = SimplePlayerInput();

#if defined(__has_include) && __has_include(<termios.h>)
		tcgetattr(STDIN_FILENO, &canonicalTerminal);
		terminal = canonicalTerminal;
#endif

	}

public:
	const AdvancedPlayerInput& GetAdvancedInput();
	const SimplePlayerInput& GetSimpleInput();
	bool IsAdvancedInputSupported();
	void UseAdvancedInputSystem(); // TODO: set linux terminal termios read options
	void UseSimpleInputSystem();// TODO: set linux terminal termios read options
	bool GetInput();

private:

#if defined(__has_include) && __has_include(<termios.h>)
	struct termios terminal;
	struct termios canonicalTerminal;
#endif

	bool isAdvancedInputUsed = false;

	AdvancedPlayerInput GetAdvancedKeyboardInput();
	SimplePlayerInput GetSimpleKeyboardInput();
	AdvancedPlayerInput AdvancedInput;
	SimplePlayerInput SimpleInput;

};

#endif // !PLAYER_H_
