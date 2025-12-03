#include "Game.h"
#include <windows.h>

int main(int , char **)
{
    FreeConsole();
    Game game;
    game.Run();
    return 0;
}
