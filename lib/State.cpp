#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "State.hpp"

#include <fstream>
#include <string>
#include <cstring>

#include<iostream>
// TODO: remove

State::State() {
	State::gameState = GameState::Unknown;
	canContinueGame = true;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	currentMenuOptionSelected = 0;
	currentSizeIndex = 0;
	currentSymbolsIndex = 0;
}

void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	State::currentMenuOptionSelected = 1;
}

void State::SetStatusMessage(const char message[]) {
	strcpy_s(State::statusMessage, message);
}

const char* const State::GetStatusMessage() {
	return State::statusMessage;
}


void State::ReadSettings() {

	std::fstream settingsFile;
	settingsFile.open(GAME_SETTINGS_FILE, std::ios::binary | std::ios::in);

	if (settingsFile.is_open()) {
		settingsFile.read((char*)&(State::settings), sizeof(State::settings));
		settingsFile.close();
	}

	std::fstream settingsTemplate;
	settingsTemplate.open(SETTINGS_TEMPLATE_FILE, std::ios::binary | std::ios::in);
	if (settingsTemplate.is_open()) {
		std::string buffer;
		while (true) {
			std::getline(settingsTemplate, buffer);
			if (buffer[0] == '}') {
				break;
			}

			// TODO: implement json parser

		}
		settingsTemplate.close();
	}
	else {
		sizeOptions = 5;
		symbolsOptions = 2;

		currentSizeIndex = 0;
		currentSymbolsIndex = 0;

		// TODO: handle approptiate utf-8 support
		char* a = new char[50];
		char* b = new char[50];
		//char* c = new char[50];
		strcpy(a, "R-0X12345678");
		strcpy(b, "F_-B12345678");
		//strcpy(c, "🚩⬛☐💣1️⃣2️⃣3️⃣4️⃣5️⃣6️⃣7️⃣8️⃣");
		symbols.push_back(a);
		symbols.push_back(b);
		//symbols.push_back(c);

		sizes.push_back(Size(9, 9, 10));
		sizes.push_back(Size(10, 10, 15));
		sizes.push_back(Size(16, 16, 40));
		sizes.push_back(Size(16, 30, 99));
		sizes.push_back(Size(24, 30, 200));
	}

}

void State::DeleteSavedGame() {
	std::fstream savedGame;
	savedGame.open(SAVED_GAME_FILE, std::ios::out);

	if (savedGame.is_open()) {
		savedGame << '\0';
		savedGame.close();
	}
}

void State::IncreaseMenuOptionSelected(ushort optionsCount) {
	++currentMenuOptionSelected;
	if (currentMenuOptionSelected > optionsCount) {
		currentMenuOptionSelected = 1;
	}
}

void State::DecreaseMenuOptionSelected(ushort optionsCount) {
	--currentMenuOptionSelected;
	if (currentMenuOptionSelected < 1) {
		currentMenuOptionSelected = optionsCount;
	}
}

void State::MoveLeftIngame() {
	if (currentInGameColIndex == 0) {
		currentInGameColIndex = settings.BoardSettings.boardCols - 1;
	}
	else {
		--currentInGameColIndex;
	}
	isLockedPosition = false;
}

void State::MoveRightIngame() {
	++currentInGameColIndex;
	if (currentInGameColIndex > settings.BoardSettings.boardCols - 1) {
		currentInGameColIndex = 0;
	}
	isLockedPosition = false;
}

void State::MoveUpIngame() {
	if (currentInGameRowIndex == 0) {
		currentInGameRowIndex = settings.BoardSettings.boardRows - 1;
	}
	else {
		--currentInGameRowIndex;
	}

	isLockedPosition = false;
}

void State::MoveDownIngame() {
	++currentInGameRowIndex;
	if (currentInGameRowIndex > settings.BoardSettings.boardRows - 1) {
		currentInGameRowIndex = 0;
	}
	isLockedPosition = false;
}

void State::LockIngamePosition() {
	isLockedPosition = true;
}

void State::UnlockIngamePosition() {
	isLockedPosition = false;
}

void State::SaveSettings() {
	std::fstream settingsFile;
	settingsFile.open(GAME_SETTINGS_FILE, std::ios::binary | std::ios::out);

	if (settingsFile.is_open()) {
		settingsFile.write((char*)&(State::settings), sizeof(State::settings));
		settingsFile.close();
	}
}

bool State::SaveGame(const char* const* playerBoard, const char* const* board) {
	std::fstream savedGame;
	savedGame.open(SAVED_GAME_FILE, std::ios::out);

	if (!savedGame.is_open()) {
		canContinueGame = false;
		return false;
	}

	for (ushort i = 0; i < settings.BoardSettings.boardRows; i++)
	{
		for (ushort j = 0; j < settings.BoardSettings.boardCols; j++)
		{
			savedGame << board[i][j];
		}
		savedGame << std::endl;
	}

	for (ushort i = 0; i < settings.BoardSettings.boardRows; i++)
	{
		for (ushort j = 0; j < settings.BoardSettings.boardCols; j++)
		{
			savedGame << playerBoard[i][j];
		}
		savedGame << std::endl;
	}
	savedGame.close();
	canContinueGame = true;
}

// Set state:
void State::NewGame() {
	gameState = GameState::Playing;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	isLockedPosition = false;
	canContinueGame = false;
}

void State::ResumeGame() {
	gameState = GameState::Playing;
	isLockedPosition = false;
}

void State::ContinueGame() {
	gameState = GameState::Playing;
	canContinueGame = false;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	isLockedPosition = false;
	deleteMatrix(rawBoardData, settings.BoardSettings.boardRows);
	deleteMatrix(rawPlayerBoardData, settings.BoardSettings.boardRows);
}

void State::FinishGame() {
	gameState = GameState::Finished;
	canContinueGame = false;
}

void State::OpenEscapeMenu() {
	gameState = GameState::EscapeMenu;
	currentMenuOptionSelected = 1;
}
void State::OpenSettingsMenu() {
	currentMenuOptionSelected = 1;
	gameState = GameState::Settings;
}
void State::OpenSizeSettingsMenu() {
	gameState = GameState::SizeSettings;
	currentMenuOptionSelected = 1;
}
void State::OpenSymbolsSettingsMenu() {
	gameState = GameState::SymbolsSettings;
	currentMenuOptionSelected = 1;
}
void State::OpenUncoverSettingsMenu() {
	gameState = GameState::UncoverSettings;
	currentMenuOptionSelected = 1;
}
void State::OpenControlSettingsMenu() {
	gameState = GameState::ControlSettings;
	currentMenuOptionSelected = 1;
}
void State::OpenLookSettingsMenu() {
	gameState = GameState::LookSettings;
	currentMenuOptionSelected = 1;
}


void State::SelectSize(ushort index) {
	currentSizeIndex = index;
	settings.BoardSettings.boardRows = sizes[index].rows;
	settings.BoardSettings.boardCols = sizes[index].cols;
	settings.BoardSettings.bombsCount = sizes[index].bombs;
	canContinueGame = false;
}

void State::SelectSymbols(ushort index) {
	currentSymbolsIndex = index;
	settings.BoardSettings.bombMarked = symbols[index][0];
	settings.BoardSettings.covered = symbols[index][1];
	settings.BoardSettings.uncovered = symbols[index][2];
	settings.BoardSettings.bombRevealed = symbols[index][3];
	for (ushort i = 0; i < 8; i++)
	{
		settings.BoardSettings.numbers[i] = symbols[index][4 + i];
	}
	canContinueGame = false;
}

void State::SelectUncover(ushort index) {
	settings.UncoverType = (UncoverType)(index);
	canContinueGame = false;
}

void State::SelectControl(ushort index) {
	settings.ControlType = (ControlType)(index);
	canContinueGame = false;
}

void State::SelectLook(ushort index) {
	settings.BoardLook = (BoardLook)(index);
	canContinueGame = false;
}

const ushort& State::GetCurrentMenuOptionSelected() {
	return State::currentMenuOptionSelected;
}

const ushort& State::GetCurrentInGameColIndex() {
	return State::currentInGameColIndex;
}

const ushort& State::GetCurrentInGameRowIndex() {
	return State::currentInGameRowIndex;
}

const bool& State::GetLockedPosition() {
	return State::isLockedPosition;
}

const char* const* const State::GetRawBoardData() {
	return rawBoardData;
}

const char* const* const State::GetRawPlayerBoardData() {
	return rawPlayerBoardData;
}

const ushort& State::GetSizeOptions() {
	return sizeOptions;
}

const ushort& State::GetSymbolsOptions() {
	return symbolsOptions;
}

const ushort& State::GetCurrentSizeIndex() {
	return currentSizeIndex;
}

const ushort& State::GetCurrentSymbolsIndex() {
	return currentSymbolsIndex;
}
const bool& State::CanContinueGame() {
	if (canContinueGame) {

		std::fstream savedGame;
		savedGame.open(SAVED_GAME_FILE, std::ios::in);

		if (!savedGame.is_open()) {
			canContinueGame = false;
			return canContinueGame;
		}

		std::string buffer;
		initializeMatrix(rawBoardData, settings.BoardSettings.boardRows, settings.BoardSettings.boardCols);
		initializeMatrix(rawPlayerBoardData, settings.BoardSettings.boardRows, settings.BoardSettings.boardCols);

		std::getline(savedGame, buffer);
		if (buffer[0] == '\0') {
			canContinueGame = false;
			return canContinueGame;
		}

		for (ushort i = 0; i < settings.BoardSettings.boardRows; i++)
		{
			copyLine(buffer.c_str(), rawBoardData[i], settings.BoardSettings.boardCols);
			std::getline(savedGame, buffer);
		}

		for (ushort i = 0; i < settings.BoardSettings.boardRows; i++)
		{
			copyLine(buffer.c_str(), rawPlayerBoardData[i], settings.BoardSettings.boardCols);
			std::getline(savedGame, buffer);
		}
		savedGame.close();

		DeleteSavedGame();
	}

	return canContinueGame;
}

