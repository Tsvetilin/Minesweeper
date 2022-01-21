#ifndef ENGINE_H_
#define ENGINE_H_

#include "State.hpp"

/// <summary>
/// Info about the current move
/// </summary>
enum class Move {
	None = 0,
	Reveal = 1,
	MarkBomb = 2,
};

/// <summary>
/// Contains the main game logic
/// </summary>
struct Engine {

	Engine() {
		srand((ushort)time(NULL));

		visitedBoard = nullptr;
		board = nullptr;
		playerBoard = nullptr;
		isPlaying = false;
		isWin = false;
	}

	// Getters
	const char* const* const GetPlayerBoard();
	const char* const* const GetBoard();

	/// <summary>
	/// Load a game based on given boards
	/// </summary>
	/// <param name="rawPlayerBoardData"> Pointer to the board to be the current game state</param>
	/// <param name="rawBoardData">Pointer to the board to be the revealed board</param>
	/// <param name="boardSettings">Board settings to be used</param>
	void LoadGame(const BoardSettings& boardSettings, const char* const* const rawBoardData, const char* const* const rawPlayerBoardData);

	/// <summary>
	/// Generate board according to the settings specified
	/// </summary>
	/// <param name="boardSettings">Current game's board settings</param>
	void GenerateBoard(const BoardSettings& boardSettings);
	
	/// <summary>
	/// Perform a specified <paramref name="move"/> on a position
	/// </summary>
	/// <param name="move">The desired move to perform on the current state of the board</param>
	/// <param name="row">The row to perform the move on</param>
	/// <param name="col">The column to perform the move on</param>
	/// <param name="boardSettings">Current game's board settings</param>
	/// <param name="uncoverType">Current game's uncover type</param>
	void PerformMove(const Move move, const ushort row, const ushort col, const BoardSettings& boardSettings, const UncoverType uncoverType);

	/// <summary>
	/// Free all resources related to the current game
	/// </summary>
	/// <param name="boardSettings">Current game's board settings</param>
	void FinishGame(const BoardSettings& boardSettings);


	bool HasGameFinished();
	bool IsWin();

private:
	bool isPlaying;
	bool isWin;
	bool** visitedBoard;
	char** board;
	char** playerBoard;

	/// <summary>
	/// Recursively reveal all surrounding cells until reaching a number
	/// </summary>
	void revealToNumber(const short row, const short col, const ushort rows, const ushort cols, const char uncovered, const char covered, const char* const numbers);

	/// <summary>
	/// Reveal only the surrounding 8 cells if no number position is hit
	/// </summary>
	void uncoverSurroundingEight(short row, short col, ushort rows, ushort cols, char uncovered);

	/// <summary>
	/// Check current board state to determine if the player has revealed every non-bomb position
	/// </summary>
	bool checkForWin(const BoardSettings& boardSettings);

	/// <summary>
	/// Check if the current position is a number
	/// </summary>
	bool isNumber(const ushort row, const ushort col, const char* const numbers);

	// Handle board initialization & disposal
	void initializeBoard(const ushort rows, const ushort cols);
	void deleteBoard(const ushort rows);
	void fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar);

};

#endif // !ENGINE_H_
