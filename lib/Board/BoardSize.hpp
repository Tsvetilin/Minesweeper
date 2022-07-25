#pragma once

#include "../Common/Common.hpp"
#include "../Common/Common.hpp"

struct BoardSize : public Serializable
{

	BoardSize(ushort rows = 9, ushort cols = 9, ushort bombs = 10)
	{
		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
	}

	ushort rows;
	ushort cols;
	ushort bombs;

	bool isValidCellIndex(ushort row, ushort col) const
	{
		return (row >= 0 && row < rows) && (col >= 0 && col < cols);
	}
};