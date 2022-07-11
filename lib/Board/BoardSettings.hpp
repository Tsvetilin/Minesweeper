#pragma once

#include "../Common.hpp"

enum class BoardLook {
	Default = 0,
	Fancy = 1,
};

enum class UncoverType {
	Default = 0, // As in original game
	Custom = 1,  // Uncover just the surrounding 8 
};

enum class ControlType {
	PrimitiveInput = 0,
	AdvancedArrowInput = 1,
};

struct BoardSize {

	BoardSize(ushort rows = 9, ushort cols = 9, ushort bombs = 10) {
		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
	}

	ushort rows;
	ushort cols;
	ushort bombs;
};

char numbersDefault[NUMBERS_CHAR_ARRAY_SIZE]{ "12345678" };
struct BoardSymbols {

	BoardSymbols(
		char bombRevealed = 'B',
		char bombMarked = 'F',
		char uncovered = '-',
		char covered = '_',
		char* numbers = numbersDefault)
	{
		char bombRevealed = bombRevealed;
		char bombMarked = bombMarked;
		char uncovered = uncovered;
		char covered = covered;
		copyString(numbers, this->numbers, (ushort)strlen(numbersDefault));
	}

	char bombRevealed;
	char bombMarked;
	char uncovered;
	char covered;
	char numbers[NUMBERS_CHAR_ARRAY_SIZE];
};

struct Settings {
	BoardSize size;												// Board size
	BoardSymbols symbols;										// Board style
	UncoverType uncoverType = UncoverType::Default;				// Default / custom uncover
	ControlType controlType = ControlType::AdvancedArrowInput;	// Arrow / Input controls
	BoardLook boardLook = BoardLook::Default;				    // Fancy / default board look
};

