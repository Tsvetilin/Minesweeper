#include "../lib/Game.hpp"

int main()
{
    Game game;

    game.Start();

    while (game.IsRunning()) {
        game.Update();
    }

    game.SaveAndExit();
}
