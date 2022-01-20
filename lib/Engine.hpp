#pragma once
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

public:
	const char* const* const GetPlayerBoard();
	const char* const* const GetBoard();

	void LoadGame(const BoardSettings& boardSettings, const char* const* const rawBoardData, const char* const* const rawPlayerBoardData);
	void GenerateBoard(const BoardSettings& boardSettings);
	void PerformMove(const Move move, const ushort row, const ushort col, const BoardSettings& boardSettings, const UncoverType uncoverType);
	void FinishGame(const BoardSettings& boardSettings);
	bool HasGameFinished();
	bool IsWin();

private:
	bool isPlaying;
	bool isWin;
	bool** visitedBoard;
	char** board;
	char** playerBoard;

	void revealToNumber(const short row, const short col, const ushort rows, const ushort cols, const char uncovered, const char covered, const char* const numbers);

	bool checkForWin(const BoardSettings& boardSettings);
	bool isNumber(const ushort row, const ushort col, const char* const numbers);

	void initializeBoard(const ushort rows, const ushort cols);
	void deleteBoard(const ushort rows);
	void fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar);

};

#endif // !ENGINE_H_
