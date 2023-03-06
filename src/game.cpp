#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "game.hpp"
#include "screen.hpp"
#include "logo_screen.hpp"
#include "title_screen.hpp"
#include "gameplay_screen.hpp"
#include "options_screen.hpp"
#include "ending_screen.hpp"
#include <iostream>
#include <memory>

Game::Game() {}

Game::~Game() {}

void Game::Initialize()
{
    // Initialize window
	m_window.raylib::Window::Init(m_windowWidth, m_windowHeight, m_title);
	
    // Setup and init first screen
    m_currentScreen = LOGO;
    m_screen = std::make_unique<LogoScreen>();
    m_screen->InitScreen();

    m_window.SetTargetFPS(m_targetFPS);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Load textures
    initializeTextures({
        "./src/resources/textures/cupid.png",
        "./src/resources/textures/bow_loaded.png",
        "./src/resources/textures/bow_unloaded.png",
        "./src/resources/textures/arrow.png",
        "./src/resources/textures/hearts_01.png",
        "./src/resources/textures/hearts_02.png",
        "./src/resources/textures/hearts_03.png",
        "./src/resources/textures/heart_end.png",
        "./src/resources/textures/clouds.png",
        "./src/resources/textures/cupid_end.png",
        "./src/resources/textures/title.png",
        "./src/resources/textures/play_button.png",
        "./src/resources/textures/credits_button.png",
        "./src/resources/textures/quit_button.png",
        "./src/resources/textures/restart_button.png"
    }, m_textures);

    // Load font
    m_font = raylib::Font("./src/resources/fonts/Love.ttf", 64);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);

    // Load music
    m_backgroundMusic = raylib::Music("./src/resources/sfx/music/music.mp3");
    m_backgroundMusic.SetLooping(true);

    // Load transition sounds
    m_openingTransitionSound = raylib::Sound::Sound("./src/resources/sfx/gameplay_opening_transition.mp3");
    m_endingTransitionSound = raylib::Sound::Sound("./src/resources/sfx/gameplay_ending_transition.mp3");

    m_score = std::make_shared<int>();
}

void Game::RunLoop()
{
	while (!m_window.ShouldClose())
	{
		const float dT = m_window.GetFrameTime();
		UpdateGame(dT);
		RenderGame();
	}
}

void Game::Shutdown()
{
    // Unload resources
    for (auto& [name, texture] : m_textures)
        texture.Unload();

    m_audio.Close();
    m_openingTransitionSound.Unload();
    m_endingTransitionSound.Unload();
	m_window.Close();
}

void Game::initializeTextures(
    const std::vector<std::string>& texturePaths,
    std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures
)
{
    // Load textures into GPU
    for (auto& path : texturePaths)
    {
        raylib::Texture2DUnmanaged texture(path);
        // Get name of file as key
        std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
        std::string::size_type const p(baseFilename.find_last_of('.'));
        std::string fileWithoutExtension = baseFilename.substr(0, p);
        textures[fileWithoutExtension] = texture;
    }

    // Set textures to filter_bilinear flag for better scaling
    for (auto& [name, texture] : textures)
    {
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    }
}

void Game::UpdateGame(float deltaTime)
{
    if (m_currentScreen != LOGO)
        m_backgroundMusic.Play();

    // Update music
    m_backgroundMusic.Update();

	// Update game variables
    if (m_onTransition)
    {
        UpdateTransition(); // Update transition (fade-in, fade-out)
        return;
    }

    m_screen->UpdateScreen(deltaTime);
    int nextScreen {m_screen->GetFinishScreen()};
    switch (m_currentScreen)
    {
        case LOGO:
        {
            if (nextScreen) 
                TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            if (nextScreen == 1)
            {
                m_openingTransitionSound.Play();
                TransitionToScreen(OPTIONS);
            }
            else if (nextScreen == 2)
            {
                m_openingTransitionSound.Play();
                TransitionToScreen(GAMEPLAY);
            }

        } break;
        case OPTIONS:
        {
            if (nextScreen) TransitionToScreen(TITLE);

        } break;
        case GAMEPLAY:
        {
            if (nextScreen)
            {
                m_endingTransitionSound.Play();
                TransitionToScreen(ENDING);
            }
            //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

        } break;
        case ENDING:
        {
            if (nextScreen) TransitionToScreen(TITLE);

        } break;
        default: break;
    }
    
    //----------------------------------------------------------------------------------
}

void Game::RenderGame()
{
	BeginDrawing();
		m_window.ClearBackground(RAYWHITE);
        m_screen->DrawScreen();

        // Draw full screen rectangle in front of everything
        if (m_onTransition) DrawTransition();
	EndDrawing();
}

// Change to next screen, no transition
void Game::ChangeToScreen(GameScreen screen)
{
    // Unload current screen
    m_screen->UnloadScreen();

    // Init next screen
    switch (screen)
    {
        case LOGO: 
        {
            m_screen = std::make_unique<LogoScreen>();
        } break;
        case TITLE:
        {
            m_screen = std::make_unique<TitleScreen>(m_textures);
        } break;
        case GAMEPLAY: 
        {
            m_screen = std::make_unique<GameplayScreen>(m_textures, m_font, m_score);
        } break;
        case ENDING: 
        {
            m_screen = std::make_unique<EndingScreen>(m_textures, m_font);
        } break;
        default: break;
    }
    m_screen->InitScreen();
    m_currentScreen = screen;
}

// Request transition to next screen
void Game::TransitionToScreen(GameScreen screen)
{
    m_onTransition = true;
    m_transFadeOut = false;
    m_transFromScreen = m_currentScreen;
    m_transToScreen = screen;
    m_transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
void Game::UpdateTransition(void)
{
    if (!m_transFadeOut)
    {
        m_transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (m_transAlpha > 1.01f)
        {
            m_transAlpha = 1.0f;

            // Unload current screen
            m_screen->UnloadScreen();

            // Load next screen
            switch (m_transToScreen)
            {
                case LOGO:
                {
                    m_screen = std::make_unique<LogoScreen>();
                } break;
                case TITLE:
                {
                    m_screen = std::make_unique<TitleScreen>(m_textures);
                } break;
                case GAMEPLAY:
                {
                    m_screen = std::make_unique<GameplayScreen>(m_textures, m_font, m_score);
                } break;
                case ENDING:
                {
                    m_screen = std::make_unique<EndingScreen>(m_textures, m_font);
                } break;
                default: break;
            }
            m_screen->InitScreen();

            m_currentScreen = m_transToScreen;

            // Activate fade out effect to next loaded screen
            m_transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        m_transAlpha -= 0.02f;

        if (m_transAlpha < -0.01f)
        {
            m_transAlpha = 0.0f;
            m_transFadeOut = false;
            m_onTransition = false;
            m_transFromScreen = -1;
            m_transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void Game::DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, m_transAlpha));
}