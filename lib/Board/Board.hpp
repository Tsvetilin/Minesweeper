#pragma once
#include "../Common/Common.hpp"
#include "BoardMarks.hpp"
#include "BoardSize.hpp"

class Board {
	BoardSize size;

	bool** visitedBoard;
	BoardMark** board;
	BoardMark** playerBoard;

	bool isNumber(const ushort row, const ushort col, const char* const numbers);

	void copyFrom(const Board& other);
	void free();
public:
	Board(const BoardSize& size);
	Board(const Board&);
	Board& operator=(const Board&);
	virtual Board* generateBoard();
	virtual void reveal(ushort row, ushort col) = 0;
	virtual void markBomb(ushort row, ushort col);
	virtual Board* clone() const = 0;
	virtual ~Board() = default;
};

