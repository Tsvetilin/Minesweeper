#include "../lib/Game.hpp"

int main()
{
    Game game;

    game.Start();

    while (game.IsRunning()) {
        game.Update();
    }

    game.SaveAndExit();

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

