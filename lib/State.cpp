#include "State.hpp"

#include <fstream>
#include <string>
#include <cstring>

void State::SetStatusMessage(const char message[]) {
	copyString(message, statusMessage, (ushort)strlen(message));
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
		// add default settings options

		currentSizeIndex = 0;
		currentSymbolsIndex = 0;

		symbolsOptions = 2;
		symbols.push_back(new char[SYMBOLS_CHAR_ARRAY_SIZE]{ "F_-B12345678" });
		symbols.push_back(new char[SYMBOLS_CHAR_ARRAY_SIZE]{ "R-0X12345678" });
	

		// TODO: handle approptiate utf-8 support
		//symbols.push_back( new char[80]{u8"🚩⬛☐💣1️⃣2️⃣3️⃣4️⃣5️⃣6️⃣7️⃣8️⃣"});

		sizeOptions = 5;
		sizes.push_back(new Size(9, 9, 10));
		sizes.push_back(new Size(10, 10, 15));
		sizes.push_back(new Size(16, 16, 40));
		sizes.push_back(new Size(16, 30, 99));
		sizes.push_back(new Size(24, 30, 200));
	}
}

void State::DeleteSettingsAllocatedMemory() {
	for (ushort i = 0; i < symbolsOptions; ++i)
	{
		delete[] symbols[i];
	}

	for (ushort i = 0; i < sizeOptions; ++i)
	{
		delete sizes[i];
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

	for (ushort i = 0; i < settings.boardSettings.boardRows; i++)
	{
		for (ushort j = 0; j < settings.boardSettings.boardCols; j++)
		{
			savedGame << board[i][j];
		}
		savedGame << std::endl;
	}

	for (ushort i = 0; i < settings.boardSettings.boardRows; i++)
	{
		for (ushort j = 0; j < settings.boardSettings.boardCols; j++)
		{
			savedGame << playerBoard[i][j];
		}
		savedGame << std::endl;
	}
	savedGame.close();
	canContinueGame = true;
	return true;
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
		rawBoardData = initializeMatrix(settings.boardSettings.boardRows, settings.boardSettings.boardCols);
		rawPlayerBoardData = initializeMatrix(settings.boardSettings.boardRows, settings.boardSettings.boardCols);

		std::getline(savedGame, buffer);
		if (buffer[0] == '\0') {
			canContinueGame = false;
			return canContinueGame;
		}

		for (ushort i = 0; i < settings.boardSettings.boardRows; i++)
		{
			copyLine(buffer.c_str(), rawBoardData[i], settings.boardSettings.boardCols);
			std::getline(savedGame, buffer);
		}

		for (ushort i = 0; i < settings.boardSettings.boardRows; i++)
		{
			copyLine(buffer.c_str(), rawPlayerBoardData[i], settings.boardSettings.boardCols);
			std::getline(savedGame, buffer);
		}
		savedGame.close();

		DeleteSavedGame();
	}

	return canContinueGame;
}


// Set state:
void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	State::currentMenuOptionSelected = 1;
}

void State::NewGame() {
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	canContinueGame = false;
	ResumeGame();
}

void State::ResumeGame() {
	gameState = GameState::Playing;
	isLockedPosition = false;
}

void State::ContinueGame() {
	ResumeGame();
	canContinueGame = false;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	deleteMatrix(rawBoardData, settings.boardSettings.boardRows);
	deleteMatrix(rawPlayerBoardData, settings.boardSettings.boardRows);
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

// Ingame state modifiers:
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
		currentInGameColIndex = settings.boardSettings.boardCols - 1;
	}
	else {
		--currentInGameColIndex;
	}
	isLockedPosition = false;
}

void State::MoveRightIngame() {
	++currentInGameColIndex;
	if (currentInGameColIndex > settings.boardSettings.boardCols - 1) {
		currentInGameColIndex = 0;
	}
	isLockedPosition = false;
}

void State::MoveUpIngame() {
	if (currentInGameRowIndex == 0) {
		currentInGameRowIndex = settings.boardSettings.boardRows - 1;
	}
	else {
		--currentInGameRowIndex;
	}

	isLockedPosition = false;
}

void State::MoveDownIngame() {
	++currentInGameRowIndex;
	if (currentInGameRowIndex > settings.boardSettings.boardRows - 1) {
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

// Change settings:
void State::SelectSize(ushort index) {
	currentSizeIndex = index;
	settings.boardSettings.boardRows = sizes[index]->rows;
	settings.boardSettings.boardCols = sizes[index]->cols;
	settings.boardSettings.bombsCount = sizes[index]->bombs;
	canContinueGame = false;
}

void State::SelectSymbols(ushort index) {
	currentSymbolsIndex = index;
	settings.boardSettings.bombMarked = symbols[index][0];
	settings.boardSettings.covered = symbols[index][1];
	settings.boardSettings.uncovered = symbols[index][2];
	settings.boardSettings.bombRevealed = symbols[index][3];
	for (ushort i = 0; i < 8; i++)
	{
		settings.boardSettings.numbers[i] = symbols[index][4 + i];
	}
	canContinueGame = false;
}

void State::SelectUncover(ushort index) {
	settings.uncoverType = (UncoverType)(index);
	canContinueGame = false;
}

void State::SelectControl(ushort index) {
	settings.controlType = (ControlType)(index);
}

void State::SelectLook(ushort index) {
	settings.boardLook = (BoardLook)(index);
}


// Getters:
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

const GameState& State::GetGameState() {
	return gameState;
}

const Settings& State::GetSettings() {
	return settings;
}