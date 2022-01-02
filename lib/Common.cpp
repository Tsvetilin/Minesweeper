#include "Common.hpp"

ushort GenerateRandomNumber(ushort lowerBound, ushort upperBound) {
    return rand() % (upperBound - lowerBound) + lowerBound;
}