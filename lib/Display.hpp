#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "State.hpp"

// Writes on the console 
struct Display {

public:
	void WritePauseMenu(ushort currentIndexSelected);
	void WriteMainMenu(ushort currentIndexSelected);
	void WriteLookSettingsMenu(ushort currentIndexSelected);
	void WriteControlSettingsMenu(ushort currentIndexSelected);
	void WriteUncoverSettingsMenu(ushort currentIndexSelected);
	void WriteSizeSettingsMenu(ushort currentIndexSelected);
	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board);

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[], const char backgroundColor[]);

	void writeHeader();
};

#endif // !DISPLAY_H_
