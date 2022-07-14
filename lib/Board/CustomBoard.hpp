#include "Board.hpp"

class CustomBoard : public Board {
	/// <summary>
/// Reveal only the surrounding 8 cells if no number position is hit
/// </summary>
	void uncoverSurroundingEight(short row, short col, ushort rows, ushort cols, char uncovered);

};