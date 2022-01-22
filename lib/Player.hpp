#ifndef PLAYER_H_
#define PLAYER_H_

#include "State.hpp"

#if defined(__has_include) && __has_include(<termios.h>)
#include<termios.h>
#define STDIN_FILENO 0
#endif

// Handles player input
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
	SimplePlayerInput() {
		num1 = 0;
		num2 = 0;
		ingameCmd = '\0';
		isValidCmd = false;
	}

	ushort num1;
	ushort num2;
	char ingameCmd;
	bool isValidCmd;
};

struct Player {
	Player() {
		isAdvancedInputUsed = false;

		AdvancedInput = AdvancedPlayerInput::None;
		SimpleInput = SimplePlayerInput();

		// If using Lunix - save the default terminal settings
#if defined(__has_include) && __has_include(<termios.h>)
		tcgetattr(STDIN_FILENO, &canonicalTerminal);
		terminal = canonicalTerminal;
#endif

	}

	// Getters:
	const AdvancedPlayerInput& GetAdvancedInput();
	const SimplePlayerInput& GetSimpleInput();

	// Input type handlers:
	bool IsAdvancedInputSupported();
	void UseAdvancedInputSystem();
	void UseSimpleInputSystem();

	//
	bool GetInput();

private:

#if defined(__has_include) && __has_include(<termios.h>)
	struct termios terminal;
	struct termios canonicalTerminal;
#endif

	bool isAdvancedInputUsed;

	AdvancedPlayerInput GetAdvancedKeyboardInput();
	SimplePlayerInput GetSimpleKeyboardInput();
	AdvancedPlayerInput AdvancedInput;
	SimplePlayerInput SimpleInput;

};

#endif // !PLAYER_H_
