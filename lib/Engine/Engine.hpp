#pragma once

#include "../Board/Board.hpp"
#include "../Board/BoardSettings.hpp"

#include "../Common/Common.hpp"

#include "../Engine/EngineState.hpp"
#include "../Engine/Move.hpp"

/// <summary>
/// Contains the main ingame logic
/// </summary>
class Engine {
	Board* board;
	EngineState state;

	/// <summary>
	/// Check current board state to determine if the player has revealed every non-bomb position
	/// </summary>
	bool checkForWin();
	EngineState handleBoardResult(BoardOperationResult);

	void free();
	void copyFrom(const Engine&);

public:
	Engine();
	Engine(const Engine&);
	Engine& operator=(const Engine&);

	EngineState newGame(const Settings* settings);
	EngineState loadGame(const Settings* settings, const Board& board);

	/// <summary>
	/// Perform a specified <paramref name="move"/> on a position
	/// </summary>
	/// <param name="move">The desired move to perform on the current state of the board</param>
	/// <param name="row">The row to perform the move on</param>
	/// <param name="col">The column to perform the move on</param>
	EngineState performMove(Move move, ushort row, ushort col);
	EngineState finishGame();

	const Board& getBoard();
	EngineState getState();
	bool hasGameFinished();
	bool isWin();

	~Engine();
};
