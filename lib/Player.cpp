#include "Player.hpp"

#include <iostream>

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

AdvancedPlayerInput Player::GetAdvancedKeyboardInput() {
	int c = _getch();

	if (c == ARROW_SEQUENCE_WIN) {
		switch (c = _getch())
		{
		case KEY_UP_WIN:
			return AdvancedPlayerInput::UpArrow;
		case KEY_DOWN_WIN:
			return AdvancedPlayerInput::DownArrow;
		case KEY_LEFT_WIN:
			return AdvancedPlayerInput::LeftArrow;
		case KEY_RIGHT_WIN:
			return AdvancedPlayerInput::RightArrow;
		default:
			return AdvancedPlayerInput::None;
		}
	}
	else if (c == ENTER_WIN) {
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
#include <unistd.h>

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
		n = read(STDIN_FILENO, &c, 1);
	}

	AdvancedPlayerInput input = AdvancedPlayerInput::None;

	if (buff[0] == ESCAPE) {
		if (buff[1] == ARROW_SEQUENCE_LIN) {
			if (buff[2] == KEY_UP_LIN) {
				input = AdvancedPlayerInput::UpArrow;
			}
			if (buff[2] == KEY_DOWN_LIN) {
				input = AdvancedPlayerInput::DownArrow;
			}
			if (buff[2] == KEY_RIGHT_LIN) {
				input = AdvancedPlayerInput::RightArrow;
			}
			if (buff[2] == KEY_LEFT_LIN) {
				input = AdvancedPlayerInput::LeftArrow;
			}
		}
		else if (buff[1] == buff[2] && buff[1] == '\0') {
			input = AdvancedPlayerInput::Escape;
		}
	}
	else if (buff[1] == buff[2] && buff[1] == '\0') {
		if (buff[0] == ENTER_LIN) {
			input = AdvancedPlayerInput::Select;
		}
		else if (buff[0] == QuitChar || buff[0] == QuitChar + LOWER_TO_UPPER_TRANSFORM) {
			input = AdvancedPlayerInput::Escape;
		}
		else if (buff[0] == MarkChar || buff[0] == MarkChar + LOWER_TO_UPPER_TRANSFORM) {
			input = AdvancedPlayerInput::MarkBomb;
		}
		else if (buff[0] == RevealChar || buff[0] == RevealChar + LOWER_TO_UPPER_TRANSFORM) {
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

		// Prevent buffering keystrokes
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
	// Restore default terminal settings
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
	
	// TODO: Support for more complex cmds

	SimplePlayerInput result = SimplePlayerInput();

	char line[COMMAND_MAX_LENGTH] = {};
	std::cin.getline(line, COMMAND_MAX_LENGTH);

	ushort ind = 0;
	ushort words = 1;

	// trim start 
	trimTextInput(line, ind);

	// count words
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

	ind = 0;
	// trim start 
	trimTextInput(line, ind);

	if (words == 1) {
		if ((line[ind] == QuitChar || line[ind] == QuitChar + LOWER_TO_UPPER_TRANSFORM) &&
			(line[ind + 1] == ' ' || line[ind + 1] == '\0')) {
			result.isValidCmd = true;
			result.ingameCmd = QuitChar;
		}
		else if (line[0] >= '0' && line[0] <= '9') {
			result.isValidCmd = true;
			result.ingameCmd = line[0];
		}
	}
	else if (words == 3) {
		ushort n1 = 0, n2 = 0;

		while (true) {
			if (line[ind] == ' ') {
				break;
			}
			if (line[ind] >= '0' && line[ind] <= '9') {
				n1 = n1 * 10 + line[ind] - '0';
			}
			else {
				return result;
			}
			++ind;
		}

		trimTextInput(line, ind);

		while (true) {
			if (line[ind] == ' ') {
				break;
			}
			if (line[ind] >= '0' && line[ind] <= '9') {
				n2 = n2 * 10 + line[ind] - '0';
			}
			else {
				return result;
			}
			++ind;
		}

		trimTextInput(line, ind);

		if (line[ind + 1] != ' ' && line[ind + 1] != '\0') {
			return result;
		}
		if (line[ind] == MarkChar || line[ind] == MarkChar + LOWER_TO_UPPER_TRANSFORM){
			result.ingameCmd = MarkChar;
		}
		else if (line[ind] == RevealChar || line[ind] == RevealChar + LOWER_TO_UPPER_TRANSFORM) {
			result.ingameCmd = RevealChar;
		}
		else {
			return result;
		}

		result.num1 = n1;
		result.num2 = n2;
		result.isValidCmd = true;
	}

	return result;
}

const AdvancedPlayerInput& Player::GetAdvancedInput() {
	return AdvancedInput;
}

const SimplePlayerInput& Player::GetSimpleInput() {
	return SimpleInput;
}

#ifdef _WIN32
#include <windows.h>

void Player::activateVirtualTerminal()
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(handleOut, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
	SetConsoleMode(handleOut, consoleMode);
}
#endif
