#include "Player.hpp"


bool Player::IsAdvancedInputSupported() {

#if defined __has_include && (__has_include(<conio.h>) || __has_include(<termios.h>))
	return true;
#else
	return false;
#endif

}


#if defined __has_include

#if __has_include(<conio.h>)

#include <conio.h>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

PlayerInput Player::GetKeyboardInput() {

	int c, ex;
	c = getch();

	PlayerInput input = PlayerInput::None;

	if (c && c != 224)
	{
		return input;
	}

	switch (ex = getch())
	{
	case KEY_UP:// H
		input = PlayerInput::UpArrow;//key up
		break;
	case KEY_DOWN: // K
		input = PlayerInput::DownArrow;   // key down
		break;
	case KEY_LEFT:// M
		input = PlayerInput::LeftArrow;  // key left
		break;
	case KEY_RIGHT: // P
		input = PlayerInput::RightArrow;   // key right
		break;
	default:
		// not arrow
		break;
	}

	return input;
}


#elif __has_include(<termios.h>)

#include <termios.h>
#define STDIN_FILENO 0

PlayerInput Player::GetKeyboardInput() {

	// Black magic to prevent Linux from buffering keystrokes.
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);

	// Once the buffering is turned off, the rest is simple
	char c, d, e;
	cin >> c;
	cin >> d;
	cin >> e;

	PlayerInput input = PlayerInput::None;
	// Using 3 char type, Cause up down right left consist with 3 character
	if ((c == 27) && (d = 91)) {
		if (e == 65) {
			input = PlayerInput::UpArrow;
		}
		if (e == 66) {
			input = PlayerInput::DownArrow;
		}
		if (e == 67) {
			input = PlayerInput::RightArrow;
		}
		if (e == 68) {
			input = PlayerInput::LeftArrow;
		}
	}
	return input;
}
#endif

#endif

