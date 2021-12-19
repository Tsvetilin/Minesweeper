#include "Display.hpp"

#include <iostream>

/*
public:
	void WritePauseMenu(GameState state, ushort currentIndexSelected);
	void WriteMainMenu(GameState state, ushort currentIndexSelected);
	void WriteSettingsMenu(GameState state, ushort currentIndexSelected);
	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board);

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[] = "", const char backgroundColor[]= "");
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
}