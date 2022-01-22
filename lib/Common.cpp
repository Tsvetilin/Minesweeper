#include "Common.hpp"

#include<string>
#include<cstring>

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


void trimTextInput(const char* const text, ushort& index) {
	while (text[index] == ' ') {
		++index;
	}
}

bool compareSequence(const char* const toCompare, const char* const compareWith) {
	ushort length = strlen(compareWith);

	for (ushort i = 0; i < length; ++i)
	{
		if (toCompare[i] != compareWith[i]) {
			return false;
		}
	}

	return true;
}

bool compareSequence(std::string toCompare, std::string compareWith) {
	ushort length = strLen(compareWith);

	for (ushort i = 0; i < length; ++i)
	{
		if (toCompare[i] != compareWith[i]) {
			return false;
		}
	}

	return true;
}

void trimText(std::string text, ushort& index) {
	while (text[index] == ' ') {
		++index;
	}
}

ushort strLen(std::string str) {
	ushort length = 0;
	while (str[length] != '\0') {
		++length;
	}

	return length;
}

bool isObjectStart(std::string str) {
	ushort index = 0;
	SkipBOM(str, index);
	trimText(str, index);
	return str[index] == '{';
}

bool isObjectEnd(std::string str) {
	ushort index = 0;
	trimText(str, index);
	return str[index] == '}';
}

bool isObjectName(std::string str, std::string name) {
	ushort index = 0;
	trimText(str, index);

	if (str[index] == '"') {
		++index;
	}
	else {
		return false;
	}

	if (compareSequence(str.c_str() + index, name)) {
		if (str[index + strLen(name)] == '"') {
			return true;
		}
	}

	return false;
}


int getIntValue(std::string str) {
	short index = str.find(":");
	if (index == -1) {
		return index;
	}
	++index;

	return atoi(str.c_str() + index);
}

std::string getStringValue(std::string str) {

	std::string result = "";

	ushort index = str.find(":");
	if (index == -1) {
		return result;
	}
	++index;

	trimText(str, index);
	if (str[index] == '"') {
		++index;
		while (str[index] != '"') {
			result += str[index];
			++index;
		}
	}

	return result;
}


bool isArrayStart(std::string str) {
	ushort index = 0;
	trimText(str, index);
	if (str[index] == '[') {
		return true;
	}

	short indexOfColumn = str.find(":");
	if (indexOfColumn > index) {
		index = indexOfColumn + 1;
		trimText(str, index);
		return str[index] == '[';
	}

	return false;
}

bool isArrayEnd(std::string str) {
	ushort index = 0;
	trimText(str, index);
	return str[index] == ']';
}


bool getIntValueWithNameCheck(std::string str, std::string name, ushort& valueResult) {
	if (isObjectName(str, name)) {
		valueResult = getIntValue(str);
		return true;
	}

	return false;
}

bool getStringtValueWithNameCheck(std::string str, std::string name, std::string& valueResult) {
	if (isObjectName(str, name)) {
		valueResult = getStringValue(str);
		return true;
	}

	return false;
}

void SkipBOM(std::string str, ushort& index)
{
	if (str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF') {
		index += 3;
	}
}