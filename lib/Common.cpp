#include "Common.hpp"

ushort GenerateRandomNumber(ushort lowerBound, ushort upperBound) {
	return rand() % (upperBound - lowerBound) + lowerBound;
}

char** initializeMatrix(ushort rows, ushort cols) {
	char** matrix = new char* [rows];
	for (ushort i = 0; i < rows; ++i)
	{
		matrix[i] = new char[cols];
	}

	return matrix;
}

void deleteMatrix(char** matrix, ushort rows) {
	for (ushort i = 0; i < rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void copyLine(const char* const source, char* destination, ushort cols) {
	for (ushort i = 0; i < cols; ++i)
	{
		destination[i] = source[i];
	}
}

void copyString(const char* const source, char* destination, ushort cols) {
	copyLine(source, destination, cols);
	destination[cols] = '\0';
}