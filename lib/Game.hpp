#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "Engine.hpp"
#include "State.hpp"
#include "Display.hpp"
#include "Player.hpp"

struct Game {

public:
	Engine engine;
	State state;
	Display display;
	Player player;

	void Start();		// Initialize according to settings
	bool IsRunning();	// Return true/false according to current state
	void Update();		// Get user input, update the game state, draw the game
	void SaveAndExit(); // Save current state and settings

};

#endif // !GAME_H_
