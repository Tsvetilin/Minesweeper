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
* File with implementations of functions handling the current game state and settings
*
*/

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

	readSettingOptions();

	synchronizeOptionsSelected();
}

void State::DeleteSettingsAllocatedMemory() {
	for (short i = sizeOptions - 1; i >= 0; --i)
	{
		delete sizes[i];
		sizes.pop_back();
	}
	sizeOptions = 0;

	for (short i = symbolsOptions - 1; i >= 0; --i)
	{
		delete[] symbols[i];
		symbols.pop_back();
	}
	symbolsOptions = 0;
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
		}

		savedGame.close();
	}

	return canContinueGame;
}

void State::ReadSavedBoard() {
	if (canContinueGame) {

		std::fstream savedGame;
		savedGame.open(SAVED_GAME_FILE, std::ios::in);

		if (!savedGame.is_open()) {
			canContinueGame = false;
		}

		std::string buffer;
		rawBoardData = initializeMatrix(settings.boardSettings.boardRows, settings.boardSettings.boardCols);
		rawPlayerBoardData = initializeMatrix(settings.boardSettings.boardRows, settings.boardSettings.boardCols);

		std::getline(savedGame, buffer);
		if (buffer[0] == '\0') {
			canContinueGame = false;
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
}

// Set state:
void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	resetMenuIndex();
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
	resetMenuIndex();
}
void State::OpenSettingsMenu() {
	resetMenuIndex();
	gameState = GameState::Settings;
}
void State::OpenSizeSettingsMenu() {
	gameState = GameState::SizeSettings;
	resetMenuIndex();
}
void State::OpenSymbolsSettingsMenu() {
	gameState = GameState::SymbolsSettings;
	resetMenuIndex();
}
void State::OpenUncoverSettingsMenu() {
	gameState = GameState::UncoverSettings;
	resetMenuIndex();
}
void State::OpenControlSettingsMenu() {
	gameState = GameState::ControlSettings;
	resetMenuIndex();
}
void State::OpenLookSettingsMenu() {
	gameState = GameState::LookSettings;
	resetMenuIndex();
}

void State::resetMenuIndex() {
	currentMenuOptionSelected = settings.controlType == ControlType::AdvancedArrowInput ? 1 : -1;
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
const short& State::GetCurrentMenuOptionSelected() {
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

// TODO: add more validation cases & improve supported read syntax
void State::readSettingOptions() {

	std::fstream settingsTemplate;
	settingsTemplate.open(SETTINGS_TEMPLATE_FILE, std::ios::in);

	bool isJsonRead = false;
	bool isJsonCorrect = true;
	if (settingsTemplate.is_open()) {
		isJsonRead = true;
		bool isStarted = false;
		bool isSizeSectionStarted = false;
		bool isSymbolsSectionStarted = false;
		bool isSizeSectionFinished = false;
		bool isSymbolsSectionFinished = false;

		std::string buffer;
		while (true) {
			std::getline(settingsTemplate, buffer);

			if (buffer[0] == '\0') {
				break;
			}

			if (!isJsonCorrect) {
				break;
			}

			if (!isStarted) {
				if (isObjectStart(buffer)) {
					isStarted = true;
				}
				else {
					isJsonCorrect = false;
					break;
				}
			}
			else if (isStarted && 
					!((isSizeSectionStarted && !isSizeSectionFinished) || (isSymbolsSectionStarted && !isSymbolsSectionFinished)) &&
					!(isSizeSectionFinished && isSymbolsSectionFinished)) {
				if (isObjectName(buffer, SizeSection)) {
					if (isArrayStart(buffer)) {
						isSizeSectionStarted = true;
					}
					else {
						std::getline(settingsTemplate, buffer);
						isSizeSectionStarted = isArrayStart(buffer);
					}
				}
				else if (isObjectName(buffer, SymbolSection)) {
					if (isArrayStart(buffer)) {
						isSymbolsSectionStarted = true;
					}
					else {
						std::getline(settingsTemplate, buffer);
						isSymbolsSectionStarted = isArrayStart(buffer);
					}
				}
			}
			else if (isStarted && 
					 isSizeSectionStarted &&
					 !isSizeSectionFinished && 
					 (!isSymbolsSectionStarted || (isSymbolsSectionStarted && isSymbolsSectionFinished))) {
				if (!isObjectStart(buffer)) {
					isJsonCorrect = false;
					break;
				}

				while (true) {

					ushort rows = 0;
					ushort cols = 0;
					ushort bombs = 0;
					std::getline(settingsTemplate, buffer);
					if (!getIntValueWithNameCheck(buffer, SizeSectionRows, rows)) {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (!getIntValueWithNameCheck(buffer, SizeSectionCols, cols)) {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (!getIntValueWithNameCheck(buffer, SizeSectionBombs, bombs)) {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (!isObjectEnd(buffer)) {
						isJsonCorrect = false;
						break;
					}

					sizes.push_back(new Size(rows, cols, bombs));
					++sizeOptions;

					std::getline(settingsTemplate, buffer);
					if (isObjectStart(buffer)) {
					}
					else if (isArrayEnd(buffer)) {
						isSizeSectionFinished = true;
						break;
					}
					else {
						isJsonCorrect = false;
						break;
					}

				}
			}
			else if (isStarted && 
					 isSymbolsSectionStarted &&
					 !isSymbolsSectionFinished &&
					 (!isSizeSectionStarted || (isSizeSectionStarted && isSizeSectionFinished))) {
				if (!isObjectStart(buffer)) {
					isJsonCorrect = false;
					break;
				}

				char result[SYMBOLS_CHAR_ARRAY_SIZE]{};
				result[SYMBOLS_CHAR_ARRAY_SIZE - 1] = '\0';
				while (true) {
					std::string temp;


					std::getline(settingsTemplate, buffer);
					if (getStringtValueWithNameCheck(buffer, SymbolSectionMarked, temp)) {
						result[0] = temp[0];
					}
					else {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (getStringtValueWithNameCheck(buffer, SymbolSectionCovered, temp)) {
						result[1] = temp[0];
					}
					else {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (getStringtValueWithNameCheck(buffer, SymbolSectionUncovered, temp)) {
						result[2] = temp[0];
					}
					else {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (getStringtValueWithNameCheck(buffer, SymbolSectionRevealed, temp)) {
						result[3] = temp[0];
					}
					else {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (getStringtValueWithNameCheck(buffer, SymbolSectionNumbers, temp)) {
						copyLine(temp.c_str(), result + 4, 8);
					}
					else {
						isJsonCorrect = false;
						break;
					}

					std::getline(settingsTemplate, buffer);
					if (!isObjectEnd(buffer)) {
						isJsonCorrect = false;
						break;
					}

					char* toAdd = new char[SYMBOLS_CHAR_ARRAY_SIZE];
					copyString(result, toAdd, strLen(result));
					symbols.push_back(toAdd);
					++symbolsOptions;

					std::getline(settingsTemplate, buffer);
					if (isObjectStart(buffer)) {
					}
					else if (isArrayEnd(buffer)) {
						isSymbolsSectionFinished = true;
						break;
					}
					else {
						isJsonCorrect = false;
						break;
					}

				}
			}
			else if (isStarted && isSymbolsSectionFinished && isSizeSectionFinished) {
				if (isObjectEnd(buffer)) {
					break;
				}
				else {
					isJsonCorrect = false;
					break;
				}
			}
			else {
				isJsonCorrect = false;
				break;
			}

		}
		settingsTemplate.close();
	}

	if (isJsonRead && !isJsonCorrect) {
		DeleteSettingsAllocatedMemory();
		isJsonRead = false;
	}

	if (!isJsonRead) {
		// add default settings options

		currentSizeIndex = 0;
		currentSymbolsIndex = 0;

		symbolsOptions = 3;
		symbols.push_back(new char[SYMBOLS_CHAR_ARRAY_SIZE] {'F', '_', '-', 'B', '1', '2', '3', '4', '5', '6', '7', '8', '\0'});
		symbols.push_back(new char[SYMBOLS_CHAR_ARRAY_SIZE] {'R', '-', '0', 'X', '1', '2', '3', '4', '5', '6', '7', '8', '\0'});
		symbols.push_back(new char[SYMBOLS_CHAR_ARRAY_SIZE] {'M', ' ', '*', 'B', '1', '2', '3', '4', '5', '6', '7', '8', '\0'});

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

void State::synchronizeOptionsSelected() {
	short ind = -1;
	for (ushort i = 0; i < sizeOptions; ++i)
	{
		if (sizes[i]->bombs == settings.boardSettings.bombsCount &&
			sizes[i]->rows == settings.boardSettings.boardRows &&
			sizes[i]->cols == settings.boardSettings.boardCols) {
			ind = i;
			break;
		}
	}

	if (ind != -1) {
		currentSizeIndex = ind;
	}
	else {
		sizes.push_back(new Size(settings.boardSettings.boardRows,
			settings.boardSettings.boardCols,
			settings.boardSettings.bombsCount));
		++sizeOptions;
		currentSizeIndex = (ushort)(sizes.size() - 1);
	}


	ind = -1;
	for (ushort i = 0; i < symbolsOptions; ++i)
	{
		if (symbols[i][0] == settings.boardSettings.bombMarked &&
			symbols[i][1] == settings.boardSettings.covered &&
			symbols[i][2] == settings.boardSettings.uncovered &&
			symbols[i][3] == settings.boardSettings.bombRevealed &&
			strcmp(symbols[i] + 4, settings.boardSettings.numbers) == 0) {
			ind = i;
			break;
		}
	}

	if (ind != -1) {
		currentSymbolsIndex = ind;
	}
	else {
		char* result = new char[SYMBOLS_CHAR_ARRAY_SIZE] {};
		result[SYMBOLS_CHAR_ARRAY_SIZE - 1] = '\0';
		result[0] = settings.boardSettings.bombMarked;
		result[1] = settings.boardSettings.covered;
		result[2] = settings.boardSettings.uncovered;
		result[3] = settings.boardSettings.bombRevealed;
		copyString(settings.boardSettings.numbers, result + 4, 8);

		symbols.push_back(result);
		++symbolsOptions;
		currentSymbolsIndex = (ushort)symbols.size() - 1;
	}
}