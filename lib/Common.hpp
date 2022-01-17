#pragma once
#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <ctime>

typedef unsigned short int ushort;

const ushort NUMBERS_CHAR_ARRAY_SIZE = 9;
const ushort COMMAND_MAX_LENGTH = 100;

const char GAME_SETTINGS_FILE[] = "settings.minesweeper";
const char SETTINGS_TEMPLATE_FILE[] = "settingsTemplate.minesweeper.json";
const char SAVED_GAME_FILE[] = "game.minesweeper";

// ANSII Support Required
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


enum class Move {
    None = 0,
    Reveal = 1,
    MarkBomb = 2,
};

ushort GenerateRandomNumber(ushort lowerBound, ushort upperBound);
void initializeMatrix(char** &matrix, ushort rows, ushort cols);
void copyLine(const char const* source, char* &destination, ushort cols);
void deleteMatrix(char** &matrix, ushort rows);

#endif // !COMMON_H_