#include "Game.hpp"
#include <cstring>

#include<iostream>

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

	std::cout << (int)currentState << "  " << (int)player.AdvancedInput << "  " << (int)currentSettings.ControlType << "\n";

	if (currentSettings.ControlType == ControlType::AdvancedArrowInput) {
		if (currentState == GameState::MainMenu) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
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
					//display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.board, state.GetStatusMessage());
					break;

				case 2:
					state.ContinueGame();
					if (state.GetGameState() == GameState::Unknown) {
						state.OpenSettingsMenu();
						state.SetStatusMessage("Can't load previous game!");
						display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					}
					else {
						engine.LoadGame(currentSettings.BoardSettings, state.rawBoardData, state.rawPlayerBoardData);
						display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
					}
					break;

				case 3:
					state.OpenSettingsMenu();
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
				state.IncreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
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
					state.OpenSizeSettingsMenu();
					display.WriteSizeSettingsMenu(state.currentMenuOptionSelected, state.sizeOptions, state.sizes, state.currentSizeIndex, state.GetStatusMessage());
					break;

				case 2:
					state.OpenSymbolsSettingsMenu();
					display.WriteSymbolsSettingsMenu(state.currentMenuOptionSelected, state.symbolsOptions, state.symbols, state.currentSymbolsIndex, state.GetStatusMessage());
					break;

				case 3:
					state.OpenUncoverSettingsMenu();
					display.WriteUncoverSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.UncoverType, state.GetStatusMessage());
					break;

				case 4:
					state.OpenControlSettingsMenu();
					display.WriteControlSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.ControlType, state.GetStatusMessage());
					break;

				case 5:
					state.OpenLookSettingsMenu();
					display.WriteLookSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.BoardLook, state.GetStatusMessage());
					break;

				default:
					state.SetStatusMessage("Invalid command");
					display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				display.WriteMainMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Invalid command");
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::SizeSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(state.sizeOptions);

			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.sizeOptions);

			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSize(state.currentMenuOptionSelected - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
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
				state.IncreaseMenuOptionSelected(state.symbolsOptions);
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.symbolsOptions);
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSymbols(state.currentMenuOptionSelected - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Invalid command");
			}
			display.WriteSymbolsSettingsMenu(state.currentMenuOptionSelected, state.symbolsOptions, state.symbols, state.currentSymbolsIndex, state.GetStatusMessage());
		}
		else if (currentState == GameState::LookSettings || currentState == GameState::UncoverSettings || currentState == GameState::ControlSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
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
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.currentMenuOptionSelected, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
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
				display.WriteLookSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.BoardLook, state.GetStatusMessage());
				break;
			case GameState::UncoverSettings:
				display.WriteUncoverSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.UncoverType, state.GetStatusMessage());
				break;
			case GameState::ControlSettings:
				display.WriteControlSettingsMenu(state.currentMenuOptionSelected, (int)currentSettings.ControlType, state.GetStatusMessage());
				break;
			}

		}

		else if (currentState == GameState::Playing) {
			if (engine.HasGameFinished()) {
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.board, state.GetStatusMessage());
				return;
			}

			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.MoveDownIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.MoveUpIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::LeftArrow) {
				state.MoveLeftIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::RightArrow) {
				state.MoveRightIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.LockIngamePosition();
				state.SetStatusMessage("Position locked. Press B for marking bomb or R for reveal.");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::MarkBomb || player.AdvancedInput == AdvancedPlayerInput::Reveal) {
				if (state.isLockedPosition) {
					Move move = player.AdvancedInput == AdvancedPlayerInput::MarkBomb ? Move::MarkBomb : Move::Reveal;
					state.UnlockIngamePosition();
					engine.PerformMove(move, state.currentInGameRowIndex, state.currentInGameColIndex, currentSettings.BoardSettings, currentSettings.UncoverType);
				}
				else {
					state.SetStatusMessage("Please lock your position by pressing Enter!");
				}
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				isRunning = false;
				state.SaveGame();
				display.WriteExit(state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Invalid command");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.playerBoard, state.GetStatusMessage());
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