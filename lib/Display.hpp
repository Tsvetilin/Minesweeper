#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "State.hpp"

// Writes on the console 
struct Display {

public:
	void WritePauseMenu(ushort currentIndexSelected, char* statusMessage);
	void WriteMainMenu(ushort currentIndexSelected, char* statusMessage);
	void WriteSettingsMenu(ushort currentIndexSelected, char* statusMessage);
	void WriteLookSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char* statusMessage);
	void WriteControlSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char* statusMessage);
	void WriteUncoverSettingsMenu(ushort currentIndexSelected, ushort currentUsedIndex, char* statusMessage);
	void WriteSizeSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<Size> sizes, ushort currentUsedIndex, char* statusMessage);
	void WriteSymbolsSettingsMenu(ushort currentIndexSelected, ushort options, std::vector<char*> sizes, ushort currentUsedIndex, char* statusMessage);

	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, char** board, char* statusMessage);

	void WriteExit(char* statusMessage);

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[], const char backgroundColor[]);

	void writeHeader();
};

#endif // !DISPLAY_H_
