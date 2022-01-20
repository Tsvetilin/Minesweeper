#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Engine.hpp"
#include "Common.hpp"


void Engine::GenerateBoard(const BoardSettings& boardSettings) {

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
		do {
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
			if (Engine::board[row][col] == boardSettings.bombRevealed) {
				continue;
			}

			countNearbyBombs = 0;

			// up row
			for (short i = col - 1; i < col + 2; ++i)
			{
				if (row - 1 < 0) {
					break;
				}

				if (i < 0 || i > cols - 1) {
					continue;
				}

				if (Engine::board[row - 1][i] == boardSettings.bombRevealed) {
					countNearbyBombs++;
				}
			}

			// down row
			for (short i = col - 1; i < col + 2; ++i)
			{
				if (row + 1 > rows - 1) {
					break;
				}

				if (i < 0 || i > cols - 1) {
					continue;
				}

				if (Engine::board[row + 1][i] == boardSettings.bombRevealed) {
					countNearbyBombs++;
				}
			}

			// left
			if (col - 1 >= 0 && Engine::board[row][col - 1] == boardSettings.bombRevealed) {
				countNearbyBombs++;
			}

			// right
			if (col + 1 < cols && Engine::board[row][col + 1] == boardSettings.bombRevealed) {
				countNearbyBombs++;
			}

			if (countNearbyBombs > 0) {
				Engine::board[row][col] = boardSettings.numbers[countNearbyBombs - 1];
			}
		}
	}
}

void Engine::PerformMove(const Move move, const ushort row, const ushort col, const BoardSettings& boardSettings, const UncoverType uncoverType) {

	if (!Engine::isPlaying) {
		return;
	}

	ushort rows = boardSettings.boardRows;
	ushort cols = boardSettings.boardCols;

	if (0 > row || row >= rows) {
		return;
	}

	if (0 > col || col >= cols) {
		return;
	}

	if (Engine::playerBoard[row][col] == boardSettings.uncovered || isNumber(row, col, boardSettings.numbers)) {
		return;
	}

	if (move == Move::MarkBomb) {
		if (Engine::playerBoard[row][col] == boardSettings.bombMarked)
		{
			Engine::playerBoard[row][col] = boardSettings.covered;
		}
		else {
			Engine::playerBoard[row][col] = boardSettings.bombMarked;
		}
		return;
	}

	if (move == Move::None) {
		return;
	}

	if (Engine::playerBoard[row][col] == boardSettings.bombMarked) {
		return;
	}

	if (Engine::board[row][col] == boardSettings.bombRevealed) {
		Engine::isWin = false;
		Engine::isPlaying = false;
		Engine::playerBoard[row][col] = boardSettings.bombRevealed;
		return;
	}

	if (uncoverType == UncoverType::Custom) {
		if (Engine::board[row][col] == boardSettings.uncovered) {
			if (row > 0) {
				if (col > 0) {
					Engine::playerBoard[row - 1][col - 1] = Engine::board[row - 1][col - 1];
				}
			
				Engine::playerBoard[row - 1][col] = Engine::board[row - 1][col];
				
				if (col < cols - 1) {
					Engine::playerBoard[row - 1][col + 1] = Engine::board[row - 1][col + 1];
				}
			}

			if (col > 0) {
				Engine::playerBoard[row][col - 1] = Engine::board[row][col - 1];
			}
			
			Engine::playerBoard[row][col] = Engine::board[row][col];
			
			if (col < cols - 1) {
				Engine::playerBoard[row][col + 1] = Engine::board[row][col + 1];
			}

			if (row < rows - 1) {
				if (col > 0) {
					Engine::playerBoard[row + 1][col - 1] = Engine::board[row + 1][col - 1];
				}
				
				Engine::playerBoard[row + 1][col] = Engine::board[row + 1][col];
				
				if (col < cols - 1) {
					Engine::playerBoard[row + 1][col + 1] = Engine::board[row + 1][col + 1];
				}
			}
		}
		else {
			Engine::playerBoard[row][col] = Engine::board[row][col];
		}

	}
	else if (uncoverType == UncoverType::Default) {
		Engine::revealToNumber(row, col, rows, cols, boardSettings.uncovered, boardSettings.covered,boardSettings.numbers);
	}

	if (checkForWin(boardSettings)) {
		Engine::isPlaying = false;
		Engine::isWin = true;
	}

}

void Engine::revealToNumber(short row, short col, ushort rows, ushort cols, char uncovered, char covered, const char* const numbers) {

	if (row > rows - 1 || row<0 || col>cols - 1 || col < 0) {
		return;
	}

	if (visitedBoard[row][col]) {
		return;
	}

	Engine::playerBoard[row][col] = Engine::board[row][col];
	Engine::visitedBoard[row][col] = true;

	if(isNumber(row, col, numbers)){
		return;
	}

	revealToNumber(row + 1, col, rows, cols, uncovered, covered, numbers);
	revealToNumber(row - 1, col, rows, cols, uncovered, covered, numbers);
	revealToNumber(row, col + 1, rows, cols, uncovered, covered, numbers);
	revealToNumber(row, col - 1, rows, cols, uncovered, covered, numbers);
}

void Engine::FinishGame(const BoardSettings& boardSettings) {
	Engine::deleteBoard(boardSettings.boardRows);
}

bool Engine::HasGameFinished() {
	return !Engine::isPlaying;
}

bool Engine::IsWin() {
	return Engine::isWin;
}

bool Engine::checkForWin(const BoardSettings& boardSettings) {

	ushort rows = boardSettings.boardRows;
	ushort cols = boardSettings.boardCols;

	ushort markedBombs = 0;

	for (ushort row = 0; row < rows; ++row)
	{
		for (ushort col = 0; col < cols; ++col)
		{
			if (playerBoard[row][col] == boardSettings.uncovered) {
				return false;
			}

			if (playerBoard[row][col] == boardSettings.bombMarked) {
				++markedBombs;
			}
		}
	}

	return markedBombs == boardSettings.bombsCount;
}

bool Engine::isNumber(const ushort row, const ushort col, const char* numbers) {
	ushort i = 0;
	while (i < NUMBERS_CHAR_ARRAY_SIZE) {
		if (Engine::playerBoard[row][col] == numbers[i]) {
			return true;
		}

		++i;
	}

	return false;
}

void Engine::initializeBoard(const ushort rows, const ushort cols) {

	Engine::board = new char* [rows];
	Engine::playerBoard = new char* [rows];
	Engine::visitedBoard = new bool* [rows];

	for (ushort row = 0; row < rows; ++row)
	{
		Engine::playerBoard[row] = new char[cols];
		Engine::board[row] = new char[cols];
		Engine::visitedBoard[row] = new bool[cols];
	}
}

void Engine::deleteBoard(const ushort rows) {

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

void Engine::fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar) {

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

void Engine::LoadGame(const BoardSettings& boardSettings, const char* const* const rawBoardData, const char* const* const rawPlayerBoardData) {
	
	initializeBoard(boardSettings.boardRows,boardSettings.boardCols);

	for (ushort i = 0; i < boardSettings.boardRows; ++i)
	{
		copyLine(rawBoardData[i], board[i], boardSettings.boardCols);
	}

	for (ushort i = 0; i < boardSettings.boardRows; ++i)
	{
		copyLine(rawPlayerBoardData[i], playerBoard[i], boardSettings.boardCols);
	}

	isPlaying = true;
	isWin = false;

	for (ushort row = 0; row < boardSettings.boardRows; ++row)
	{
		for (ushort col = 0; col < boardSettings.boardCols; ++col)
		{
			Engine::visitedBoard[row][col] = false;
		}
	}
}

const char* const* const Engine::GetPlayerBoard() {
	return playerBoard;
}

const char* const* const Engine::GetBoard() {
	return board;
}