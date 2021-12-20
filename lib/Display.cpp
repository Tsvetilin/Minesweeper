#include "Display.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

void activateVirtualTerminal()
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(handleOut, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
	SetConsoleMode(handleOut, consoleMode);
}
#endif

/*
public:
	void WritePauseMenu(GameState state, ushort currentIndexSelected);
	void WriteMainMenu(GameState state, ushort currentIndexSelected);
	void WriteSettingsMenu(GameState state, ushort currentIndexSelected);
*/

void Display::WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board) {

	ushort rows = boardSize.boardRows;
	ushort cols = boardSize.boardCols;

	if (boardLook == BoardLook::Default) {

		for (ushort row = 0; row < rows; ++row)
		{
			for (ushort col = 0; col < cols; ++col)
			{
				std::cout << board[row][col];
			}

			std::cout << std::endl;
		}
	}
	else if (boardLook == BoardLook::Fancy) {
		// TODO: implement
	}
}

void Display::clearScreen() {

#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
	//std::cout<<"'\33c\e[3J'";
#else
	for (int i = 0; i < 128; ++i) {
		std::cout << std::endl;
	}
#endif

}

void Display::colorizeOutput(const char foregroundColor[] = "", const char backgroundColor[] = "") {
	if (foregroundColor[0] == '\0' && backgroundColor[0] == '\0') {
		std::cout << "\033[0m";
		return;
	}

	std::cout << "\033[3;" << backgroundColor << ";" << foregroundColor << "m";
}