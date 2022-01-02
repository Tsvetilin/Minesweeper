#pragma once
#ifndef STATE_H_
#define STATE_H_

#include "Common.hpp"

// Handles game state
enum class GameState {
	Unknown = 0,
	Settings = 1,
	MainMenu = 2,
	EscapeMenu = 3,
	Playing = 4,
	Finished = 5,
	Exiting = 6,
};

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

// Default board settings
struct BoardSettings {
	ushort boardRows = 9;
	ushort boardCols = 9;
	ushort bombsCount = 10;
	char bombRevealed = 'B';
	char bombMarked = 'F';
	char uncovered = ' ';
	char covered = '_';
	char numbers[NUMBERS_CHAR_ARRAY_SIZE] = "12345678";
};

struct Settings {
	BoardSettings BoardSettings;								// Board settings -> board size & bombs count
	UncoverType UncoverType = UncoverType::Default;				// Default / custom uncover
	ControlType ControlType = ControlType::AdvancedArrowInput;	// Arrow / Input controls
	BoardLook BoardLook = BoardLook::Fancy;				        // Fancy / default board look
};

const ushort MAIN_MENU_OPTIONS_COUNT = 4;

struct State {

public:
	

	void ReadSettings();
	void SaveSettings();
	void SaveGame();
	void NewGame();
	void ContinueGame();
	void OpenMainMenu();
	void OpenEscapeMenu();
	void OpenSettingsMenu();

	void SetStatusMessage(const char message[]);

	GameState UpdateGameState();

	GameState GetGameState() {
		return gameState;
	};

	Settings GetSettings() {
		return settings;
	};

	ushort currentMenuOptionSelected;

private:
	GameState gameState;
	Settings settings;

	char statusMessage[COMMAND_MAX_LENGTH];
};

#endif // !STATE_H_
