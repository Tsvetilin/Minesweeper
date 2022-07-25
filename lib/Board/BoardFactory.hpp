#pragma once

#include "BoardSize.hpp"
#include "Board.hpp"

class BoardFactory{

public:
    static Board* getBoard(UncoverType uncoverType, const BoardSize&);
};