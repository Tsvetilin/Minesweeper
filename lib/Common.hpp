#pragma once
#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <ctime>

typedef unsigned short int ushort;

const ushort NUMBERS_CHAR_ARRAY_SIZE = 9;
const ushort SYMBOLS_CHAR_ARRAY_SIZE = 20;
const ushort COMMAND_MAX_LENGTH = 256;

const char LOWER_TO_UPPER_TRANSFORM = 'A' - 'a';

const char GAME_SETTINGS_FILE[] = "settings.minesweeper";
const char SETTINGS_TEMPLATE_FILE[] = "settingsTemplate.minesweeper.json";
const char SAVED_GAME_FILE[] = "game.minesweeper";

// Console color codes for escape codes
#define BlackFG          "30" 
#define RedFG            "31" 
#define GreenFG          "32" 
#define YellowFG         "33" 
#define BlueFG           "34" 
#define MagentaFG        "35" 
#define CyanFG           "36" 
#define WhiteFG          "37" 
#define BrightBlackFG    "90" 
#define BrightRedFG      "91" 
#define BrightGreenFG    "92" 
#define BrightYellowFG   "93" 
#define BrightBlueFG     "94" 
#define BrightMagentaFG  "95" 
#define BrightCyanFG     "96" 
#define BrightWhiteFG    "97" 
#define BlackBG             "40"
#define RedBG               "41"
#define GreenBG             "42"
#define YellowBG            "43"
#define BlueBG              "44"
#define MagentaBG           "45"
#define CyanBG              "46"
#define WhiteBG             "47"
#define BrightBlackBG      "100"
#define BrightRedBG        "101"
#define BrightGreenBG      "102"
#define BrightYellowBG     "103"
#define BrightBlueBG       "104"
#define BrightMagentaBG    "105"
#define BrightCyanBG       "106"
#define BrightWhiteBG      "107"

// Extended ascii symbols for walls
#define VLLeft (char)185
#define VerticalLine (char)186
#define URAngle (char)187
#define DRAngle (char)188
#define DLAngle (char)200
#define ULAngle (char)201
#define HLUp (char)202
#define HLDown (char)203
#define VLRight (char)204
#define HorizontalLine (char)205
#define Crossing (char)206

// Keys for ingame commands
#define QuitChar 'q'
#define RevealChar 'r'
#define MarkChar 'f'

// ASCII escape code
#define ESCAPE 27

// ASCII escape codes - Windows specific
#define KEY_UP_WIN    72
#define KEY_LEFT_WIN  75
#define KEY_RIGHT_WIN 77
#define KEY_DOWN_WIN  80
#define ARROW_SEQUENCE_WIN 224
#define ENTER_WIN 13

// ASCII escape codes - Linux specific
#define KEY_UP_LIN    65
#define KEY_LEFT_LIN  68
#define KEY_RIGHT_LIN 67
#define KEY_DOWN_LIN  66
#define ARROW_SEQUENCE_LIN 91
#define ENTER_LIN 10

// Non-existing endex to be passed as parameter
#define InvalidIndex -1

/// <summary>
/// Generates random number in range [<paramref name="lowerBound"/>;<paramref name="upperBound"/>]
/// </summary>
/// <param name="lowerBound">The lower bound of the range</param>
/// <param name="upperBound">The upper bound of the range</param>
/// <returns>Random number in the given range</returns>
ushort GenerateRandomNumber(ushort lowerBound, ushort upperBound);

/// <summary>
/// Allocates memory for a matrix with a given size
/// </summary>
/// <param name="rows">The number of rows</param>
/// <param name="cols">The number of columns</param>
/// <returns>Pointer to the start of the initialized matrix</returns>
char** initializeMatrix(ushort rows, ushort cols);

/// <summary>
/// Copies a sequance of chars from an array to another 
/// </summary>
/// <param name="source">The array to copy from</param>
/// <param name="destination">The array to copy to</param>
/// <param name="cols">The number of elements to copy from the begining</param>
void copyLine(const char* const source, char* destination, ushort cols);

/// <summary>
/// Deletes allocated memory for a matrix
/// </summary>
/// <param name="matrix">The pointer to the begining of the matrix</param>
/// <param name="rows">The number of rows in the matrix</param>
void deleteMatrix(char** matrix, ushort rows);

/// <summary>
/// Copy a string (null terminated sequence of characters)
/// </summary>
/// <param name="source">The string to copy from</param>
/// <param name="destination">The string to copy to</param>
/// <param name="cols">The length of the string</param>
void copyString(const char* const source, char* destination, ushort cols);

#endif // !COMMON_H_