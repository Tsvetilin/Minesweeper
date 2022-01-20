#include "../lib/Game.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
   // _CrtSetBreakAlloc(202); // 202 192 165 164
    Game game;

    game.Start();

    while (game.IsRunning()) {
        game.Update();
    }

    game.SaveAndExit();
    
    _CrtDumpMemoryLeaks();
    return 0;
}
