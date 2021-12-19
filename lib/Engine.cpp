#include "Engine.hpp"

/*
struct Engine {
public:
	char** board;
	char** playerBoard;

	void PerformMove(ushort row, ushort col);
	bool HasGameFinished();
	bool IsWin();
};
*/

void Engine::GenerateBoard(BoardSettings boardSettings) {

	ushort rows = boardSettings.boardRows;
	ushort cols = boardSettings.boardCols;
	ushort bombsCount = boardSettings.bombsCount;

	initializeBoard(rows, cols);
	fillBoard(rows, cols, boardSettings.uncovered);

	for (ushort i = 0; i < bombsCount; ++i)
	{
		ushort rowIndex = 0, colIndex = 0;
		do {
			ushort rowIndex = GenerateRandomNumber(1, rows) - 1;
			ushort colIndex = GenerateRandomNumber(1, cols) - 1;
		} while (board[rowIndex][colIndex] == boardSettings.bombRevealed);

		board[rowIndex][colIndex] = boardSettings.bombRevealed;
	}
}

void Engine::initializeBoard(const ushort rows, const ushort cols) {

	Engine::board = new char* [rows];
	Engine::playerBoard = new char* [rows];

	for (ushort row = 0; row < rows; ++row)
	{
		Engine::playerBoard[row] = new char[cols];
		Engine::board[row] = new char[cols];
	}
}

void Engine::deleteBoard(const ushort rows) {

	for (ushort row = 0; row < rows; ++row)
	{
		delete[] Engine::playerBoard[row];
		delete[] Engine::board[row];
	}

	delete[] board;
	delete[] playerBoard;
}

void Engine::fillBoard(const ushort rows, const ushort cols, const char uncoveredChar) {

	for (ushort row = 0; row < rows; ++row)
	{
		for (ushort col = 0; col < cols; ++col)
		{
			Engine::board[row][col] = uncoveredChar;
			Engine::playerBoard[row][col] = uncoveredChar;
		}
	}
}