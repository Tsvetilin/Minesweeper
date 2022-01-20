#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "State.hpp"

// Writes on the console 
struct Display {

public:
	void WritePauseMenu(short currentIndexSelected, const char* const statusMessage);
	void WriteMainMenu(short currentIndexSelected, const char* const statusMessage);
	void WriteSettingsMenu(short currentIndexSelected, const char* const statusMessage);
	void WriteLookSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);
	void WriteControlSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);
	void WriteUncoverSettingsMenu(short currentIndexSelected, ushort currentUsedIndex, const char* const statusMessage);
	void WriteSizeSettingsMenu(short currentIndexSelected, ushort options, std::vector<Size*> sizes, ushort currentUsedIndex, const char* const statusMessage);
	void WriteSymbolsSettingsMenu(short currentIndexSelected, ushort options, std::vector<char*> sizes, ushort currentUsedIndex, const char* const statusMessage);

	void WriteBoard(BoardLook boardLook, BoardSettings boardSize, int currentRowIndex, int currentColIndex, const char* const* const board, const char* const statusMessage);
	void WriteFinishBoard(BoardLook boardLook, BoardSettings boardSize, const char* const* const playerBoard, const char* const* const board, const char* const statusMessage);
	void WriteExit(const char* const statusMessage);

	void WriteManual();

private:
	void clearScreen();
	void colorizeOutput(const char foregroundColor[] = "", const char backgroundColor[] = "");

	void writeHeader();

	void writeBoardTop(bool isFancyBoard, bool isSmallBoard, ushort cols);
	void writeBoardBottom(bool isSmallBoard, ushort cols);
};

#endif // !DISPLAY_H_
