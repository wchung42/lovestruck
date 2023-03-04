#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "ending_screen.hpp"

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

EndingScreen::EndingScreen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures)
    : Screen(textures)
{
}

EndingScreen::~EndingScreen() {}

// Ending Screen Initialization logic
void EndingScreen::InitScreen()
{
    // TODO: Initialize ENDING screen variables here!
    m_framesCounter = 0;
    m_finishScreen = 0;
}

// Ending Screen Update logic
void EndingScreen::UpdateScreen(float deltaTime)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        m_finishScreen = 1;
        //PlaySound(fxCoin);
    }
}

// Ending Screen Draw logic
void EndingScreen::DrawScreen()
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    raylib::Vector2 titlePosition {20, 10};
    raylib::DrawText("ENDING SCREEN", titlePosition.GetX(), titlePosition.GetY(), 20, DARKBLUE);
    raylib::Vector2 instructionPosition {120, 220};
    raylib::DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", instructionPosition.GetX(), instructionPosition.GetY(), 30, DARKBLUE);
}

// Ending Screen Unload logic
void EndingScreen::UnloadScreen()
{
    // TODO: Unload ENDING screen variables here!
}