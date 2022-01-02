#include "State.hpp"

#include <fstream>


void State::OpenMainMenu() {
	State::gameState = GameState::MainMenu;
	State::currentMenuOptionSelected = 1;
}

void State::SetStatusMessage(const char message[]) {
	strcpy(State::statusMessage, message);
}