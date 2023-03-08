#include "screen.hpp"
#include "ending_screen.hpp"

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

EndingScreen::EndingScreen(
    std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
    const raylib::Font& font,
    std::shared_ptr<int> score)
    : Screen(textures), m_font(font), m_score(score)
{
}

EndingScreen::~EndingScreen() {}

// Ending Screen Initialization logic
void EndingScreen::InitScreen()
{
    // Initialize Player
    float playerScale {1.0f};
    m_player = AnimatedObject(m_textures["cupid_end"], 2, 1.0f / 1.0f, 1, 1, playerScale);

    // Initialize buttons
    float buttonScale {0.8f};
    float buttonOffset {15.0f};

    raylib::Vector2 playAgainButtonPos {
        static_cast<float>(GetScreenWidth() / 2 - (m_textures["play_again_button"].width * buttonScale / 2)),
        static_cast<float>(GetScreenHeight() * 0.5f),
    };
    m_playAgainButton = Button(playAgainButtonPos, m_textures["play_again_button"], buttonScale);

    raylib::Vector2 creditsButtonPos {
       playAgainButtonPos.x,
       playAgainButtonPos.y + m_playAgainButton.getHeight() * buttonScale - buttonOffset,
    };
    m_creditsButton = Button(creditsButtonPos, m_textures["credits_button"], buttonScale);

    raylib::Vector2 quitButtonPos {
        creditsButtonPos.x,
        creditsButtonPos.y + m_creditsButton.getHeight() * buttonScale - buttonOffset,
    };
    m_quitButton = Button(quitButtonPos, m_textures["quit_button"], buttonScale);

}

// Ending Screen Update logic
void EndingScreen::UpdateScreen(float deltaTime)
{
    // Press enter or tap to change to GAMEPLAY screen
    if (m_playAgainButton.isClicked())
    {
        //finishScreen = 1;     // OPTIONS
        m_finishScreen = 3;     // GAMEPLAY
        return;
    }

    // Show credits
    if (m_creditsButton.isClicked())
    {
        m_finishScreen = 5;     // CREDITS
        return;
    }

    // Exit out of game
    if (m_quitButton.isClicked() || WindowShouldClose())
    {
        m_finishScreen = 6;     // Exit game
        return;
    }

    m_player.update(deltaTime);
    m_playAgainButton.update();
    m_creditsButton.update();
    m_quitButton.update();
}

// Ending Screen Draw logic
void EndingScreen::DrawScreen()
{
    std::string text = "You made " + std::to_string(*m_score) + " people fall in love.";
    raylib::Text finalScoreText(
        m_font,
        text,
        50.0f,
        3.0f,
        BLACK
    );
    raylib::Vector2 finalScoreTextMeasurement = finalScoreText.MeasureEx();
    raylib::Vector2 finalScoreTextPos {
        GetScreenWidth() / 2 - finalScoreTextMeasurement.GetX() / 2,
        GetScreenHeight() * 0.45f - finalScoreTextMeasurement.GetY() / 2
    };
    finalScoreText.Draw(finalScoreTextPos);

    // Draw player
    raylib::Vector2 playerPos {
        static_cast<float>((GetScreenWidth() * 0.5f) - (m_player.getWidth() * m_player.getScale() / 2)),
        static_cast<float>((GetScreenHeight() * 0.25f) - (m_player.getHeight() / 2))
    };
    raylib::Rectangle playerDestRec(
        playerPos.x,
        playerPos.y + sin(GetTime() * 2.0f) * 5.0f,
        m_player.getWidth() * m_player.getScale(),
        m_player.getHeight() * m_player.getScale()
    );
    float deltaTime = GetFrameTime();
    m_player.draw(deltaTime, playerDestRec);

    // Draw buttons
    m_playAgainButton.draw();
    m_creditsButton.draw();
    m_quitButton.draw();

}

// Ending Screen Unload logic
void EndingScreen::UnloadScreen()
{
    // TODO: Unload ENDING screen variables here!
}