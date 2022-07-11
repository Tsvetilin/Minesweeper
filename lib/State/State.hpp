/**
*
* Solution to course project # 13
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Tsvetilin Tsvetilov
* @idnumber 3MI0600062
* @compiler VC
*
* File with definitons of functions handling the current game state and settings
*
*/

#ifndef STATE_H_
#define STATE_H_

#include "Common.hpp"

#include <vector>
#include <cstring>

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


const ushort MAIN_MENU_OPTIONS_COUNT = 4;
const ushort SETTINGS_MENU_OPTIONS_COUNT = 5;
const ushort OTHER_S_MENU_OPTIONS = 2;

// Handle game state
struct State {

	State() {
		State::gameState = GameState::Unknown;
		canContinueGame = true;
		currentInGameColIndex = 0;
		currentInGameRowIndex = 0;
		currentMenuOptionSelected = 0;
		currentSizeIndex = 0;
		currentSymbolsIndex = 0;
		sizeOptions = 0;
		symbolsOptions = 0;
		rawPlayerBoardData = nullptr;
		rawBoardData = nullptr;
		isLockedPosition = false;
		statusMessage[0] = '\0';
	};

	std::vector<Size*> sizes;
	std::vector<char*> symbols;

	/// <summary>
	/// Read settings from file or use default
	/// </summary>
	void ReadSettings();

	/// <summary>
	/// Save current settings to file
	/// </summary>
	void SaveSettings();

	/// <summary>
	/// Save current game with the current state
	/// </summary>
	/// <param name="playerBoard"> Pointer to the board presenting the current game state</param>
	/// <param name="board">Pointer to the board presenting the revealed board</param>
	bool SaveGame(const char* const* const playerBoard, const char* const* const board);

	/// <summary>
	/// Read the file containing the saved game
	/// </summary>
	void ReadSavedBoard();

	/// <summary>
	/// Delete the file (empty it) holding the last saved game
	/// </summary>
	void DeleteSavedGame();

	/// <summary>
	/// Delete any memory allocated to hold the settings options
	/// </summary>
	void DeleteSettingsAllocatedMemory();

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

	// Select settings
	void SelectSize(ushort index);
	void SelectSymbols(ushort index);
	void SelectUncover(ushort index);
	void SelectControl(ushort index);
	void SelectLook(ushort index);

	// Menu control state:
	void IncreaseMenuOptionSelected(ushort optionsCount);
	void DecreaseMenuOptionSelected(ushort optionsCount);

	// Ingame control state:
	void MoveLeftIngame();
	void MoveRightIngame();
	void MoveUpIngame();
	void MoveDownIngame();

	void LockIngamePosition();
	void UnlockIngamePosition();

	// Status message hadlers:
	void SetStatusMessage(const char message[]);
	const char* const GetStatusMessage();

	const GameState& UpdateGameState();

	// Getters:
	const GameState& GetGameState();
	const Settings& GetSettings();
	const short& GetCurrentMenuOptionSelected();
	const ushort& GetCurrentInGameRowIndex();
	const ushort& GetCurrentInGameColIndex();
	const ushort& GetSizeOptions();
	const ushort& GetSymbolsOptions();
	const ushort& GetCurrentSizeIndex();
	const ushort& GetCurrentSymbolsIndex();
	const bool& CanContinueGame();
	const bool& GetLockedPosition();
	const char* const* const GetRawBoardData();
	const char* const* const GetRawPlayerBoardData();

private:
	char** rawBoardData;
	char** rawPlayerBoardData;

	ushort sizeOptions;
	ushort symbolsOptions;
	ushort currentSizeIndex;
	ushort currentSymbolsIndex;

	short currentMenuOptionSelected;

	ushort currentInGameRowIndex;
	ushort currentInGameColIndex;
	bool isLockedPosition;
	bool canContinueGame;

	GameState gameState;
	Settings settings;

	char statusMessage[COMMAND_MAX_LENGTH];

	void resetMenuIndex();
	void readSettingOptions();
	void synchronizeOptionsSelected();
};

#endif // !STATE_H_
