#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "State.hpp"

// Writes on the console 
struct Display {

public:
	void WritePauseMenu(ushort currentIndexSelected, char const * statusMessage);
	void WriteMainMenu(ushort currentIndexSelected, char const * statusMessage);
	void WriteSettingsMenu(ushort currentIndexSelected, char const * statusMessage);
	void WriteLookSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage);
	void WriteControlSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage);
	void WriteUncoverSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char const * statusMessage);
	void WriteSizeSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<Size> sizes, ushort currentUsedIndex, char const * statusMessage);
	void WriteSymbolsSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<char*> sizes, ushort currentUsedIndex, char const * statusMessage);

	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board, char const * statusMessage);

	void WriteExit(char const * statusMessage);

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[], const char backgroundColor[]);

	void writeHeader();
};

#endif // !DISPLAY_H_
