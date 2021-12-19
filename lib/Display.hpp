#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Common.hpp"
#include "State.hpp"

// Writes on the console 
struct Display {

public:
	void WritePauseMenu(GameState state, ushort currentIndexSelected);
	void WriteMainMenu(GameState state, ushort currentIndexSelected);
	void WriteSettingsMenu(GameState state, ushort currentIndexSelected);
	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board);

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[] = "", const char backgroundColor[]= "");
};

#endif // !DISPLAY_H_
