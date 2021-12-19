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

	void GenerateBoard(const BoardSettings boardSettings);
	void PerformMove(const ushort row, ushort col);
	bool HasGameFinished();
	bool IsWin();

private:
	void initializeBoard(const ushort rows, const ushort cols);
	void deleteBoard(const ushort rows);
	void fillBoard(const ushort rows, const ushort cols, const char uncoveredChar);

};

#endif // !ENGINE_H_
