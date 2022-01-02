#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include "State.hpp"

// Contains main game logic
struct Engine {

	Engine() {
		srand(time(0));
	}

public:
	char** board;
	char** playerBoard;

	void LoadGame(const BoardSettings boardSettings, char** rawBoardData, char** rawPlayerBoardData);
	void GenerateBoard(const BoardSettings boardSettings);
	void PerformMove(const Move move, const ushort row, const ushort col, const BoardSettings boardSettings, const UncoverType uncoverType);
	void FinishGame(const BoardSettings boardSettings);
	bool HasGameFinished();
	bool IsWin();

private:
	bool isPlaying = false;
	bool isWin = false;

	void revealToNumber(short row, short col, ushort rows, ushort cols, char uncovered, char covered);

	bool checkForWin(const BoardSettings boardSettings);
	bool isNumber(const ushort row, const ushort col, const char* numbers);

	void initializeBoard(const ushort rows, const ushort cols);
	void deleteBoard(const ushort rows);
	void fillBoard(const ushort rows, const ushort cols, const char uncoveredChar, const char coveredChar);

};

#endif // !ENGINE_H_
