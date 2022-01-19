#include "Game.hpp"
#include <cstring>

#include<iostream>

void Game::Start() {
	// Read settings
	state.ReadSettings();
	ApplySettings();
	display.WriteManual();
	isRunning = true;
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
	/*if (!input) {
		return;
	}
	*/
	const Settings& currentSettings = state.GetSettings();
	state.SetStatusMessage("");

	//std::cout << (int)currentState << "  " << (int)player.AdvancedInput << "  " << (int)currentSettings.ControlType << "\n";

	if (currentSettings.ControlType == ControlType::AdvancedArrowInput) {
		const AdvancedPlayerInput& advancedInput = player.GetAdvancedInput();

		if (currentState == GameState::Unknown) {
			if (advancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}
		else if (currentState == GameState::MainMenu) {
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
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
					break;

				case 2:
					if (state.CanContinueGame()) {
						engine.LoadGame(currentSettings.BoardSettings, state.GetRawBoardData(), state.GetRawPlayerBoardData());
						state.ContinueGame();
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
			else if (advancedInput == AdvancedPlayerInput::Escape) {
				isRunning = false;
				display.WriteExit(state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::Settings) {
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
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
			else if (advancedInput == AdvancedPlayerInput::Escape) {
				state.OpenMainMenu();
				display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter and make sure you are writing in the English alphabet. ");
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::SizeSettings) {
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(state.GetSizeOptions());

			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.GetSizeOptions());

			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
				state.SelectSize(state.GetCurrentMenuOptionSelected() - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else if (advancedInput == AdvancedPlayerInput::Escape) {
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
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(state.GetSymbolsOptions());
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(state.GetSymbolsOptions());
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
				state.SelectSymbols(state.GetCurrentMenuOptionSelected() - 1);
				state.SaveSettings();
				ApplySettings();
				state.OpenSettingsMenu();
				display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
				return;
			}
			else if (advancedInput == AdvancedPlayerInput::Escape) {
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
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
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
			else if (advancedInput == AdvancedPlayerInput::Escape) {
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
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.MoveDownIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.MoveUpIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::LeftArrow) {
				state.MoveLeftIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::RightArrow) {
				state.MoveRightIngame();
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
				state.LockIngamePosition();
				state.SetStatusMessage("Position locked. Press F for marking bomb or R for reveal.");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::MarkBomb || advancedInput == AdvancedPlayerInput::Reveal) {
				if (state.GetLockedPosition()) {
					Move move = advancedInput == AdvancedPlayerInput::MarkBomb ? Move::MarkBomb : Move::Reveal;
					state.UnlockIngamePosition();
					engine.PerformMove(move, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), currentSettings.BoardSettings, currentSettings.UncoverType);
				}
				else {
					state.SetStatusMessage("Please lock your position by pressing Enter!");
				}
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::Escape) {
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
			if (advancedInput == AdvancedPlayerInput::Escape || advancedInput == AdvancedPlayerInput::Select) {
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
			if (advancedInput == AdvancedPlayerInput::DownArrow) {
				state.IncreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
				display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::UpArrow) {
				state.DecreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
				display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			}
			else if (advancedInput == AdvancedPlayerInput::Select) {
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
			else if (advancedInput == AdvancedPlayerInput::Escape) {
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
		const SimplePlayerInput& simpleInput = player.GetSimpleInput();
		const char cmd = simpleInput.ingameCmd;
		const ushort num1 = simpleInput.num1;
		const ushort num2 = simpleInput.num2;
		const bool isValid = simpleInput.isValidCmd;


		if (currentState == GameState::Unknown) {
			if (isValid && cmd == QuitChar) {
				state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
				state.OpenMainMenu();
				display.WriteMainMenu(-1, state.GetStatusMessage());
			}
			else {
				display.WriteManual();
			}
		}

		else if (currentState == GameState::MainMenu) {
			if (isValid) {
				/*
				1. Start new game
				2. Continue game
				3. Change settings
				4. Save & Exit
				*/
				switch (cmd)
				{
				case '1':
					state.NewGame();
					engine.GenerateBoard(currentSettings.BoardSettings);
					state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position.");
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
					break;

				case '2':
					if (state.CanContinueGame()) {
						engine.LoadGame(currentSettings.BoardSettings, state.GetRawBoardData(), state.GetRawPlayerBoardData());
						state.ContinueGame();
						state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position.");
						display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
					}
					else {
						state.SetStatusMessage("Can't load previous game! Write a number from 1 to 4 to select an option.");
						display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
					}
					break;

				case '3':
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write a number from 1 to 5 to select an option.");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					break;

				case '4':
				case QuitChar:
					isRunning = false;
					display.WriteExit(state.GetStatusMessage());
					break;
				default:
					state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 4 to select an option.");
					display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
					break;
				}
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 4 to select an option.");
				display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::Settings) {
			if (isValid) {
				/*
					1. board size
					2. board symbols
					3. board uncover type
					4. board control type
					5. board look
				*/
				switch (cmd)
				{
				case '1':
					state.OpenSizeSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSizeSettingsMenu(InvalidIndex, state.GetSizeOptions(), state.sizes, state.GetCurrentSizeIndex(), state.GetStatusMessage());
					break;

				case '2':
					state.OpenSymbolsSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSymbolsSettingsMenu(InvalidIndex, state.GetSymbolsOptions(), state.symbols, state.GetCurrentSymbolsIndex(), state.GetStatusMessage());
					break;

				case '3':
					state.OpenUncoverSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteUncoverSettingsMenu(InvalidIndex, (int)currentSettings.UncoverType, state.GetStatusMessage());
					break;

				case '4':
					state.OpenControlSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteControlSettingsMenu(InvalidIndex, (int)currentSettings.ControlType, state.GetStatusMessage());
					break;

				case '5':
					state.OpenLookSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteLookSettingsMenu(InvalidIndex, (int)currentSettings.BoardLook, state.GetStatusMessage());
					break;

				case QuitChar:
					state.OpenMainMenu();
					state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
					display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
					break;

				default:
					state.SetStatusMessage("Status: Invalid command! Please write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					break;
				}
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Please write the number of you choice!");
				display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::SizeSettings) {

			if (isValid) {
				if (cmd >= '1' && cmd <= '0' + state.GetSizeOptions()) {
					state.SelectSize(cmd - '0' - 1);
					state.SaveSettings();
					ApplySettings();
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
				else if (cmd == QuitChar) {
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
			}

			state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
			display.WriteSizeSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSizeOptions(), state.sizes, state.GetCurrentSizeIndex(), state.GetStatusMessage());
		}

		else if (currentState == GameState::SymbolsSettings) {
			if (isValid) {
				if (cmd >= '1' && cmd <= '0' + state.GetSymbolsOptions()) {
					state.SelectSymbols(cmd - '0' - 1);
					state.SaveSettings();
					ApplySettings();
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
				else if (cmd == QuitChar) {
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
			}

			state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
			display.WriteSymbolsSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetSymbolsOptions(), state.symbols, state.GetCurrentSymbolsIndex(), state.GetStatusMessage());
		}
		else if (currentState == GameState::LookSettings || currentState == GameState::UncoverSettings || currentState == GameState::ControlSettings) {

			if (isValid) {
				if (cmd >= '1' && cmd <= OTHER_S_MENU_OPTIONS + '0') {
					switch (currentState)
					{
					case GameState::LookSettings:
						state.SelectLook(cmd - '0' - 1);
						break;
					case GameState::UncoverSettings:
						state.SelectUncover(cmd - '0' - 1);
						break;
					case GameState::ControlSettings:
						state.SelectControl(cmd - '0' - 1);
						break;
					}

					state.SaveSettings();
					ApplySettings();
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
				else if (cmd == QuitChar) {
					state.OpenSettingsMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WriteSettingsMenu(InvalidIndex, state.GetStatusMessage());
					return;
				}
			}
			state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
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
			state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");

			if (isValid) {
				if (cmd == QuitChar) {
					state.OpenEscapeMenu();
					state.SetStatusMessage("Write the number of you choice or Q to go back!");
					display.WritePauseMenu(InvalidIndex, state.GetStatusMessage());
				}
				else if (num1 > 0 && num1 <= currentSettings.BoardSettings.boardRows && num2 > 0 && num2 < currentSettings.BoardSettings.boardCols) {
					Move move = cmd == MarkChar ? Move::MarkBomb : Move::Reveal;
					engine.PerformMove(move, num1 - 1, num2 - 1, currentSettings.BoardSettings, currentSettings.UncoverType);
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
				}
				else
				{
					state.SetStatusMessage("Status: Invalid command! Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
				}
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
				display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
			}

			if (engine.HasGameFinished()) {
				state.FinishGame();

				if (engine.IsWin()) {
					state.SetStatusMessage("You won! GG!\nWrite Qto continue...");
				}
				else {
					state.SetStatusMessage("You lost! Try again!\nWrite Q to continue...");
				}

				display.WriteFinishBoard(currentSettings.BoardLook, currentSettings.BoardSettings, engine.GetPlayerBoard(), engine.GetBoard(), state.GetStatusMessage());
				return;
			}
		}

		else if (currentState == GameState::Finished) {
			if (isValid && cmd == QuitChar) {
				engine.FinishGame(currentSettings.BoardSettings);
				state.OpenMainMenu();
				state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
				display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
			}
			else {
				state.SetStatusMessage("Status: Invalid command! Write Q to continue...");
				display.WriteFinishBoard(currentSettings.BoardLook, currentSettings.BoardSettings, engine.GetPlayerBoard(), engine.GetBoard(), state.GetStatusMessage());
			}
		}

		else if (currentState == GameState::EscapeMenu) {
			/*
			1. Resume
			2. Save and Exit
			*/
			if (isValid) {
				if (cmd == QuitChar) {
					state.ResumeGame();
					state.SetStatusMessage("Status: Invalid command! Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
					display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, state.GetCurrentInGameRowIndex(), state.GetCurrentInGameColIndex(), engine.GetPlayerBoard(), state.GetStatusMessage());

				}
				else if (cmd > '0' && cmd <= OTHER_S_MENU_OPTIONS + '0') {
					switch (cmd)
					{
					case '1':
						state.ResumeGame();
						display.WriteBoard(currentSettings.BoardLook, currentSettings.BoardSettings, InvalidIndex, InvalidIndex, engine.GetPlayerBoard(), state.GetStatusMessage());
						break;

					case '2':
						if (!engine.HasGameFinished()) {
							state.SaveGame(engine.GetPlayerBoard(), engine.GetBoard());
						}
						else {
							state.DeleteSavedGame();
						}
						engine.FinishGame(currentSettings.BoardSettings);
						state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
						state.OpenMainMenu();
						display.WriteMainMenu(InvalidIndex, state.GetStatusMessage());
						break;
					default:
						state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
						display.WritePauseMenu(InvalidIndex, state.GetStatusMessage());
						break;
					}
				}
			}
		}

		else if (currentState == GameState::Exiting) {
			state.SetStatusMessage("Thanks for playing!");
			isRunning = false;
			display.WriteExit(state.GetStatusMessage());
		}

	}
}

void Game::SaveAndExit() {
	state.DeleteSettingsAllocatedMemory();
	state.SaveSettings();
}