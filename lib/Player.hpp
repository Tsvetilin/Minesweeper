#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "State.hpp"

// Handles Player input

/*enum class PlayerInput {
	None = 0,
	Quit = 1,
	Save = 2,
	Escape = 3,
	Select = 4,
	IngameInput = 5,
	SettingsInput = 6,
};
*/
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

// move=None & relative coords when using advanced input
/*struct PlayerIngameCommand {
	Move move;
	short row;
	short col;
};*/

struct Player {
	Player() {
		AdvancedInput = AdvancedPlayerInput::None;
		SimpleInput = SimplePlayerInput();
	}

public:
	//PlayerIngameCommand PlayerIngameCommand;
	const AdvancedPlayerInput& GetAdvancedInput();
	const SimplePlayerInput& GetSimpleInput();
	bool IsAdvancedInputSupported();
	void UseAdvancedInputSystem(); // TODO: set linux terminal termios read options
	void UseSimpleInputSystem();// TODO: set linux terminal termios read options
	bool GetInput();

private:
	bool isAdvancedInputUsed = false;
	AdvancedPlayerInput GetAdvancedKeyboardInput();
	SimplePlayerInput GetSimpleKeyboardInput();
	AdvancedPlayerInput AdvancedInput;
	SimplePlayerInput SimpleInput;

};

#endif // !PLAYER_H_
