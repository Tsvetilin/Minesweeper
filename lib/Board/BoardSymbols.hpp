#include "../Common/Common.hpp"
#include "BoardMarks.hpp"

char numbersDefault[NUMBERS_CHAR_ARRAY_SIZE]{ "12345678" };
struct BoardSymbols {

	BoardSymbols(
		char bombRevealed = 'B',
		char bombMarked = 'F',
		char uncovered = '-',
		char covered = '_',
		char* numbers = numbersDefault)
	{
		char bombRevealed = bombRevealed;
		char bombMarked = bombMarked;
		char uncovered = uncovered;
		char covered = covered;
		copyString(numbers, this->numbers, (ushort)strlen(numbersDefault));
	}

	char bombRevealed;
	char bombMarked;
	char uncovered;
	char covered;
	char numbers[NUMBERS_CHAR_ARRAY_SIZE];

	char getSymbol(BoardMark mark) {
		switch (mark) {
		case BoardMark::Bomb: return bombRevealed;
		case BoardMark::Marked: return bombMarked;
		case BoardMark::Covered: return covered;
		case BoardMark::Revealed: return uncovered;
		case BoardMark::One:return numbers[0];
		case BoardMark::Two:return numbers[1];
		case BoardMark::Three:return numbers[2];
		case BoardMark::Four:return numbers[3];
		case BoardMark::Five:return numbers[4];
		case BoardMark::Six:return numbers[5];
		case BoardMark::Seven:return numbers[6];
		case BoardMark::Eigth:return numbers[7];
		}
	}
};