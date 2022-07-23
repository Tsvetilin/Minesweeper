#pragma once
#include "../Common/Common.hpp"
#include "BoardMarks.hpp"
#include "BoardSize.hpp"
#include "../Common/Serializable.hpp"

class Board : public Serializable{
	BoardSize size;

	bool** visitedBoard;
	BoardMark** board;
	BoardMark** playerBoard;

	bool isNumber(ushort row, ushort col);

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