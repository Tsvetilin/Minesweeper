#pragma once
#ifndef STATE_H_
#define STATE_H_

#include "Common.hpp"

#include <vector>

// Handles game state
enum class GameState {
	Unknown = 0,
	Settings = 1,
	MainMenu = 2,
	EscapeMenu = 3,
	Playing = 4,
	Finished = 5,
	Exiting = 6,

	SizeSettings=10,
	SymbolsSettings=11,
	LookSettings=12,
	UncoverSettings=13,
	ControlSettings=14,
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
	char uncovered = '-';
	char covered = '_';
	char numbers[NUMBERS_CHAR_ARRAY_SIZE] = "12345678";
};

struct Settings {
	BoardSettings BoardSettings;								// Board settings -> board size & bombs count
	UncoverType UncoverType = UncoverType::Default;				// Default / custom uncover
	ControlType ControlType = ControlType::AdvancedArrowInput;	// Arrow / Input controls
	BoardLook BoardLook = BoardLook::Fancy;				        // Fancy / default board look
};

struct Size {

	Size(ushort rows, ushort cols, ushort bombs) {
		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
	}

	ushort rows;
	ushort cols;
	ushort bombs;
};

const ushort MAIN_MENU_OPTIONS_COUNT = 4;
const ushort SETTINGS_MENU_OPTIONS_COUNT = 5;
const ushort OTHER_S_MENU_OPTIONS = 2;

struct State {

	State();
public:
	std::vector<Size> sizes;
	std::vector<char*> symbols;

	void ReadSettings();
	void SaveSettings();
	bool SaveGame(const char* const* playerBoard, const char* const* board);
	void DeleteSavedGame();

	// Set state:
	void NewGame();
	void ResumeGame();
	void ContinueGame();
	void FinishGame();
	void OpenMainMenu();
	void OpenEscapeMenu();
	void OpenSettingsMenu();
	void OpenSizeSettingsMenu();
	void OpenSymbolsSettingsMenu();
	void OpenUncoverSettingsMenu();
	void OpenControlSettingsMenu();
	void OpenLookSettingsMenu();

	void SelectSize(ushort index);
	void SelectSymbols(ushort index);
	void SelectUncover(ushort index);
	void SelectControl(ushort index);
	void SelectLook(ushort index);

	void IncreaseMenuOptionSelected(ushort optionsCount);
	void DecreaseMenuOptionSelected(ushort optionsCount);

	void MoveLeftIngame();
	void MoveRightIngame();
	void MoveUpIngame();
	void MoveDownIngame();

	void LockIngamePosition();
	void UnlockIngamePosition();

	void SetStatusMessage(const char message[]);
	const char const* GetStatusMessage();

	const GameState& UpdateGameState();

	const GameState& GetGameState() {
		return gameState;
	};

	const Settings& GetSettings() {
		return settings;
	};

	const ushort& GetCurrentMenuOptionSelected();
	const ushort& GetCurrentInGameRowIndex();
	const ushort& GetCurrentInGameColIndex();
	const bool& GetLockedPosition();
	const char const* const* GetRawBoardData();
	const char const* const* GetRawPlayerBoardData();
	const ushort& GetSizeOptions();
	const ushort& GetSymbolsOptions();
	const ushort& GetCurrentSizeIndex();
	const ushort& GetCurrentSymbolsIndex();
	const bool& CanContinueGame();

private:
	char** rawBoardData;
	char** rawPlayerBoardData;

	ushort sizeOptions;
	ushort symbolsOptions;
	ushort currentSizeIndex;
	ushort currentSymbolsIndex;

	ushort currentMenuOptionSelected;

	ushort currentInGameRowIndex;
	ushort currentInGameColIndex;
	bool isLockedPosition = false;
	bool canContinueGame = false;

	GameState gameState;
	Settings settings;

	char statusMessage[COMMAND_MAX_LENGTH];
};

#endif // !STATE_H_
