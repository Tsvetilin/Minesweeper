#pragma once
#include "../Common.hpp"
#include "../Engine.hpp"

class Board {
	ushort rows;
	ushort cols;

	const BoardSettings* settings;

public:
	virtual Board* generateBoard(ushort rows, ushort cols);
	virtual void reveal(ushort row, ushort col) const = 0;
	virtual Board* clone() const = 0;
};