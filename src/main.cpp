/*******************************************************************************************
*
*   Lovestruck
*   
*   Valentine's Day is Cupid's day to shine. Help Cupid make as many people fall in love
*   before he is struck by love himself.
* 
*   A game by FictionalGiggle
*   https://fictionalgiggle.itch.io/
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "screen.hpp"
#include "game.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int main()
{
    Game game;
    game.Initialize();
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(game.RunLoop, 60, 1);
#else
    game.RunLoop();
#endif
    
    game.Shutdown();
    return 0;
}