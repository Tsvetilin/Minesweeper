/**
*
* Solution to course project # 13
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Tsvetilin Tsvetilov
* @idnumber 3MI0600062
* @compiler VC
*
* File with definitons of functions related to the game cycle
*
*/

#ifndef GAME_H_
#define GAME_H_

#include "Engine.hpp"
#include "State.hpp"
#include "Display.hpp"
#include "Player.hpp"
#include <iostream>

// Main game object
struct Game {

	Game(std::istream&, std::ostream&) {
		isRunning = false;
	}

	void Run() {

		Start();

		while (IsRunning()) {
			Update();
		}

		SaveAndExit();

	}

private:
	// Initialize the game according to the settings
	void Start();		
	
	// Return current state
	bool IsRunning();	
	
	// Handle the main game cycle -> get user input, update the game state, draw the game
	void Update();		
	
	// Save current state and settings
	void SaveAndExit(); 


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
