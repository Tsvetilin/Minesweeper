#include "Game.hpp"
#include <cstring>

void Game::Start() {
	state.ReadSettings();
	ApplySettings();
	display.WriteManual();
	isRunning = true;
}

void Game::ApplySettings() {
	const Settings& settings = Game::state.GetSettings();
	if (settings.controlType == ControlType::AdvancedArrowInput && player.IsAdvancedInputSupported()) {
		player.UseAdvancedInputSystem();
	}
	else {
		player.UseSimpleInputSystem();
		state.SelectControl(0);
	}
}

bool Game::IsRunning() {
	return isRunning;
}


void Game::Update() {

	const GameState& currentState = Game::state.GetGameState();

	Game::player.GetInput();

	if (currentState == GameState::Unknown) {
		handleStateUnknown();
	}
	else if (currentState == GameState::MainMenu) {
		handleStateMainMenu();
	}
	else if (currentState == GameState::Settings) {
		handleStateSettingsMenu();
	}
	else if (currentState == GameState::SizeSettings || currentState == GameState::SymbolsSettings || currentState == GameState::LookSettings || currentState == GameState::UncoverSettings || currentState == GameState::ControlSettings) {
		handleStateSelectSettings();
	}
	else if (currentState == GameState::Playing) {
		handleStatePlaying();
	}
	else if (currentState == GameState::Finished) {
		handleStateFinished();
	}
	else if (currentState == GameState::EscapeMenu) {
		handleStateEscapeMenu();
	}
	else if (currentState == GameState::Exiting) {
		handleStateExiting();
	}

}

void Game::SaveAndExit() {
	state.DeleteSettingsAllocatedMemory();
	state.SaveSettings();
}

void Game::handleStateUnknown() {
	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
		if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			state.OpenMainMenu();
			state.SetStatusMessage("Use Arrow keys / Enter / Escape(or Q) to navigate!");
			display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			return;
		}
	}
	else {
		if (player.GetSimpleInput().isValidCmd && player.GetSimpleInput().ingameCmd == QuitChar) {
			state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
			state.OpenMainMenu();
			display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			return;
		}
	}

	display.WriteManual();
}

void Game::handleStateMainMenu() {

	bool isInvalidCmd = false;
	bool isEscape = false;
	short optionSelectedIndex = InvalidIndex;
	short x = InvalidIndex;
	short y = InvalidIndex;

	/*
	1. Start new game
	2. Continue game
	3. Change settings
	4. Save & Exit
	*/

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {

		state.SetStatusMessage("Use Arrow keys / Enter / Escape(or Q) to navigate!");

		if (player.GetAdvancedInput() == AdvancedPlayerInput::DownArrow) {
			state.IncreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::UpArrow) {
			state.DecreaseMenuOptionSelected(MAIN_MENU_OPTIONS_COUNT);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Select) {

			switch (state.GetCurrentMenuOptionSelected())
			{
			case 1:
				state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
				break;
			case 2:
				if (state.CanContinueGame()) {
					state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
				}
				else {
					isInvalidCmd = true;
					state.SetStatusMessage("Can't load previous game!");
				}
				break;

			case 4:
				isEscape = true;
				break;

			default:
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
				break;
			}
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			isEscape = true;
			state.SetStatusMessage("Thanks for playing!");
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
		}

		optionSelectedIndex = state.GetCurrentMenuOptionSelected();
	}
	else {
		if (player.GetSimpleInput().isValidCmd) {
			optionSelectedIndex = player.GetSimpleInput().ingameCmd - '0';
			switch (player.GetSimpleInput().ingameCmd)
			{
			case '1':
				state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position.");
				break;

			case '2':
				if (state.CanContinueGame()) {
					state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position.");
				}
				else {
					state.SetStatusMessage("Can't load previous game! Write a number from 1 to 4 to select an option.");
					isInvalidCmd = true;
				}
				break;

			case '3':
				state.SetStatusMessage("Write a number from 1 to 5 to select an option.");
				break;

			case '4':
			case QuitChar:
				isEscape = true;
				break;
			default:
				isInvalidCmd = true;
				state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 4 to select an option.");
				break;
			}
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 4 to select an option.");
		}
	}

	if (isEscape) {
		handleStateExiting();
		return;
	}
	else if (!isInvalidCmd) {
		switch (optionSelectedIndex)
		{
		case 1:
			state.NewGame();
			engine.GenerateBoard(state.GetSettings().boardSettings);
			if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
				x = state.GetCurrentInGameRowIndex();
				y = state.GetCurrentInGameColIndex();
			}
			display.WriteBoard(state.GetSettings().boardLook,
							   state.GetSettings().boardSettings, 
							   x,
							   y,
							   engine.GetPlayerBoard(), 
							   state.GetStatusMessage());
			return;

		case 2:
			if (state.CanContinueGame()) {
				state.ReadSavedBoard();
				engine.LoadGame(state.GetSettings().boardSettings, state.GetRawBoardData(), state.GetRawPlayerBoardData());
				state.ContinueGame();
				if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
					x = state.GetCurrentInGameRowIndex();
					y = state.GetCurrentInGameColIndex();
				}
				display.WriteBoard(state.GetSettings().boardLook,
								   state.GetSettings().boardSettings,
								   x,
								   y, 
								   engine.GetPlayerBoard(), 
								   state.GetStatusMessage());
			}
			return;

		case 3:
			state.OpenSettingsMenu();
			display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			return;
		}
	}

	display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
}

void Game::handleStateSettingsMenu() {
	bool isInvalidCmd = false;
	bool isEscape = false;
	short optionSelectedIndex = InvalidIndex;

	/*
	1. board size
	2. board symbols
	3. board uncover type
	4. board control type
	5. board look
	*/

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {

		state.SetStatusMessage("Use Arrow keys to navigate, Enter to select and Escape(or Q) to go back!");

		if (player.GetAdvancedInput() == AdvancedPlayerInput::DownArrow) {
			state.IncreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::UpArrow) {
			state.DecreaseMenuOptionSelected(SETTINGS_MENU_OPTIONS_COUNT);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Select) {
			isInvalidCmd = false;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			isEscape = true;
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
		}

		optionSelectedIndex = state.GetCurrentMenuOptionSelected();
	}
	else {
		if (player.GetSimpleInput().isValidCmd) {
			optionSelectedIndex = player.GetSimpleInput().ingameCmd - '0';

			if (optionSelectedIndex > 0 && optionSelectedIndex <= SETTINGS_MENU_OPTIONS_COUNT) {
				state.SetStatusMessage("Write the number of you choice or Q to go back!");
			}
			else if (player.GetSimpleInput().ingameCmd == QuitChar) {
				isEscape = true;
				state.SetStatusMessage("Use Arrow keys / Enter / Escape(or Q) to navigate!");
			}
			else {
				isInvalidCmd = true;
				state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 5 to select an option.");

			}
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Write a number from 1 to 5 to select an option.");
		}
	}

	if (isEscape) {
		state.OpenMainMenu();
		display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
		return;
	}
	else if (!isInvalidCmd) {
		switch (optionSelectedIndex)
		{
		case 1:
			state.OpenSizeSettingsMenu();
			display.WriteSizeSettingsMenu(state.GetCurrentMenuOptionSelected(), 
										  state.GetSizeOptions(), 
										  state.sizes, 
										  state.GetCurrentSizeIndex(), 
										  state.GetStatusMessage());
			return;

		case 2:
			state.OpenSymbolsSettingsMenu();
			display.WriteSymbolsSettingsMenu(state.GetCurrentMenuOptionSelected(),
										     state.GetSymbolsOptions(), 
										     state.symbols, 
										     state.GetCurrentSymbolsIndex(),
										     state.GetStatusMessage());
			return;

		case 3:
			state.OpenUncoverSettingsMenu();
			display.WriteUncoverSettingsMenu(state.GetCurrentMenuOptionSelected(),
											 (int)state.GetSettings().uncoverType, 
											 state.GetStatusMessage());
			return;

		case 4:
			state.OpenControlSettingsMenu();
			display.WriteControlSettingsMenu(state.GetCurrentMenuOptionSelected(),
											(int)state.GetSettings().controlType, 
											state.GetStatusMessage());
			return;

		case 5:
			state.OpenLookSettingsMenu();
			display.WriteLookSettingsMenu(state.GetCurrentMenuOptionSelected(), 
										 (int)state.GetSettings().boardLook,
										 state.GetStatusMessage());
			return;
		}
	}

	display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
}

void Game::handleStateSelectSettings() {
	bool isInvalidCmd = false;
	bool isEscape = false;
	short optionSelectedIndex = InvalidIndex;

	ushort maxNumberOfOptions = 0;
	if (state.GetGameState() == GameState::SizeSettings) {
		maxNumberOfOptions = state.GetSizeOptions();
	}
	else if (state.GetGameState() == GameState::SymbolsSettings) {
		maxNumberOfOptions = state.GetSymbolsOptions();
	}
	else {
		maxNumberOfOptions = OTHER_S_MENU_OPTIONS;
	}

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {

		state.SetStatusMessage("Use Arrow keys to navigate, Enter to select and Escape(or Q) to go back!");

		if (player.GetAdvancedInput() == AdvancedPlayerInput::DownArrow) {
			state.IncreaseMenuOptionSelected(maxNumberOfOptions);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::UpArrow) {
			state.DecreaseMenuOptionSelected(maxNumberOfOptions);
			isInvalidCmd = true;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Select) {
			isInvalidCmd = false;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			isEscape = true;
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
		}

		optionSelectedIndex = state.GetCurrentMenuOptionSelected();
	}
	else {
		if (player.GetSimpleInput().isValidCmd) {
			optionSelectedIndex = player.GetSimpleInput().ingameCmd - '0';

			if (optionSelectedIndex > 0 && optionSelectedIndex <= maxNumberOfOptions) {
				isInvalidCmd = false;
				state.SetStatusMessage("Write a number to select an option or Q to go back!");
			}
			else if (player.GetSimpleInput().ingameCmd == QuitChar) {
				isEscape = true;
				state.SetStatusMessage("Write a number to select an option or Q to go back!.");
			}
			else {
				isInvalidCmd = true;
				state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
			}
		}
		else {
			isInvalidCmd = true;
			state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
		}
	}

	if (isEscape) {
		state.OpenSettingsMenu();
		display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
		return;
	}
	else if (!isInvalidCmd) {
		switch (state.GetGameState())
		{
		case GameState::SizeSettings:
			state.SelectSize(optionSelectedIndex - 1);
			break;
		case GameState::SymbolsSettings:
			state.SelectSymbols(optionSelectedIndex - 1);
			break;
		case GameState::LookSettings:
			state.SelectLook(optionSelectedIndex - 1);
			break;
		case GameState::UncoverSettings:
			state.SelectUncover(optionSelectedIndex - 1);
			break;
		case GameState::ControlSettings:
			state.SelectControl(optionSelectedIndex - 1);
			if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
				state.SetStatusMessage("Use Arrow keys to navigate, Enter to select and Escape(or Q) to go back!");
			}
			else {
				state.SetStatusMessage("Write a number from 1 to 5 to select an option or Q to go back!.");
			}
			break;
		default:
			break;
		}

		state.SaveSettings();
		ApplySettings();
		state.OpenSettingsMenu();
		display.WriteSettingsMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
		return;
	}

	switch (state.GetGameState())
	{
	case GameState::SizeSettings:
		display.WriteSizeSettingsMenu(state.GetCurrentMenuOptionSelected(),
									  state.GetSizeOptions(),
									  state.sizes, state.GetCurrentSizeIndex(),
									  state.GetStatusMessage());
		break;
	case GameState::SymbolsSettings:
		display.WriteSymbolsSettingsMenu(state.GetCurrentMenuOptionSelected(),
										 state.GetSymbolsOptions(),
										 state.symbols,
										 state.GetCurrentSymbolsIndex(), 
										 state.GetStatusMessage());
		break;
	case GameState::LookSettings:
		display.WriteLookSettingsMenu(state.GetCurrentMenuOptionSelected(), 
									  (int)state.GetSettings().boardLook,
									  state.GetStatusMessage());
		break;
	case GameState::UncoverSettings:
		display.WriteUncoverSettingsMenu(state.GetCurrentMenuOptionSelected(), 
										 (int)state.GetSettings().uncoverType,
										 state.GetStatusMessage());
		break;
	case GameState::ControlSettings:
		display.WriteControlSettingsMenu(state.GetCurrentMenuOptionSelected(),
										 (int)state.GetSettings().controlType,
										 state.GetStatusMessage());
		break;
	default:
		break;
	}
}

void Game::handleStatePlaying() {

	short x = InvalidIndex;
	short y = InvalidIndex;

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {

		state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");

		if (player.GetAdvancedInput() == AdvancedPlayerInput::DownArrow) {
			state.MoveDownIngame();
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::UpArrow) {
			state.MoveUpIngame();
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::LeftArrow) {
			state.MoveLeftIngame();
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::RightArrow) {
			state.MoveRightIngame();
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Select) {
			state.LockIngamePosition();
			state.SetStatusMessage("Position locked. Press F for marking bomb or R for reveal.");
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::MarkBomb ||
				 player.GetAdvancedInput() == AdvancedPlayerInput::Reveal) {
			if (state.GetLockedPosition()) {
				Move move = player.GetAdvancedInput() == AdvancedPlayerInput::MarkBomb ? Move::MarkBomb : Move::Reveal;
				state.UnlockIngamePosition();
				engine.PerformMove(move,
								   state.GetCurrentInGameRowIndex(),
								   state.GetCurrentInGameColIndex(), 
								   state.GetSettings().boardSettings,
								   state.GetSettings().uncoverType);
			}
			else {
				state.SetStatusMessage("Please lock your position by pressing Enter!");
			}
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			state.OpenEscapeMenu();
			state.SetStatusMessage("Game paused. Use arrow keys to navigate and Enter to select or press Escape(or Q) to go back!");
			display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
			return;
		}
		else {
			state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
		}
		x = state.GetCurrentInGameRowIndex();
		y = state.GetCurrentInGameColIndex();
	}
	else {
		if (player.GetSimpleInput().isValidCmd) {

			state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. \
Write Q for pausing.");

			if (player.GetSimpleInput().num1 > 0 && 
				player.GetSimpleInput().num1 <= state.GetSettings().boardSettings.boardRows && 
				player.GetSimpleInput().num2 > 0 && 
				player.GetSimpleInput().num2 <= state.GetSettings().boardSettings.boardCols) {

				Move move = player.GetSimpleInput().ingameCmd == MarkChar ? Move::MarkBomb : Move::Reveal;
				engine.PerformMove(move,
								   player.GetSimpleInput().num1 - 1, 
								   player.GetSimpleInput().num2 - 1,
								   state.GetSettings().boardSettings,
								   state.GetSettings().uncoverType);
			}
			else if (player.GetSimpleInput().ingameCmd == QuitChar) {
				state.OpenEscapeMenu();
				state.SetStatusMessage("Write the number of you choice or Q to go back!");
				display.WritePauseMenu(InvalidIndex, state.GetStatusMessage());
				return;
			}
			else {
				state.SetStatusMessage("Status: Invalid command! \
Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
			}
		}
		else {
			state.SetStatusMessage("Status: Invalid command! \
Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
		}
	}

	display.WriteBoard(state.GetSettings().boardLook,
					   state.GetSettings().boardSettings,
					   x,
					   y,
					   engine.GetPlayerBoard(),
					   state.GetStatusMessage());

	if (engine.HasGameFinished()) {
		state.FinishGame();

		if (engine.IsWin()) {
			if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
				state.SetStatusMessage("You won! GG!\nPress Escape/Enter to continue...");
			}
			else {
				state.SetStatusMessage("You won! GG!\nWrite Q to continue...");
			}
		}
		else {
			if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
				state.SetStatusMessage("You lost! Try again!\nPress Escape/Enter to continue...");
			}
			else {
				state.SetStatusMessage("You lost! Try again!\nWrite Q to continue...");
			}
		}

		display.WriteFinishBoard(state.GetSettings().boardLook,
								 state.GetSettings().boardSettings, 
								 engine.GetPlayerBoard(),
								 engine.GetBoard(), 
								 state.GetStatusMessage());
	}
}

void Game::handleStateFinished() {
	bool isEscape = false;

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
		if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape || 
			player.GetAdvancedInput() == AdvancedPlayerInput::Select) {
			state.SetStatusMessage("Use Arrow keys / Enter / Escape(or Q) to navigate!");
			isEscape = true;
		}
		else {
			if (engine.IsWin()) {
				state.SetStatusMessage("You won! GG!\nPress Escape / Enter to continue...");
			}
			else {
				state.SetStatusMessage("You lost! Try again!\nPress Escape / Enter to continue...");
			}
		}
	}
	else {
		if (player.GetSimpleInput().isValidCmd && player.GetSimpleInput().ingameCmd == QuitChar) {
			state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
			isEscape = true;
		}
		else {
			state.SetStatusMessage("Status: Invalid command! Write Q to continue...");
		}

	}

	if (isEscape) {
		engine.FinishGame(state.GetSettings().boardSettings);
		state.OpenMainMenu();
		display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
	}
	else {
		display.WriteFinishBoard(state.GetSettings().boardLook,
								 state.GetSettings().boardSettings,
								 engine.GetPlayerBoard(),
								 engine.GetBoard(),
								 state.GetStatusMessage());
	}

}

void Game::handleStateEscapeMenu() {
	/*
	1. Resume
	2. Save and Exit
	*/
	bool isEscape = true;
	bool isExit = false;
	short x = InvalidIndex;
	short y = InvalidIndex;

	if (state.GetSettings().controlType == ControlType::AdvancedArrowInput) {
		state.SetStatusMessage("Use Arrow keys / Enter / Escape(or Q) to navigate!");
		if (player.GetAdvancedInput() == AdvancedPlayerInput::DownArrow) {
			state.IncreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
			isEscape = false;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::UpArrow) {
			state.DecreaseMenuOptionSelected(OTHER_S_MENU_OPTIONS);
			isEscape = false;
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Select) {
			switch (state.GetCurrentMenuOptionSelected())
			{
			case 1:
				state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
				break;
			case 2:
				state.SetStatusMessage("");
				isEscape = false;
				isExit = true;
				break;
			default:
				state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet.");
				isEscape = false;
				break;
			}
		}
		else if (player.GetAdvancedInput() == AdvancedPlayerInput::Escape) {
			state.SetStatusMessage("Use Arrow keys to navigate & press Enter to lock a position.");
		}
		else {
			state.SetStatusMessage("Status: Invalid command! Please use Arrow keys / Escape / Enter \
and make sure you are writing in the English alphabet. ");
			isEscape = false;
		}

		x = state.GetCurrentInGameRowIndex();
		y = state.GetCurrentInGameColIndex();
	}
	else {
		if (player.GetSimpleInput().isValidCmd) {
			if (player.GetSimpleInput().ingameCmd == QuitChar) {
				state.SetStatusMessage("Status: Invalid command! \
Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. Write Q for pausing.");
			}
			else if (player.GetSimpleInput().ingameCmd > '0' && 
				player.GetSimpleInput().ingameCmd <= OTHER_S_MENU_OPTIONS + '0') {
				switch (player.GetSimpleInput().ingameCmd)
				{
				case '1':
					state.SetStatusMessage("Write [row] [column] [cmd], where cmd is F for marking a bomb or R for revealing a position. \
Write Q for pausing.");
					break;
				case '2':
					state.SetStatusMessage("Write a number from 1 to 4 to select an option.");
					isEscape = false;
					isExit = true;
					break;
				default:
					state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
					isEscape = false;
					break;
				}
			}
		}
		else {
			state.SetStatusMessage("Status: Invalid command! Write the number of you choice or Q to go back!");
			isEscape = false;
		}
	}

	if (isEscape) {
		state.ResumeGame();
		display.WriteBoard(state.GetSettings().boardLook,
						   state.GetSettings().boardSettings,
						   x,
						   y, 
						   engine.GetPlayerBoard(), 
						   state.GetStatusMessage());
	}
	else if (isExit) {
		if (!engine.HasGameFinished()) {
			state.SaveGame(engine.GetPlayerBoard(), engine.GetBoard());
		}
		else {
			state.DeleteSavedGame();
		}
		engine.FinishGame(state.GetSettings().boardSettings);
		state.OpenMainMenu();
		display.WriteMainMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
	}
	else {
		display.WritePauseMenu(state.GetCurrentMenuOptionSelected(), state.GetStatusMessage());
	}
}

void Game::handleStateExiting() {
	state.SetStatusMessage("Thanks for playing!");
	isRunning = false;
	display.WriteExit(state.GetStatusMessage());
}