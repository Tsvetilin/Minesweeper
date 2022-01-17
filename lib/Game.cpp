#include "Game.hpp"
#include <cstring>

#include<iostream>

void Game::Start() {
	// Read settings
	state.ReadSettings();
	ApplySettings();
	display.WriteManual();
}

void Game::ApplySettings() {
	const Settings& settings = Game::state.GetSettings();
	if (settings.ControlType == ControlType::AdvancedArrowInput && player.IsAdvancedInputSupported()) {
		player.UseAdvancedInputSystem();
	}
	else {
		player.UseSimpleInputSystem();
		state.SelectControl(0);
	}

	// TODO: finish
}

bool Game::IsRunning() {
	return isRunning;
}

void Game::Update() {

	const GameState& currentState = Game::state.GetGameState();
	bool input = Game::player.GetInput();
	if (!input) {
		return;
	}

	const Settings& currentSettings = state.GetSettings();
	state.SetStatusMessage("");

	//std::cout << (int)currentState << "  " << (int)player.AdvancedInput << "  " << (int)currentSettings.ControlType << "\n";

	if (currentSettings.ControlType == ControlType::AdvancedArrowInput) {
		if (currentState == GameState::Unknown) {
			if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}
		else if (currentState == GameState::MainMenu) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				/*
				1. Start new game
				2. Continue game
				3. Change settings
				4. Save & Exit
				*/
				switch (state.GetCurrentMenuOptionSelected())
				{
				case 1:
					state.NewGame();
					engine.GenerateBoard(currentSettings.BoardSettings);
					state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
					//display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.currentInGameRowIndex, state.currentInGameColIndex, engine.board, state.GetStatusMessage());
					break;

				case 2:
					if (state.CanContinueGame()) {
						engine.LoadGame(currentSettings.BoardSettings, state.GetRawBoardData(), state.GetRawPlayerBoardData());
						state.ContinueGame(); // TODO: delete alloc memory
						state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
						display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
					}
					else {
						state.SetStatusMessage("Can't load previous game!");
						display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					}
					break;

				case 3:
					state.OpenSettingsMenu();
					display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					break;

				case 4:
					display.WriteExit(state.GetStatusMessage());
					isRunning = false;
					break;

				default:
					state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
					display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				isRunning = false;
				display.WriteExit(state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::Settings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				/*
					1. board size
					2. board symbols
					3. board uncover type
					4. board control type
					5. board look
				*/
				switch (state.GetCurrentMenuOptionSelected())
				{
				case 1:
					state.OpenSizeSettingsMenu();
					display.WriteSizeSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSizeOptions(), state.sizes, state.GetCurrentSizeIndex(), state.GetStatusMessage());
					break;

				case 2:
					state.OpenSymbolsSettingsMenu();
					display.WriteSymbolsSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSymbolsOptions(), state.symbols, state.GetCurrentSymbolsIndex(), state.GetStatusMessage());
					break;

				case 3:
					state.OpenUncoverSettingsMenu();
					display.WriteUncoverSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.UncoverType, state.GetStatusMessage());
					break;

				case 4:
					state.OpenControlSettingsMenu();
					display.WriteControlSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.ControlType, state.GetStatusMessage());
					break;

				case 5:
					state.OpenLookSettingsMenu();
					display.WriteLookSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.BoardLook, state.GetStatusMessage());
					break;

				default:
					state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
					display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::SizeSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(state.GetSizeOptions());

			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.GetSizeOptions());

			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSize(state.GetCurrentMenuOptionSelected() - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
			}
			display.WriteSizeSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSizeOptions(), state.sizes, state.GetCurrentSizeIndex(), state.GetStatusMessage());
		}

		else if (currentState == GameState::SymbolsSettings) {
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(state.GetSymbolsOptions());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.GetSymbolsOptions());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.SelectSymbols(state.GetCurrentMenuOptionSelected() - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
			}
			display.WriteSymbolsSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSymbolsOptions(), state.symbols, state.GetCurrentSymbolsIndex(), state.GetStatusMessage());
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
					state.SelectLook(state.GetCurrentMenuOptionSelected() - 1);
					break;
				case GameState::UncoverSettings:
					state.SelectUncover(state.GetCurrentMenuOptionSelected() - 1);
					break;
				case GameState::ControlSettings:
					state.SelectControl(state.GetCurrentMenuOptionSelected() - 1);
					break;
				}

				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
			}

			switch (state.GetGameState())
			{
			case GameState::LookSettings:
				display.WriteLookSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.BoardLook, state.GetStatusMessage());
				break;
			case GameState::UncoverSettings:
				display.WriteUncoverSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.UncoverType, state.GetStatusMessage());
				break;
			case GameState::ControlSettings:
				display.WriteControlSettingsMenu(state.GetCurrentMenuOptionSelected(), (int)currentSettings.ControlType, state.GetStatusMessage());
				break;
			}

		}

		else if (currentState == GameState::Playing) {
			state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.MoveDownIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}																					   
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {					   
				state.MoveUpIngame();															   
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}																					  
			else if (player.AdvancedInput == AdvancedPlayerInput::LeftArrow) {					  
				state.MoveLeftIngame();															  
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}																					
			else if (player.AdvancedInput == AdvancedPlayerInput::RightArrow) {					
				state.MoveRightIngame();														
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				state.LockIngamePosition();
				state.SetStatusMessage("Position locked. Press F for marking bomb or R for reveal.");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::MarkBomb || player.AdvancedInput == AdvancedPlayerInput::Reveal) {
				if (state.GetLockedPosition()) {
					Move move = player.AdvancedInput == AdvancedPlayerInput::MarkBomb ? Move::MarkBomb : Move::Reveal;
					state.UnlockIngamePosition();
					engine.PerformMove(move, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), currentSettings.BoardSettings, currentSettings.UncoverType);
				}
				else {
					state.SetStatusMessage("Please lock your position by pressing Enter!");
				}
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.OpenEscapeMenu();
				state.SetStatusMessage("");
				display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameColIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}

			if (engine.HasGameFinished()) {
				state.FinishGame();

				if (engine.IsWin()) {
					state.SetStatusMessage("You won! GG!\nPress Escape/Enter to continue...");
				}
				else {
					state.SetStatusMessage("You lost! Try again!\nPress Escape/Enter to continue...");
				}

				display.WriteFinishBoard(currentSettings.BoardLook, currentSettings.BoardSettings, engine.GetPlayerBoard(), engine.GetBoard(), state.GetStatusMessage());
				return;
			}
		}

		else if (currentState == GameState::Finished) {
			if (player.AdvancedInput == AdvancedPlayerInput::Escape || player.AdvancedInput == AdvancedPlayerInput::Select) {
				engine.FinishGame(currentSettings.BoardSettings);
				state.OpenMainMenu();
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::EscapeMenu) {

			/*
			1. Resume
			2. Save and Exit
			*/

			if (player.AdvancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
				display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
				display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Select) {
				switch (state.GetCurrentMenuOptionSelected())
				{
				case 1:
					state.ResumeGame();
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
					break;

				case 2:
					if (!engine.HasGameFinished()) {
						state.SaveGame(engine.GetPlayerBoard(), engine.GetBoard());
					}
					else {
						state.DeleteSavedGame();
					}
					state.OpenMainMenu();
					display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					break;
				default:
					state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet.");
					display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
					break;
				}
			}
			else if (player.AdvancedInput == AdvancedPlayerInput::Escape) {
				state.ResumeGame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::Exiting) {
			state.SetStatusMessage("Thanks for playing!");
			isRunning = false;
			display.WriteExit(state.GetStatusMessage());
		}


	}
	else if (currentSettings.ControlType == ControlType::PrimitiveInput)
	{

	}


}

void Game::SaveAndExit() {
	// sleep 2.5s and close

}