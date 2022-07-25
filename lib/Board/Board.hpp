#pragma once
#include "../Common/Common.hpp"
#include "BoardMarks.hpp"
#include "BoardSize.hpp"
#include "BoardOperationResult.hpp"
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
	virtual BoardOperationResult reveal(ushort row, ushort col) = 0;
	virtual BoardOperationResult markBomb(ushort row, ushort col);
	virtual Board* clone() const = 0;
	virtual ~Board() = default;

	virtual void serialize(std::ostream&) const override;
	virtual void deserialize(std::istream&) override;
};