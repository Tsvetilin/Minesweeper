/**
*
* Solution to course project # 13
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Tsvetilin Tsvetilov
* @idnumber 3MI0600062
* @compiler VC
*
* Program entry point
*
*/

#include "../lib/Game.hpp"

int main()
{
    Game game(std::cin, std::cout);
    game.Run();

    return 0;   
}

/* Visual Studio Memory leak test:
* 
*#define _CRTDBG_MAP_ALLOC
*#include <stdlib.h>
*#include <crtdbg.h>
*
* _CrtSetBreakAlloc(n); -> breakpoint on the n-th memory allocation
* _CrtMemState s1; -> curent state at the beggining
* 
* _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); ->
* _CrtMemCheckpoint(&s1);  -> get new data
* _CrtMemDumpStatistics(&s1);
* _CrtDumpMemoryLeaks(); -> print the results in the standart output window
* 
*/

