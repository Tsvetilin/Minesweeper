#include "Display.hpp"
#include "Common.hpp"

#include <iostream>

void Display::writeBoardTop(bool isFancyBoard, bool isSmallBoard, ushort cols) {
	if (isFancyBoard) {
		if (isSmallBoard) {
			std::cout << " " << VerticalLine;
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1) << VerticalLine;
			}
			std::cout << std::endl;

			for (ushort i = 0; i < cols; i++)
			{
				std::cout << HorizontalLine << Crossing;
			}
			std::cout << HorizontalLine << VLLeft << std::endl;
		}
		else {
			std::cout << "   " << VerticalLine;
			for (ushort i = 0; i < cols; i++)
			{
				if (i + 1 < 10) {
					std::cout << " " << (i + 1) << " " << VerticalLine;
				}
				else {
					std::cout << (i + 1) << " " << VerticalLine;
				}
			}
			std::cout << std::endl;

			for (ushort i = 0; i < cols; i++)
			{
				std::cout << HorizontalLine << HorizontalLine << HorizontalLine << Crossing;
			}
			std::cout << HorizontalLine << HorizontalLine << HorizontalLine << VLLeft << std::endl;
		}
	}
	else {

		if (isSmallBoard) {
			std::cout << "  ";
			for (ushort i = 0; i < cols; i++)
			{
				std::cout << (i + 1);
			}
			std::cout << std::endl;
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
		}
	}
}

void Display::writeBoardBottom(bool isSmallBoard, ushort cols) {
	if (isSmallBoard) {
		for (ushort i = 0; i < cols; i++)
		{
			std::cout << HorizontalLine << Crossing;
		}
		std::cout << HorizontalLine << VLLeft << std::endl;
	}
	else {
		for (ushort i = 0; i < cols; i++)
		{
			std::cout << HorizontalLine << HorizontalLine << HorizontalLine << Crossing;
		}
		std::cout << HorizontalLine << HorizontalLine << HorizontalLine << VLLeft << std::endl;
	}

}


void Display::WriteBoard(BoardLook boardLook, BoardSettings boardSize, int currentRowIndex, int currentColIndex, const char* const* const board, const char* const statusMessage) {
	clearScreen();

	ushort rows = boardSize.boardRows;
	ushort cols = boardSize.boardCols;

	if (boardLook == BoardLook::Default) {

		if (rows < 10 && cols < 10) {
			writeBoardTop(false, true, cols);
			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					bool isColorized = false;
					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlueBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.bombMarked) {
						colorizeOutput(YellowBG, BlackFG);
						isColorized = true;
					}
					std::cout << board[row][col];
					if (isColorized) {
						colorizeOutput();
					}

				}

				std::cout << std::endl;
			}
		}
		else {
			writeBoardTop(false, false, cols);
			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					bool isColorized = false;
					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlueBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.bombMarked) {
						colorizeOutput(YellowBG, BlackFG);
						isColorized = true;
					}
					std::cout << " " << board[row][col] << " ";
					if (isColorized) {
						colorizeOutput();
					}
				}

				std::cout << std::endl;
			}
		}
	}
	else if (boardLook == BoardLook::Fancy) {
		/*
		╔═══╦═══╗
		║   ║   ║
		╠═══╬═══╣
		║   ║   ║
		╚═══╩═══╝
		#define VLLeft (char)185
		#define VerticalLine (char)186
		#define URAngle (char)187
		#define DRAngle (char)188
		#define DLAngle (char)200
		#define ULAngle (char)201
		#define HLUp (char)202
		#define HLDown (char)203
		#define VLRight (char)204
		#define HorizontalLine (char)205
		#define Crossing (char)206
		*/

		if (rows < 10 && cols < 10) {
			writeBoardTop(true, true, cols);
			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << VerticalLine;
				for (ushort col = 0; col < cols; ++col)
				{
					bool isColorized = false;

					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlueBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.bombMarked) {
						colorizeOutput(YellowBG, BlackFG);
						isColorized = true;
					}

					if (board[row][col] == boardSize.covered) {
						std::cout << " ";
					}
					else {
						std::cout << board[row][col];
					}

					if (isColorized) {
						colorizeOutput();
					}

					std::cout << VerticalLine;

				}

				std::cout << std::endl;
				writeBoardBottom(true, cols);

			}
		}
		else {
			writeBoardTop(true, false, cols);
			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << " " << (row + 1) << VerticalLine;
				for (ushort col = 0; col < cols; ++col)
				{
					bool isColorized = false;
					if (row == currentRowIndex && col == currentColIndex) {
						colorizeOutput(BlueBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isColorized = true;
					}
					else if (board[row][col] == boardSize.bombMarked) {
						colorizeOutput(YellowBG, BlackFG);
						isColorized = true;
					}
					std::cout << " " << board[row][col] << " ";
					if (isColorized) {
						colorizeOutput();
					}
					std::cout << VerticalLine;
				}

				std::cout << std::endl;
				writeBoardBottom(false, cols);
			}
		}

	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}

void Display::WriteFinishBoard(BoardLook boardLook, BoardSettings boardSize, const char* const* const playerBoard, const char* const* const board, const char* const statusMessage) {
	clearScreen();

	ushort rows = boardSize.boardRows;
	ushort cols = boardSize.boardCols;

	if (boardLook == BoardLook::Default) {
		if (rows < 10 && cols < 10) {
			writeBoardTop(false, true, cols);

			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{
					bool isResetNeeded = false;
					bool printBomb = false;
					if (playerBoard[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombRevealed) {
						printBomb = true;
						colorizeOutput(RedBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(YellowBG, BlackFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombMarked) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						else {
							colorizeOutput(MagentaBG, BlackFG);
						}
						isResetNeeded = true;
					}
					else if (!printBomb) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					if (printBomb) {
						std::cout << boardSize.bombRevealed;
					}
					else {
						std::cout << playerBoard[row][col];
					}

					if (isResetNeeded) {
						colorizeOutput();
					}
				}

				std::cout << std::endl;
			}
		}
		else {
			writeBoardTop(true, false, cols);

			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << (row + 1) << "|";
				for (ushort col = 0; col < cols; ++col)
				{

					bool isResetNeeded = false;
					bool printBomb = false;
					if (playerBoard[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombRevealed) {
						printBomb = true;
						colorizeOutput(RedBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(YellowBG, BlackFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombMarked) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						else {
							colorizeOutput(MagentaBG, BlackFG);
						}
						isResetNeeded = true;
					}
					else if (!printBomb) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					if (printBomb) {
						std::cout << " " << boardSize.bombRevealed << " ";
					}
					else {
						std::cout << " " << playerBoard[row][col] << " ";
					}

					if (isResetNeeded) {
						colorizeOutput();
					}
				}

				std::cout << std::endl;
			}
		}
	}
	else if (boardLook == BoardLook::Fancy) {

		if (rows < 10 && cols < 10) {

			writeBoardTop(true, true, cols);

			for (ushort row = 0; row < rows; ++row)
			{
				std::cout << (row + 1) << VerticalLine;
				for (ushort col = 0; col < cols; ++col)
				{
					bool isResetNeeded = false;
					bool printBomb = false;
					if (playerBoard[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombRevealed) {
						printBomb = true;
						colorizeOutput(RedBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(YellowBG, BlackFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombMarked) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						else {
							colorizeOutput(MagentaBG, BlackFG);
						}
						isResetNeeded = true;
					}
					else if (!printBomb) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					if (printBomb) {
						std::cout << boardSize.bombRevealed;
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						std::cout << " ";
					}
					else {
						std::cout << playerBoard[row][col];
					}


					if (isResetNeeded) {
						colorizeOutput();
					}
					std::cout << VerticalLine;
				}

				std::cout << std::endl;
				writeBoardBottom(true, cols);
			}
		}
		else {
			writeBoardTop(true, false, cols);

			for (ushort row = 0; row < rows; ++row)
			{
				if (row + 1 < 10) {
					std::cout << " ";
				}
				std::cout << " " << (row + 1) << VerticalLine;

				for (ushort col = 0; col < cols; ++col)
				{

					bool isResetNeeded = false;
					bool printBomb = false;
					if (playerBoard[row][col] == boardSize.uncovered) {
						colorizeOutput(BrightBlackBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombRevealed) {
						printBomb = true;
						colorizeOutput(RedBG, WhiteFG);
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(YellowBG, BlackFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					else if (playerBoard[row][col] == boardSize.bombMarked) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						else {
							colorizeOutput(MagentaBG, BlackFG);
						}
						isResetNeeded = true;
					}
					else if (!printBomb) {
						if (board[row][col] == boardSize.bombRevealed) {
							colorizeOutput(GreenBG, WhiteFG);
							printBomb = true;
						}
						isResetNeeded = true;
					}
					if (printBomb) {
						std::cout << " " << boardSize.bombRevealed << " ";
					}
					else if (playerBoard[row][col] == boardSize.covered) {
						std::cout << "   ";
					}
					else {
						std::cout << " " << playerBoard[row][col] << " ";
					}

					if (isResetNeeded) {
						colorizeOutput();
					}
					std::cout << VerticalLine;
				}

				std::cout << std::endl;
				writeBoardBottom(false, cols);
			}
		}
	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}


void Display::WritePauseMenu(short currentIndexSelected, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Resume" << std::endl;
	std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Save and Exit" << std::endl;

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}

void Display::WriteMainMenu(short currentIndexSelected, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Start new game" << std::endl;
	std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Continue game" << std::endl;
	std::cout << (currentIndexSelected == 3 ? ">>" : "  ") << "3. Change settings" << std::endl;
	std::cout << (currentIndexSelected == 4 ? ">>" : "  ") << "4. Save & Exit" << std::endl;

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}

void Display::WriteSettingsMenu(short currentIndexSelected, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Board size" << std::endl;
	std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Board symbols" << std::endl;
	std::cout << (currentIndexSelected == 3 ? ">>" : "  ") << "3. Board uncover type" << std::endl;
	std::cout << (currentIndexSelected == 4 ? ">>" : "  ") << "4. Board control type" << std::endl;
	std::cout << (currentIndexSelected == 5 ? ">>" : "  ") << "5. Board look" << std::endl;

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}

void Display::WriteLookSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	if (currentUsedIndex == 0) {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "1. Default look" << std::endl;
		colorizeOutput();
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Fancy Look" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default look" << std::endl;
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "2. Fancy Look" << std::endl;
		colorizeOutput();
	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}
void Display::WriteControlSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	if (currentUsedIndex == 0) {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "1. Standart keyboard typing input" << std::endl;
		colorizeOutput();
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ") << "2. Advanced keyboard input" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Standart keyboard typing input" << std::endl;
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "2. Advanced keyboard input" << std::endl;
		colorizeOutput();
	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}
void Display::WriteUncoverSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	if (currentUsedIndex == 0) {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "1. Default uncovering as in the original game" << std::endl;
		colorizeOutput();
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ");
		std::cout << "2. Custom uncovering the surrounding 8" << std::endl;
	}
	else {
		std::cout << (currentIndexSelected == 1 ? ">>" : "  ") << "1. Default uncovering as in the original game" << std::endl;
		std::cout << (currentIndexSelected == 2 ? ">>" : "  ");
		colorizeOutput(GreenFG, WhiteBG);
		std::cout << "2. Custom uncovering the surrounding 8" << std::endl;
		colorizeOutput();
	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}


void Display::WriteSizeSettingsMenu(short currentIndexSelected, ushort options, std::vector<Size*> sizes, ushort currentUsedIndex, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	for (ushort i = 0; i < options; ++i)
	{
		std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ");
		if (currentUsedIndex == i) {
			colorizeOutput(GreenFG, WhiteBG);
			std::cout << (i + 1) << ". Rows:" << sizes[i]->rows << "; Cols: " << sizes[i]->cols << "; Bombs: " << sizes[i]->rows << std::endl;
			colorizeOutput(WhiteFG, BlackBG);
		}
		else {
			std::cout << (i + 1) << ". Rows:" << sizes[i]->rows << "; Cols: " << sizes[i]->cols << "; Bombs: " << sizes[i]->rows << std::endl;
		}
	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}
void Display::WriteSymbolsSettingsMenu(short currentIndexSelected, ushort options, std::vector<char*> sizes, ushort currentUsedIndex, const char* const statusMessage) {
	clearScreen();
	writeHeader();

	for (ushort i = 0; i < options; ++i)
	{
		std::cout << (currentIndexSelected == i + 1 ? ">>" : "  ");
		if (currentUsedIndex == i) {

			colorizeOutput(GreenFG, WhiteBG);
			std::cout << (i + 1) << ". " << sizes[i] << std::endl;
			colorizeOutput();
		}
		else {
			std::cout << (i + 1) << ". " << sizes[i] << std::endl;
		}

	}

	std::cout << std::endl << std::endl << statusMessage << std::endl;
}

void Display::WriteExit(const char* const statusMessage) {
	clearScreen();

	std::cout << "Exiting..." << std::endl << std::endl;
}

void Display::WriteManual() {
	clearScreen();
	writeHeader();

	std::cout << "Welcome, fellow gamer!" << std::endl;
	std::cout << std::endl;
	std::cout << "Here are some things you need to know before start playing:" << std::endl;
	std::cout << "0. All of the settings and features listed below are accesible via the menu!" << std::endl;
	std::cout << "1. The game has two working modes:" << std::endl;
	std::cout << "		 a. Controlling via arrow keys and the key presses. This type of control uses Up/Down/Left/Right keys to navigate, as well as Enter/Escape buttons. Some commands require other keys to be pressed. IMPORTANT: Using English alphabet is required to be able to detect the commands!" << std::endl;
	std::cout << "		 b. Controlling via writing to the console." << std::endl;
	std::cout << "2. There are two styles of the game:" << std::endl;
	std::cout << "		 a. Borderless: minimalistic." << std::endl;
	std::cout << "		 b. Borders: using spacial character. IMPORTANT: Not all consoles may support those!" << std::endl;
	std::cout << "3. There are two types of gameplay:" << std::endl;
	std::cout << "		 a. Standard: as in the original game." << std::endl;
	std::cout << "		 b. Custom: revealing just the surrounding 8 cells there are no bombs nearby." << std::endl;
	std::cout << "4. There are several board size presets." << std::endl;
	std::cout << "5. There are several symbols presets, representing the different. IMPORTANT: Not all consoles may support those!" << std::endl;
	std::cout << std::endl;
	std::cout << "You can always go Back or Pause by pressing Escape or Q (if 1a) or Write Q (if 1b)!" << std::endl;
	std::cout << std::endl;
	std::cout << "Note: Not all functionality may be supported on your OS and the console you are using!" << std::endl;
	std::cout << std::endl;
	std::cout << "Press Escape or Q (if 1a) or Write Q (if 1b) to continue!" << std::endl;
	std::cout << std::endl;

}

void Display::writeHeader() {
	std::cout << "         \033[1m MINESWEEPER\033[0m " << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void Display::clearScreen() {

	std::cout << "\033[2J\033[1;1H";

	/* system calls forbidden
	#if defined (_WIN32)
		system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
	#elif defined (__APPLE__)
		system("clear");
	#else
		for (int i = 0; i < 128; ++i) {
			std::cout << std::endl;
		}
	#endif
	*/

}

// No params = set to default
void Display::colorizeOutput(const char foregroundColor[], const char backgroundColor[]) {
	if (foregroundColor[0] == '\0' && backgroundColor[0] == '\0') {
		std::cout << "\033[0;0m";
		return;
	}

	std::cout << "\033[3;" << backgroundColor << ";" << foregroundColor << "m";
}