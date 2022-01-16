#include "State.hpp"

#include <fstream>

void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	State::currentMenuOptionSelected = 1;
}

void State::SetStatusMessage(const char message[]) {
	strcpy_s(State::statusMessage, message);
}

const char const* State::GetStatusMessage() {
	return State::statusMessage;
}


void State::ReadSettings() {

	// TODO: Add appropriate values

	State::settings.ControlType = ControlType::AdvancedArrowInput;
	sizeOptions = 2;
	symbolsOptions = 0;
	currentSizeIndex = 0;
	currentSymbolsIndex = 0;

	sizes.push_back(Size(9, 9, 10));
	sizes.push_back(Size(15, 15, 20));

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

void State::SaveSettings() {}
void State::SaveGame() {}
// Set state:
void State::NewGame() {
	gameState = GameState::Playing;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	isLockedPosition = false;
}

void State::ContinueGame() {
	gameState = GameState::Playing;
}

void State::FinishGame() {
	gameState = GameState::Finished;
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
	settings.BoardSettings.boardRows = sizes[index].rows;
	settings.BoardSettings.boardCols = sizes[index].cols;
	settings.BoardSettings.bombsCount = sizes[index].bombs;
}

void State::SelectSymbols(ushort index) {}

void State::SelectUncover(ushort index) {
	settings.UncoverType = (UncoverType)(index);
}

void State::SelectControl(ushort index) {
	settings.ControlType = (ControlType)(index);
}

void State::SelectLook(ushort index) {
	settings.BoardLook = (BoardLook)(index);
}