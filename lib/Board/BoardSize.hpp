#include "../Common/Common.hpp"

struct BoardSize {

	BoardSize(ushort rows = 9, ushort cols = 9, ushort bombs = 10) {
		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
	}

	ushort rows;
	ushort cols;
	ushort bombs;
};