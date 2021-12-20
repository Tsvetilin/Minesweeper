#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include "Common.hpp"
#include "State.hpp"

// Contains main game logic
struct Engine {

public:
	char** board;
	char** playerBoard;

	void LoadGame(const BoardSettings boardSettings, const char** rawBoardData, const char** rawPlayerBoardData);
	void GenerateBoard(const BoardSettings boardSettings);
	void PerformMove(const Move move, const ushort row, const ushort col, const BoardSettings boardSettings, const UncoverType uncoverType);
	void FinishGame(const BoardSettings boardSettings);
	bool HasGameFinished();
	bool IsWin();

private:
	bool isPlaying = false;
	bool isWin = false;

	bool checkForWin(const BoardSettings boardSettings);

	void initializeBoard(const ushort rows, const ushort cols);
	void deleteBoard(const ushort rows);
	void fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar);

};

#endif // !ENGINE_H_
