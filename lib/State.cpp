#include "State.hpp"

#include <fstream>
#include <string>

State::State() {
	State::gameState = GameState::Unknown;
}

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

	std::fstream settingsFile;
	settingsFile.open(GAME_SETTINGS_FILE, std::ios::binary | std::ios::in);

	if (settingsFile.is_open()) {
		settingsFile.read((char*)&(State::settings),sizeof(State::settings));
		settingsFile.close();
	}

	std::fstream settingsTemplate;
	settingsTemplate.open(SETTINGS_TEMPLATE_FILE, std::ios::binary | std::ios::in);
	if (settingsTemplate.is_open()) {
		std::string buffer;
		while (true) {
			std::getline(settingsTemplate, buffer);
			if (buffer[0] == '\0') {
				break;
			}

		}
	}
	else {
		sizeOptions = 2;
		symbolsOptions = 0;
		currentSizeIndex = 0;
		currentSymbolsIndex = 0;

		sizes.push_back(Size(9, 9, 10));
		sizes.push_back(Size(15, 15, 20));
	}

	State::settings.ControlType = ControlType::AdvancedArrowInput;


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
void State::SaveGame(const char* const* playerBoard, const char* const* board){}
// Set state:
void State::NewGame() {
	gameState = GameState::Playing;
	currentInGameColIndex = 0;
	currentInGameRowIndex = 0;
	isLockedPosition = false;
	// Make impossible to read file
}

void State::ResumeGame() {
	gameState = GameState::Playing;
	isLockedPosition = false;
}

void State::ContinueGame() {
	gameState = GameState::Playing;
	// Make impossible to read file
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
	// Make impossible to read file
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