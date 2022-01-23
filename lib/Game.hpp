#ifndef GAME_H_
#define GAME_H_

#include "Engine.hpp"
#include "State.hpp"
#include "Display.hpp"
#include "Player.hpp"

// Main game object
struct Game {

	Game() {
		isRunning = false;
	}

	// Initialize the game according to the settings
	void Start();		
	
	// Return current state
	bool IsRunning();	
	
	// Handle the main game cycle -> get user input, update the game state, draw the game
	void Update();		
	
	// Save current state and settings
	void SaveAndExit(); 

private:
	Engine engine;
	State state;
	Display display;
	Player player;

	bool isRunning;

	void ApplySettings();

	void handleStateUnknown();
	void handleStateMainMenu();
	void handleStateSettingsMenu();
	void handleStateSelectSettings();
	void handleStatePlaying();
	void handleStateFinished();
	void handleStateEscapeMenu();
	void handleStateExiting();

};

#endif // !GAME_H_
