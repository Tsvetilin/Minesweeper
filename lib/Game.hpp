#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "Engine.hpp"
#include "State.hpp"
#include "Display.hpp"
#include "Player.hpp"

struct Game {

	Game() {
		isRunning = false;
	}

public:
	void Start();		// Initialize according to settings
	bool IsRunning();	// Return true/false according to current state
	void Update();		// Get user input, update the game state, draw the game
	void SaveAndExit(); // Save current state and settings

private:
	Engine engine;
	State state;
	Display display;
	Player player;

	bool isRunning;
	void ApplySettings();
};

#endif // !GAME_H_
