#include "Player.hpp"

#include <iostream>

#define STDIN_FILENO 0

bool Player::IsAdvancedInputSupported() {

#if defined (__has_include) && (__has_include(<conio.h>) || __has_include(<termios.h>))
	return true;
#else
	return false;
#endif

}

#if defined (__has_include)

#if __has_include(<conio.h>)

#include <conio.h>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ARROW_SEQUENCE 224
#define ESCAPE 27
#define ENTER 13

AdvancedPlayerInput Player::GetAdvancedKeyboardInput() {
	int c = _getch();

	if (c == ARROW_SEQUENCE) {
		switch (c = _getch())
		{
		case KEY_UP: // H
			return AdvancedPlayerInput::UpArrow;
		case KEY_DOWN: // K
			return AdvancedPlayerInput::DownArrow;
		case KEY_LEFT: // M
			return AdvancedPlayerInput::LeftArrow;
		case KEY_RIGHT: // P
			return AdvancedPlayerInput::RightArrow;
		default:
			return AdvancedPlayerInput::None;
		}
	}
	else if (c == ENTER) {
		return AdvancedPlayerInput::Select;
	}
	else if (c == ESCAPE) {
		return AdvancedPlayerInput::Escape;
	}
	else if (c == MarkChar || c == MarkChar + LOWER_TO_UPPER_TRANSFORM) {
		return AdvancedPlayerInput::MarkBomb;
	}
	else if (c == RevealChar || c == RevealChar + LOWER_TO_UPPER_TRANSFORM) {
		return AdvancedPlayerInput::Reveal;
	}
	else if (c == QuitChar || c == QuitChar + LOWER_TO_UPPER_TRANSFORM) {
		return AdvancedPlayerInput::Escape;
	}

	return AdvancedPlayerInput::None;

}


#elif __has_include(<termios.h>)

#include <termios.h>

AdvancedPlayerInput Player::GetAdvancedKeyboardInput() {

	char buff[3];
	buff[0] = '\0';
	buff[1] = '\0';
	buff[2] = '\0';

	int i = 0;
	char c = '\0';
	int n = 0;

	// Read at least one character.
	while (n < 1) {
		n = read(STDIN_FILENO, &c, 1);
	}

	while (i < 3 && n > 0) {
		buff[i++] = c;
		n = read(fileno(stdin), &c, 1);
	}

	AdvancedPlayerInput input = AdvancedPlayerInput::None;

	if (buff[0] == 27) {
		if (buff[1] == 91) {
			if (buff[2] == 65) {
				input = AdvancedPlayerInput::UpArrow;
			}
			if (buff[2] == 66) {
				input = AdvancedPlayerInput::DownArrow;
			}
			if (buff[2] == 67) {
				input = AdvancedPlayerInput::RightArrow;
			}
			if (buff[2] == 68) {
				input = AdvancedPlayerInput::LeftArrow;
			}
		}
		else if (buff[1] == buff[2] && buff[1] == '\0') {
			input = AdvancedPlayerInput::Escape;
		}
	}
	else if (buff[1] == buff[2] && buff[1] == '\0') {
		if (buff[2] == 10) {
			input = AdvancedPlayerInput::Select;
		}
		else if (buff[2] == 113 || buff[2] == 81) {
			input = AdvancedPlayerInput::Escape;
		}
		else if (buff[2] == 70 || buff[2] == 102) {
			input = AdvancedPlayerInput::MarkBomb;
		}
		else if (buff[2] == 114 || buff[2] == 82) {
			input = AdvancedPlayerInput::Reveal;
		}
	}

	return input;

}

#else

AdvancedPlayerInput Player::GetAdvancedKeyboardInput() {
	return AdvancedPlayerInput::None;
}

#endif

#endif

void Player::UseAdvancedInputSystem() {

	if (Player::IsAdvancedInputSupported()) {
		isAdvancedInputUsed = true;

#if defined(__has_include) && __has_include(<termios.h>)

		// Black magic to prevent Linux from buffering keystrokes.
		tcgetattr(STDIN_FILENO, &terminal);
		terminal.c_lflag &= ~ICANON;
		terminal.c_cc[VTIME] = 0;
		terminal.c_cc[VMIN] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal);

#endif
	}
}

void Player::UseSimpleInputSystem() {

#if defined(__has_include) && __has_include(<termios.h>)

	if (isAdvancedInputUsed) {
		tcsetattr(STDIN_FILENO, TCSANOW, &canonicalTerminal);
	}

#endif

	isAdvancedInputUsed = false;
}

bool Player::GetInput() {
	if (isAdvancedInputUsed) {
		AdvancedInput = GetAdvancedKeyboardInput();
		return AdvancedInput != AdvancedPlayerInput::None;
	}
	else {
		SimpleInput = GetSimpleKeyboardInput();
		return SimpleInput.isValidCmd;
	}
}

SimplePlayerInput Player::GetSimpleKeyboardInput() {

	SimplePlayerInput result;
	result.isValidCmd = false;

	char line[COMMAND_MAX_LENGTH] = {};
	std::cin.getline(line, COMMAND_MAX_LENGTH);

	ushort ind = 0;
	ushort words = 1;

	// trim start 
	while (line[ind] != '\0') {
		if (line[ind] != ' ') {
			break;
		}
		++ind;
	}

	while (line[ind] != '\0') {
		++ind;
		if (line[ind] == ' ') {
			if (line[ind - 1] == ' ') {
				continue;
			}

			++words;
		}

	}

	//trim end
	if (ind > 0 && line[ind - 1] == ' ') {
		--words;
	}

	// TODO: Support for more complex cmds

	ind = 0;
	// trim start 
	while (line[ind] != '\0') {
		if (line[ind] != ' ') {
			break;
		}
		++ind;
	}


	if (words == 1) {
		if ((line[ind] == QuitChar || line[ind] == QuitChar + LOWER_TO_UPPER_TRANSFORM) && (line[ind + 1] == ' ' || line[ind + 1] == '\0')) {
			result.isValidCmd = true;
			result.ingameCmd = 'q';
		}
		else if (line[0] >= '0' && line[0] <= '9') {
			result.isValidCmd = true;
			result.ingameCmd = line[0];
		}
	}
	else if (words == 2)
	{
		//?
	}
	else if (words == 3) {
		ushort n1 = 0, n2 = 0;
		bool isW2 = false;
		bool isW3 = false;
		int currentIndex = 0;
		while (line[currentIndex] == ' ') {
			++currentIndex;
		}
		while (true) {
			if (line[currentIndex] == ' ') {
				break;
			}
			if (line[currentIndex] >= '0' && line[currentIndex] <= '9') {
				n1 = n1 * 10 + line[currentIndex] - '0';
			}
			else {
				return result;
			}
			++currentIndex;
		}

		while (line[currentIndex] == ' ') {
			++currentIndex;
		}

		while (true) {
			if (line[currentIndex] == ' ') {
				break;
			}
			if (line[currentIndex] >= '0' && line[currentIndex] <= '9') {
				n2 = n2 * 10 + line[currentIndex] - '0';
			}
			else {
				return result;
			}
			++currentIndex;
		}

		while (line[currentIndex] == ' ') {
			++currentIndex;
		}
		if (line[currentIndex + 1] != ' ' && line[currentIndex + 1] != '\0') {
			return result;
		}
		if (line[currentIndex] == MarkChar || line[currentIndex] == MarkChar + LOWER_TO_UPPER_TRANSFORM)
		{
			result.ingameCmd = MarkChar;
		}
		else if (line[currentIndex] == RevealChar || line[currentIndex] == MarkChar + LOWER_TO_UPPER_TRANSFORM) {
			result.ingameCmd = RevealChar;
		}
		else {
			return result;
		}

		result.num1 = n1;
		result.num2 = n2;
		result.isValidCmd = true;
	}
	else {
		//?
	}

	return result;
}


const AdvancedPlayerInput& Player::GetAdvancedInput() {
	return AdvancedInput;
}

const SimplePlayerInput& Player::GetSimpleInput() {
	return SimpleInput;
}