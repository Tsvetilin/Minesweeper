#pragma once

#include "Board.hpp"

class StandartBoard : public Board {
	/// <summary>
	/// Recursively reveal all surrounding cells until reaching a number
	/// </summary>
	void revealToNumber(const short row,
		const short col,
		const ushort rows,
		const ushort cols,
		const char uncovered,
		const char covered,
		const char* const numbers);
public:


};