#include "Game.hpp"
#include <cstring>

#include<iostream>
/*
	void Start();		// Initialize according to settings
	bool IsRunning();	// Return true/false according to current state
	void Update();		// Get user input, update the game state, draw the game
	void SaveAndExit(); // Save current state and settings
*/


void Game::Start() {
	// Read settings
	state.ReadSettings();
	ApplySettings();

	state.OpenMainMenu();
	state.currentMenuOptionSelected = 1;
	
	display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
}

void Game::ApplySettings() {
	Game::player.UseAdvancedInputSystem();
}

bool Game::IsRunning() {
	return isRunning;
}

void Game::Update() {

	GameState currentState = Game::state.GetGameState();
	bool input = Game::player.GetInput();
	if (!input) {
		return;
	}

	Settings currentSettings = state.GetSettings();
	state.SetStatusMessage("");

	std::cout << (int)currentState << "  " << (int)player.AdvancedInput <<"  "<< (int)currentSettings.ControlType << "\n";

	if (currentSettings.ControlType == ControlType::AdvancedArrowInput) {
		if (currentState == GameState::MainMenu) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > MAIN_MENU_OPTIONS_COUNT) {
					state.currentMenuOptionSelected = 1;
				}
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 1) {
					state.currentMenuOptionSelected = MAIN_MENU_OPTIONS_COUNT;
				}
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
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
				case 1:
					state.NewGame();
					engine.GenerateBoard(currentSettings.BoardSettings);
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, engine.playerBoard, state.GetStatusMessage());
					break;

				case 2:
					state.ContinueGame();
					if (state.GetGameState() == GameState::Unknown) {
						state.SetStatusMessage("Can't load previous game!");
						display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					}
					else {
						engine.LoadGame(currentSettings.BoardSettings, state.rawBoardData, state.rawPlayerBoardData);
						display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, engine.playerBoard, state.GetStatusMessage());
					}
					break;

				case 3:
					state.OpenSettingsMenu();
					state.currentMenuOptionSelected = 1;
					display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					break;

				case 4:
					state.SaveGame();
					display.WriteExit(state.GetStatusMessage());
					isRunning = false;
					break;

				default:
					state.SetStatusMessage("Invalid command");
					display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				isRunning = false;
				state.SaveGame();
				display.WriteExit(state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Invalid command");
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::Settings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > SETTINGS_MENU_OPTIONS_COUNT) {
					state.currentMenuOptionSelected = 1;
				}
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 1) {
					state.currentMenuOptionSelected = SETTINGS_MENU_OPTIONS_COUNT;
				}
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				/*
					1. board size
					2. board symbols
					3. board uncover type
					4. board control type
					5. board look
				*/
				switch (state.currentMenuOptionSelected)
				{
				case 1:
					state.currentMenuOptionSelected = 1;
					state.OpenSizeSettingsMenu();
					display.WriteSizeSettingsMenu(state.currentMenuOptionSelected, state.sizeOptions, state.sizes, state.currentSizeIndex, state.GetStatusMessage());
					break;

				case 2:
					state.currentMenuOptionSelected = 1;
					state.OpenSymbolsSettingsMenu();
					display.WriteSymbolsSettingsMenu(state.currentMenuOptionSelected, state.symbolsOptions, state.symbols,state.currentSymbolsIndex, state.GetStatusMessage());
					break;

				case 3:
					state.currentMenuOptionSelected = 1;
					state.OpenUncoverSettingsMenu();
					display.WriteUncoverSettingsMenu(state.currentMenuOptionSelected,(int)currentSettings.UncoverType, state.GetStatusMessage());
					break;

				case 4:
					state.currentMenuOptionSelected = 1;
					state.OpenControlSettingsMenu();
					display.WriteControlSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.ControlType, state.GetStatusMessage());
					break;

				case 5:
					state.currentMenuOptionSelected = 1;
					state.OpenLookSettingsMenu();
					display.WriteLookSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.BoardLook , state.GetStatusMessage());
					break;

				default:
					state.SetStatusMessage("Invalid command");
					display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				state.currentMenuOptionSelected = 1;
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Invalid command");
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::SizeSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > state.sizeOptions) {
					state.currentMenuOptionSelected = 1;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 1) {
					state.currentMenuOptionSelected = state.sizeOptions;
				}

			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSize(state.currentMenuOptionSelected - 1);
				state.SaveSettings();
				ApplySettings();
				state.currentMenuOptionSelected = 1;
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				state.currentMenuOptionSelected = 1;
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Invalid command");
			}
			display.WriteSizeSettingsMenu(state.currentMenuOptionSelected, state.sizeOptions, state.sizes, state.currentSizeIndex, state.GetStatusMessage());
		}

		else if (currentState == GameState::SymbolsSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > state.symbolsOptions) {
					state.currentMenuOptionSelected = 1;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 1) {
					state.currentMenuOptionSelected = state.symbolsOptions;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSymbols(state.currentMenuOptionSelected - 1);
				state.SaveSettings();
				ApplySettings();
				state.currentMenuOptionSelected = 1;
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				state.currentMenuOptionSelected = 1;
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Invalid command");
			}
			display.WriteSymbolsSettingsMenu(state.currentMenuOptionSelected, state.symbolsOptions, state.symbols,state.currentSymbolsIndex, state.GetStatusMessage());
		}
		else if (currentState == GameState::LookSettings || currentState == GameState::UncoverSettings || currentState == GameState::ControlSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				++state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected > OTHER_S_MENU_OPTIONS) {
					state.currentMenuOptionSelected = 1;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				--state.currentMenuOptionSelected;
				if (state.currentMenuOptionSelected < 1) {
					state.currentMenuOptionSelected = OTHER_S_MENU_OPTIONS;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				switch (currentState)
				{
				case GameState::LookSettings:
					state.SelectLook(state.currentMenuOptionSelected - 1);
					break;
				case GameState::UncoverSettings:
					state.SelectUncover(state.currentMenuOptionSelected - 1);
					break;
				case GameState::ControlSettings:
					state.SelectControl(state.currentMenuOptionSelected - 1);
					break;
				}

				state.SaveSettings();
				ApplySettings();
				state.currentMenuOptionSelected = 1;
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				state.currentMenuOptionSelected = 1;
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Invalid command");
			}

			currentState = state.GetGameState();
			switch (currentState)
			{
			case GameState::LookSettings:
				display.WriteLookSettingsMenu(state.currentMenuOptionSelected,(int)currentSettings.BoardLook, state.GetStatusMessage());
				break;
			case GameState::UncoverSettings:
				display.WriteUncoverSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.UncoverType,state.GetStatusMessage());
				break;
			case GameState::ControlSettings:
				display.WriteControlSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.ControlType, state.GetStatusMessage());
				break;
			}

		}




	}
	else if (currentSettings.ControlType == ControlType::PrimitiveInput)
	{

	}


}

void Game::SaveAndExit() {
	// sleep 2.5s and close

}