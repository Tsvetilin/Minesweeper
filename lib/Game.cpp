#include "Game.hpp"
#include <cstring>
/*
	void Start();		// Initialize according to settings
	bool IsRunning();	// Return true/false according to current state
	void Update();		// Get user input, update the game state, draw the game
	void SaveAndExit(); // Save current state and settings
*/


void Game::Start() {
	// Read settings

	state.currentMenuOptionSelected = 1;
	display.WriteMainMenu(state.currentMenuOptionSelected);
}

bool Game::IsRunning() {
	return true;
}

void Game::Update() {
	
	GameState currentState = Game::state.GetGameState();
	bool input = Game::player.GetInput();
	if (!input) {
		return;
	}

	Settings currentSettings = state.GetSettings();
	state.SetStatusMessage("");

	if (currentSettings.ControlType == ControlType::AdvancedArrowInput) {
		if (currentState == GameState::MainMenu) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > MAIN_MENU_OPTIONS_COUNT) {
					state.currentMenuOptionSelected = 1;
				}
				display.WriteMainMenu(state.currentMenuOptionSelected);
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 0) {
					state.currentMenuOptionSelected = MAIN_MENU_OPTIONS_COUNT;
				}
				display.WriteMainMenu(state.currentMenuOptionSelected);
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				/*
				1. Start new game
				2. Continue game
				3. Change settings
				4. Save & Exit
				*/

				switch (state.currentMenuOptionSelected)
				{
				case 1: state.NewGame(); break;
				case 2: state.ContinueGame(); break;
				case 3: state.OpenSettingsMenu(); break;
				case 4: state.SaveGame(); break;

				default:
					state.SetStatusMessage("Invalid command");
					display.WriteMainMenu(state.currentMenuOptionSelected);
					break;
				}
			}
			else {
				state.SetStatusMessage("Invalid command");
				display.WriteMainMenu(state.currentMenuOptionSelected);
			}
		}
	}
	else if (currentSettings.ControlType == ControlType::PrimitiveInput)
	{

	}
	

}

