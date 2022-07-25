#include "Board.hpp"


bool Engine::isNumber(const ushort row, const ushort col, const char *numbers)
{
	ushort i = 0;
	while (i < NUMBERS_CHAR_ARRAY_SIZE)
	{
		if (Engine::playerBoard[row][col] == numbers[i])
		{
			return true;
		}

		++i;
	}

	return false;
}

void Engine::initializeBoard(const ushort rows, const ushort cols)
{

	Engine::board = new char *[rows];
	Engine::playerBoard = new char *[rows];
	Engine::visitedBoard = new bool *[rows];

	for (ushort row = 0; row < rows; ++row)
	{
		Engine::playerBoard[row] = new char[cols];
		Engine::board[row] = new char[cols];
		Engine::visitedBoard[row] = new bool[cols];
	}
}

void Engine::deleteBoard(const ushort rows)
{

	for (ushort row = 0; row < rows; ++row)
	{
		delete[] Engine::playerBoard[row];
		delete[] Engine::board[row];
		delete[] Engine::visitedBoard[row];
	}

	delete[] board;
	delete[] playerBoard;
	delete[] visitedBoard;
}

void Engine::fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar)
{

	for (ushort row = 0; row < rows; ++row)
	{
		for (ushort col = 0; col < cols; ++col)
		{
			Engine::board[row][col] = uncoveredChar;
			Engine::playerBoard[row][col] = coveredChar;
			Engine::visitedBoard[row][col] = false;
		}
	}
}


void Engine::GenerateBoard(const BoardSettings &boardSettings)
{

	Engine::isPlaying = true;
	Engine::isWin = false;

	ushort rows = boardSettings.boardRows;
	ushort cols = boardSettings.boardCols;
	ushort bombsCount = boardSettings.bombsCount;

	initializeBoard(rows, cols);
	fillBoard(rows, cols, boardSettings.uncovered, boardSettings.covered);

	// Place bombs
	for (ushort i = 0; i < bombsCount; ++i)
	{
		ushort rowIndex = 0, colIndex = 0;
		do
		{
			rowIndex = GenerateRandomNumber(1, rows) - 1;
			colIndex = GenerateRandomNumber(1, cols) - 1;
		} while (Engine::board[rowIndex][colIndex] == boardSettings.bombRevealed);

		Engine::board[rowIndex][colIndex] = boardSettings.bombRevealed;
	}

	// Do revealed board
	ushort countNearbyBombs = 0;
	for (ushort row = 0; row < rows; ++row)
	{
		for (ushort col = 0; col < cols; ++col)
		{
			if (Engine::board[row][col] == boardSettings.bombRevealed)
			{
				continue;
			}

			countNearbyBombs = 0;

			// up row
			for (short i = col - 1; i < col + 2; ++i)
			{
				if (row - 1 < 0)
				{
					break;
				}

				if (i < 0 || i > cols - 1)
				{
					continue;
				}

				if (Engine::board[row - 1][i] == boardSettings.bombRevealed)
				{
					countNearbyBombs++;
				}
			}

			// down row
			for (short i = col - 1; i < col + 2; ++i)
			{
				if (row + 1 > rows - 1)
				{
					break;
				}

				if (i < 0 || i > cols - 1)
				{
					continue;
				}

				if (Engine::board[row + 1][i] == boardSettings.bombRevealed)
				{
					countNearbyBombs++;
				}
			}

			// left
			if (col - 1 >= 0 && Engine::board[row][col - 1] == boardSettings.bombRevealed)
			{
				countNearbyBombs++;
			}

			// right
			if (col + 1 < cols && Engine::board[row][col + 1] == boardSettings.bombRevealed)
			{
				countNearbyBombs++;
			}

			if (countNearbyBombs > 0)
			{
				Engine::board[row][col] = boardSettings.numbers[countNearbyBombs - 1];
			}
		}
	}
}


if (Engine::playerBoard[row][col] == boardSettings.bombMarked)
		{
			Engine::playerBoard[row][col] = boardSettings.covered;
		}
		else
		{
			Engine::playerBoard[row][col] = boardSettings.bombMarked;
		}

