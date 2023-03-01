#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "game.hpp"
#include <iostream>

int main()
{
    Game game;
    game.Initialize();
    game.RunLoop();
    game.Shutdown();

    return 0;
}