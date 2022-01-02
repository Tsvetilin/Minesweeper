#pragma once
#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <ctime>

typedef unsigned short int ushort;

const ushort NUMBERS_CHAR_ARRAY_SIZE = 9;
const ushort COMMAND_MAX_LENGTH = 100;

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


enum class Move {
    None = 0,
    Reveal = 1,
    MarkBomb = 2,
};

ushort GenerateRandomNumber(ushort lowerBound, ushort upperBound);

#endif // !COMMON_H_