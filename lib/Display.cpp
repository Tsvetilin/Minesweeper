#include "Display.hpp"
#include "Common.hpp"

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


void Display::WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board, char const * statusMessage) {
	clearScreen();

	ushort rows = boardSize.boardRows;
	ushort cols = boardSize.boardCols;

	if (boardLook == BoardLook::Default) {

		if (rows < 10 && cols < 10) {
			std::cout << "  ";
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1);
			}
			std::cout << std::endl;

		/*	for (ushort i = 0; i < cols + 2; i++)
			{
				std::cout << "-";
			}
			std::cout << std::endl;
			*/
			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << board[row][col];
				}

				std::cout << std::endl;
			}
		}
		else {
			std::cout << "   ";
			for (ushort i = 0; i < cols; i++)
			{
				if (i + 1 < 10) {
					std::cout << " " << (i + 1) << " ";
				}
				else {
					std::cout << (i + 1) << " ";
				}
			}
			std::cout << std::endl;

			for (ushort i = 0; i < 3 * cols + 2; i++)
			{
				std::cout << "-";
			}
			std::cout << std::endl;

			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << " " << board[row][col] << " ";
				}

				std::cout << std::endl;
			}
		}
	}
	else if (boardLook == BoardLook::Fancy) {
		// TODO: implement

		if (rows < 10 && cols < 10) {
			std::cout << "  ";
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1);
			}
			std::cout << std::endl;

		/*	for (ushort i = 0; i < cols + 2; i++)
			{
				std::cout << "-";
			}
			std::cout << std::endl;*/

			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << board[row][col];
				}

				std::cout << std::endl;
			}
		}
		else {
			std::cout << "   ";
			for (ushort i = 0; i < cols; i++)
			{
				if (i + 1 < 10) {
					std::cout << " " << (i + 1) << " ";
				}
				else {
					std::cout << (i + 1) << " ";
				}
			}
			std::cout << std::endl;

		/*	for (ushort i = 0; i < 3 * cols + 2; i++)
			{
				std::cout << "-";
			}
			std::cout << std::endl;
			*/
			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << " " << board[row][col] << " ";
				}

				std::cout << std::endl;
			}
		}

	}
}

void Display::WriteBoard(BoardLook boardLook, BoardSettings boardSize,ushort currentRowIndex, ushort currentColIndex, char** board, char const* statusMessage) {
	clearScreen();

	ushort rows = boardSize.boardRows;
	ushort cols = boardSize.boardCols;

	if (boardLook == BoardLook::Default) {

		if (rows < 10 && cols < 10) {
			std::cout << "  ";
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1);
			}
			std::cout << std::endl;

			/*	for (ushort i = 0; i < cols + 2; i++)
				{
					std::cout << "-";
				}
				std::cout << std::endl;
				*/
			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << board[row][col];
				}

				std::cout << std::endl;
			}
		}
		else {
			std::cout << "   ";
			for (ushort i = 0; i < cols; i++)
			{
				if (i + 1 < 10) {
					std::cout << " " << (i + 1) << " ";
				}
				else {
					std::cout << (i + 1) << " ";
				}
			}
			std::cout << std::endl;

			for (ushort i = 0; i < 3 * cols + 2; i++)
			{
				std::cout << "-";
			}
			std::cout << std::endl;

			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << " " << board[row][col] << " ";
				}

				std::cout << std::endl;
			}
		}
	}
	else if (boardLook == BoardLook::Fancy) {
		// TODO: implement

		if (rows < 10 && cols < 10) {
			std::cout << "  ";
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1);
			}
			std::cout << std::endl;

			/*	for (ushort i = 0; i < cols + 2; i++)
				{
					std::cout << "-";
				}
				std::cout << std::endl;*/

			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlueBG, WhiteFG);
					}
					std::cout << board[row][col];
					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlackBG, WhiteFG);
					}
				}

				std::cout << std::endl;
			}
		}
		else {
			std::cout << "   ";
			for (ushort i = 0; i < cols; i++)
			{
				if (i + 1 < 10) {
					std::cout << " " << (i + 1) << " ";
				}
				else {
					std::cout << (i + 1) << " ";
				}
			}
			std::cout << std::endl;

			/*	for (ushort i = 0; i < 3 * cols + 2; i++)
				{
					std::cout << "-";
				}
				std::cout << std::endl;
				*/
			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					std::cout << " " << board[row][col] << " ";
				}

				std::cout << std::endl;
			}
		}

	}
}


void Display::WritePauseMenu(ushort currentIndexSelected, char const * statusMessage) {}
void Display::WriteMainMenu(ushort currentIndexSelected, char const * statusMessage) {
	clearScreen();

	std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Start new game" << std::endl;
	std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Continue game" << std::endl;
	std::cout << (currentIndexSelected == 3 ? ">>" : "  ") << "3. Change settings" << std::endl;
	std::cout << (currentIndexSelected == 4 ? ">>" : "  ") << "4. Save & Exit" << std::endl;
}
void Display::WriteSettingsMenu(ushort currentIndexSelected, char const * statusMessage) {
	clearScreen();

	std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Board size" << std::endl;
	std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Board symbols" << std::endl;
	std::cout << (currentIndexSelected == 3 ? ">>" : "  ") << "3. Board uncover type" << std::endl;
	std::cout << (currentIndexSelected == 4 ? ">>" : "  ") << "4. Board control type" << std::endl;
	std::cout << (currentIndexSelected == 5 ? ">>" : "  ") << "5. Board look" << std::endl;
}

/*
enum class BoardLook {
	Default = 0,
	Fancy = 1,
};

enum class UncoverType {
	Default = 0, // As in original game
	Custom = 1,  // Uncover just the surrounding 8
};

enum class ControlType {
	PrimitiveInput = 0,
	AdvancedArrowInput = 1,
};
*/
void Display::WriteLookSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage) {
	clearScreen();
	if (currentUsedIndex == 0) {
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default look" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Fancy Look" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default look" << std::endl;
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Fancy Look" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
	}

}
void Display::WriteControlSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage) {
	clearScreen();
	if (currentUsedIndex == 0) {
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Standart keyboard typing input" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Advanced keyboard input" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Standart keyboard typing input" << std::endl;
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Advanced keyboard input" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
	}
}
void Display::WriteUncoverSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage) {
	clearScreen();

	if (currentUsedIndex == 0) {
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default uncovering as in the original game" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Custom uncovering the surrounding 8" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default uncovering as in the original game" << std::endl;
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Custom uncovering the surrounding 8" << std::endl;
		colorizeOutput(WhiteFG, BlackBG);
	}
}


void Display::WriteSizeSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<Size> sizes, ushort currentUsedIndex, char const * statusMessage) {
	clearScreen();

	for (ushort i = 0; i < options; i++)
	{
		if (currentUsedIndex == i) {
			colorizeOutput(GreenFG, WhiteBG);
			std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ") << (i + 1) << ". Rows:" << sizes[i].rows << "; Cols: " << sizes[i].cols << "; Bombs: " << sizes[i].rows << std::endl;
			colorizeOutput(WhiteFG, BlackBG);
		}
		else {
			std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ") << (i + 1) << ". Rows:" << sizes[i].rows << "; Cols: " << sizes[i].cols << "; Bombs: " << sizes[i].rows << std::endl;
		}
	}
}
void Display::WriteSymbolsSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<char*> sizes, ushort currentUsedIndex, char const * statusMessage) {
	clearScreen();

	for (ushort i = 0; i < options; i++)
	{
		if (currentUsedIndex == i) {
			colorizeOutput(GreenFG, WhiteBG);
			std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ") << (i + 1) << ". " << sizes[i] << std::endl;
		}
		else {
			std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ") << (i + 1) << ". " << sizes[i] << std::endl;
		}

	}
}

void Display::WriteExit(char const * statusMessage) {
	clearScreen();

	std::cout << "Exiting..." << std::endl;
}

void Display::clearScreen() {

#if defined (_WIN32)
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

void Display::colorizeOutput(const char foregroundColor[], const char backgroundColor[]) {
	if (foregroundColor[0] == '\0' && backgroundColor[0] == '\0') {
		std::cout << "\033[0m";
		return;
	}

	std::cout << "\033[3;" << backgroundColor << ";" << foregroundColor << "m";
}