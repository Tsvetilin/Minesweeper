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


void State::ReadSettings() {}
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

void State::SelectSize(ushort index) {}
void State::SelectSymbols(ushort index) {}
void State::SelectUncover(ushort index) {}
void State::SelectControl(ushort index) {}
void State::SelectLook(ushort index) {}