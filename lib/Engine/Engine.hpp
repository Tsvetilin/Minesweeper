/**
*
* Solution to course project # 13
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Tsvetilin Tsvetilov
* @idnumber 3MI0600062
* @compiler VC
*
* File with definitons of functions containing the ingame logic
*
*/

#pragma once
#include "../Board/Board.hpp"
#include "../Common/Common.hpp"
#include "../Board/BoardSettings.hpp"
#include "../Engine/EngineState.hpp"
#include "../Engine/Move.hpp"

/// <summary>
/// Contains the main ingame logic
/// </summary>
class Engine {
	Board* board;
	const Settings* settings;
	EngineState state;
	bool isPlaying;

	/// <summary>
	/// Check current board state to determine if the player has revealed every non-bomb position
	/// </summary>
	bool checkForWin();

public:
	Engine() : isPlaying(false), state(EngineState::Unknown) {}

	void newGame(const Settings* settings);
	void loadGame(const Settings* settings, const Board& board);

	/// <summary>
	/// Perform a specified <paramref name="move"/> on a position
	/// </summary>
	/// <param name="move">The desired move to perform on the current state of the board</param>
	/// <param name="row">The row to perform the move on</param>
	/// <param name="col">The column to perform the move on</param>
	void performMove(Move move, ushort row, ushort col);
	void finishGame();

	const Board& getBoard();
	EngineState getState();
	bool hasGameFinished();
	bool isWin();
};
