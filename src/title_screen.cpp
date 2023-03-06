#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include "animated_object.hpp"
#include <iostream>

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

TitleScreen::TitleScreen(
    std::unordered_map<std::string,
    raylib::Texture2DUnmanaged> textures,
    raylib::Font& font
)
    : Screen(textures)
{
    //
}

TitleScreen::~TitleScreen() {}

// Title Screen Initialization logic
void TitleScreen::InitScreen()
{
    // Title 
    m_titleTexture = m_textures["title"];
    m_titlePos = raylib::Vector2 {
        static_cast<float>((GetScreenWidth() / 2) - (m_titleTexture.width / 2)),
        static_cast<float>((GetScreenHeight() * 0.4) - (m_titleTexture.height / 1.5))
    };

    // Player
    m_playerPos = raylib::Vector2 {
        static_cast<float>(GetScreenWidth() * 0.7f),
        static_cast<float>((GetScreenHeight() / 2) - m_textures["cupid"].GetHeight())
    };
    m_player = AnimatedObject (m_playerPos, m_textures["cupid"], 2, 1.0f / 1.5f);

    // Buttons
    float buttonOffset {1.0f};
    float buttonScale {0.8f};

    m_playButtonTexture = m_textures["play_button"];
    raylib::Vector2 playButtonPos = raylib::Vector2 {
        static_cast<float>(GetScreenWidth() / 2 - (m_playButtonTexture.width * buttonScale / 2)),
        static_cast<float>(GetScreenHeight() * 0.5f),
    };
    m_playButton = Button(playButtonPos, m_playButtonTexture, buttonScale);

    m_creditsButtonTexture = m_textures["credits_button"];
    raylib::Vector2 creditsButtonPos {
       playButtonPos.x,
       playButtonPos.y + m_playButton.getHeight() * buttonScale + buttonOffset - 15.0f,
    };
    m_creditsButton = Button(creditsButtonPos, m_creditsButtonTexture, buttonScale);

    m_quitButtonTexture = m_textures["quit_button"];
    raylib::Vector2 quitButtonPos {
        creditsButtonPos.x,
        creditsButtonPos.y + m_creditsButton.getHeight() * buttonScale + buttonOffset - 15.0f,
    };
    m_quitButton = Button(quitButtonPos, m_quitButtonTexture, buttonScale);
}

// Title Screen Update logic
void TitleScreen::UpdateScreen(float deltaTime)
{
    // Press enter or tap to change to GAMEPLAY screen
    if (m_playButton.isClicked())
    {
        //finishScreen = 1;   // OPTIONS
        m_finishScreen = 2;   // GAMEPLAY
    }

    m_player.update(deltaTime);
    m_playButton.update();
    m_creditsButton.update();
    m_quitButton.update();

}

// Title Screen Draw logic
void TitleScreen::DrawScreen()
{
    float deltaTime = GetFrameTime();
    m_player.draw(deltaTime);
    m_titleTexture.Draw(m_titlePos, 0.0f, 1.0f, WHITE);
    // Draw buttons
    m_playButton.draw();
    m_creditsButton.draw();
    m_quitButton.draw();

    /*DrawLineEx(
        Vector2 {static_cast<float>(GetScreenWidth()) / 2, 0.0f},
        Vector2 {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight())},
        1.0f,
        BLACK
    );*/

}

// Title Screen Unload logic
void TitleScreen::UnloadScreen(void)
{

}