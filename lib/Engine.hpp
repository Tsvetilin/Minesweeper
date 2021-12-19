#pragma once
#ifndef ENGINE_H_
#define ENGINE_H_

#include "Common.hpp"
#include "State.hpp"

// Contains main game logic
struct Engine {

public:
	char** board;

	void GenerateBoard(BoardSettings boardSettings);
	void PerformMove(ushort row, ushort col);
	bool HasGameFinished();
	bool IsWin();

private:
	void initializeBoard(ushort rows, ushort cols);
	void deleteBoard(ushort rows, ushort cols);

};

#endif // !ENGINE_H_
