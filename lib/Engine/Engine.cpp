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
 * File with implementations of functions containing the ingame logic
 *
 */

#include "Engine.hpp"
#include "Common.hpp"
#include "../Board/BoardFactory.hpp"

bool Engine::checkForWin()
{
	ushort rows = ;
	ushort cols = size->;

	ushort markedBombs = 0;
	ushort covered = 0;

	for (ushort row = 0; row < rows; ++row)
	{
		for (ushort col = 0; col < cols; ++col)
		{
			if (playerBoard[row][col] == boardSettings.covered)
			{
				++covered;
			}

			if (playerBoard[row][col] == boardSettings.bombMarked)
			{
				++markedBombs;
			}
		}
	}

	return covered + markedBombs == boardSettings.bombsCount;
}

Engine::Engine() : state(EngineState::Unknown) {}

EngineState Engine::newGame(const Settings* settings) {
	free();
	this->settings = settings;
	state = EngineState::Playing;
	this->board = BoardFactory::getBoard(settings->uncoverType, settings->size);
	return state;
}


EngineState Engine::loadGame(const Settings* settings, const Board& board) {
	free();
	this->settings = settings;
	state = EngineState::Playing;
	this->board = board.clone();
	return state;
}

EngineState Engine::performMove(Move move, ushort row, ushort col)
{
	if (Engine::state != EngineState::Playing)
	{
		return;
	}

	if (!settings->size.isValidCellIndex(row, col))
	{
		return;
	}

	BoardOperationResult result = BoardOperationResult::Unknown;

	switch (move)
	{
	case Move::None:
		result = BoardOperationResult::Unavailable;
		break;
	case Move::Reveal:
		result = board->reveal(row, col);
		break;
	case Move::MarkBomb:
		result = board->reveal(row, col);
		break;
	default:
		break;
	}

	return handleBoardResult(result);
}

EngineState Engine::finishGame() {
	free();
	state = EngineState::Unknown;
}

const Board& Engine::getBoard() {
	return *board;
}

EngineState Engine::getState() {
	return state;
}

bool Engine::hasGameFinished() {
	return state != EngineState::Playing;
}

bool Engine::isWin() {
	return state == EngineState::Win;
}

void Engine::free() {
	delete board;
	board = nullptr;
}

void Engine::copyFrom(const Engine&) {

}

Engine::Engine() : state(EngineState::Unknown), settings(nullptr), board(nullptr) {}

Engine::Engine(const Engine& other) {
	copyFrom(other);
}

Engine& Engine::operator=(const Engine& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Engine::~Engine() {
	free();
}