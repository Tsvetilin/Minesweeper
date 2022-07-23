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

#pragma once

#include "../lib/Common/App.hpp"
#include "../lib/Engine/Engine.hpp"
#include "../lib/State/State.hpp"
#include "../lib/Display/Display.hpp"
#include "../lib/Input/Player.hpp"

#include <iostream>

// Main game object
class Game : public App
{

public:
	Game(std::istream &is, std::ostream &os) : App(is, os), isOperating(false) {}

	void run()
	{

		start();

		while (isRunning())
		{
			update();
		}

		saveAndExit();
	}

private:
	// Initialize the game according to the settings
	void start();

	// Return current state
	bool isRunning();

	// Handle the main game cycle -> get user input, update the game state, draw the game
	void update();

	// Save current state and settings
	void saveAndExit();

	Engine engine;
	State state;
	Display display;
	Player player;

	bool isOperating;

	void applySettings();

	void handleStateUnknown();
	void handleStateMainMenu();
	void handleStateSettingsMenu();
	void handleStateSelectSettings();
	void handleStatePlaying();
	void handleStateFinished();
	void handleStateEscapeMenu();
	void handleStateExiting();
};