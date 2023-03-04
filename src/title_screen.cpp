#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include <iostream>

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

TitleScreen::TitleScreen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures)
    : Screen(textures)
{
    //
}

TitleScreen::~TitleScreen() {}

// Title Screen Initialization logic
void TitleScreen::InitScreen()
{
    m_title = raylib::Text("L vestruck", 100.0f, BLACK, GetFontDefault(), 5.0f);
    auto titleMeasurements = m_title.MeasureEx();
    m_titlePos = raylib::Vector2 {
        static_cast<float>((GetScreenWidth() / 2) - (titleMeasurements.GetX() / 2)),
        static_cast<float>(GetScreenHeight() / 2) - (titleMeasurements.GetY() / 2)
    };

    m_heartPos = raylib::Vector2 {
        static_cast<float>(GetScreenWidth() / 2 - m_textures["hearts_02"].GetWidth()),
        static_cast<float>(GetScreenHeight() / 2 - m_textures["hearts_02"].GetHeight())
    };
    m_heartSourceRec = raylib::Rectangle {256.0f, 0.0f, 256.0f, 256.0f};
    m_heartDestRec = raylib::Rectangle {m_heartPos.GetX(), m_heartPos.GetY(), 100.0f, 100.0f};

}

// Title Screen Update logic
void TitleScreen::UpdateScreen(float deltaTime)
{
    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        m_finishScreen = 2;   // GAMEPLAY
    }
}

// Title Screen Draw logic
void TitleScreen::DrawScreen()
{
    m_title.Draw(m_titlePos);


    m_textures["hearts_02"].Draw(m_heartSourceRec, m_heartDestRec, raylib::Vector2 {}, 0.0f, WHITE);
}

// Title Screen Unload logic
void TitleScreen::UnloadScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}