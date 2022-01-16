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
		case KEY_UP:// H
			return AdvancedPlayerInput::UpArrow;//key up
		case KEY_DOWN: // K
			return AdvancedPlayerInput::DownArrow;   // key down
		case KEY_LEFT:// M
			return AdvancedPlayerInput::LeftArrow;  // key left
		case KEY_RIGHT: // P
			return AdvancedPlayerInput::RightArrow;   // key right
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
	else if (c == 'f' || c == 'F') {
		return AdvancedPlayerInput::MarkBomb;
	}
	else if (c == 'r' || c == 'R') {
		return AdvancedPlayerInput::Reveal;
	}

	return AdvancedPlayerInput::None;

}


#elif __has_include(<termios.h>)

#include <termios.h>

AdvancedPlayerInput Player::GetAdvancedKeyboardInput() {

	char c, d, e;
	cin >> c;
	cin >> d;
	cin >> e;

	AdvancedPlayerInput input = AdvancedPlayerInput::None;
	// Using 3 char type, Cause up down right left consist with 3 character
	if ((c == 27) && (d = 91)) {
		if (e == 65) {
			input = AdvancedPlayerInput::UpArrow;
		}
		if (e == 66) {
			input = AdvancedPlayerInput::DownArrow;
		}
		if (e == 67) {
			input = AdvancedPlayerInput::RightArrow;
		}
		if (e == 68) {
			input = AdvancedPlayerInput::LeftArrow;
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

#if __has_include(<termios.h>)

		// Black magic to prevent Linux from buffering keystrokes.
		struct termios t;
		tcgetattr(STDIN_FILENO, &t);
		t.c_lflag &= ~ICANON;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);

#endif
	}
}

void Player::UseSimpleInputSystem() {
	isAdvancedInputUsed = false;

#if __has_include(<termios.h>)

	// Black magic to prevent Linux from buffering keystrokes.
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);

#endif
}

bool Player::GetInput() {
	if (isAdvancedInputUsed) {
		AdvancedInput = GetAdvancedKeyboardInput();
		return AdvancedInput != AdvancedPlayerInput::None;
	}
	else {
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

				--words;
			}

		}

		//trim end
		if (ind > 0 && line[ind - 1] == ' ') {
			--words;
		}

		if (words == 1) {
			if (strcmp(line, "quit") == 0) {

			}
		}
		else if (words == 2)
		{

		}

		else if (words == 3) {

		}
	}
}