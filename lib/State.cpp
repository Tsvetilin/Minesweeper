#include "State.hpp"

#include <fstream>

void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	State::currentMenuOptionSelected = 1;
}

void State::SetStatusMessage(const char message[]) {
	strcpy_s(State::statusMessage, message);
}

char* State::GetStatusMessage() {
	return State::statusMessage;
}


void State::ReadSettings() {

	// Add appropriate values

	State::settings.ControlType = ControlType::AdvancedArrowInput;
	sizeOptions = 2;
	symbolsOptions = 0;
	currentSizeIndex = 0;
	currentSymbolsIndex = 0;
	
	sizes.push_back(Size(9, 9, 10));
	sizes.push_back(Size(15, 15, 20));

}

void State::SaveSettings() {}
void State::SaveGame() {}
// Set state:
void State::NewGame() {
	gameState = GameState::Playing;
}
void State::ContinueGame() {
	gameState = GameState::Playing;
}
void State::OpenEscapeMenu() {
	gameState = GameState::EscapeMenu;
}
void State::OpenSettingsMenu() {
	gameState = GameState::Settings;
}
void State::OpenSizeSettingsMenu() {
	gameState = GameState::SizeSettings;
}
void State::OpenSymbolsSettingsMenu() {
	gameState = GameState::SymbolsSettings;
}
void State::OpenUncoverSettingsMenu() {
	gameState = GameState::UncoverSettings;
}
void State::OpenControlSettingsMenu() {
	gameState = GameState::ControlSettings;
}
void State::OpenLookSettingsMenu() {
	gameState = GameState::LookSettings;
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