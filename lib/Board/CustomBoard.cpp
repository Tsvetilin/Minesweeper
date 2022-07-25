#include "CustomBoard.hpp"

void Engine::uncoverSurroundingEight(short row, short col, ushort rows, ushort cols, char uncovered)
{
	if (Engine::board[row][col] == uncovered)
	{
		// up row
		if (row > 0)
		{
			if (col > 0)
			{
				Engine::playerBoard[row - 1][col - 1] = Engine::board[row - 1][col - 1];
			}

			Engine::playerBoard[row - 1][col] = Engine::board[row - 1][col];

			if (col < cols - 1)
			{
				Engine::playerBoard[row - 1][col + 1] = Engine::board[row - 1][col + 1];
			}
		}

		// left col
		if (col > 0)
		{
			Engine::playerBoard[row][col - 1] = Engine::board[row][col - 1];
		}

		Engine::playerBoard[row][col] = Engine::board[row][col];

		// right col
		if (col < cols - 1)
		{
			Engine::playerBoard[row][col + 1] = Engine::board[row][col + 1];
		}

		// down row
		if (row < rows - 1)
		{
			if (col > 0)
			{
				Engine::playerBoard[row + 1][col - 1] = Engine::board[row + 1][col - 1];
			}

			Engine::playerBoard[row + 1][col] = Engine::board[row + 1][col];

			if (col < cols - 1)
			{
				Engine::playerBoard[row + 1][col + 1] = Engine::board[row + 1][col + 1];
			}
		}
	}
	else
	{
		Engine::playerBoard[row][col] = Engine::board[row][col];
	}
}