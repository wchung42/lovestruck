#include "game.hpp"
#include "screen.hpp"
#include "sound_manager.hpp"
#include "utils.hpp"
#include <memory>

Game::Game() {}

Game::~Game() {}

void Game::Initialize()
{
    // Initialize window
	m_window.raylib::Window::Init(m_windowWidth, m_windowHeight, m_title);
    SetExitKey(0);

    // Setup first screen
    m_currentScreen = LOGO;
    m_screen = std::make_unique<LogoScreen>();

    m_window.SetTargetFPS(m_targetFPS);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Load textures
    utils::initializeTextures({
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
        "./src/resources/textures/play_again_button.png",
        "./src/resources/textures/back_button.png",
        "./src/resources/textures/firerate_powerup.png",
        "./src/resources/textures/freeze_powerup.png"
    }, m_textures);

    // Load font
    m_font = raylib::Font("./src/resources/fonts/SimpleHandmade.ttf", 64);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);

    // Load sounds
    m_soundManager = std::make_shared<SoundManager>();
    //m_backgroundMusic = raylib::Music("./src/resources/sfx/music/music.mp3");
    m_soundManager->loadMusic("./src/resources/sfx/music/music.mp3");
    //m_backgroundMusic.SetLooping(true);
    m_soundManager->setMusicLooping("music");

    // Load transition sounds
    //m_openingTransitionSound = raylib::Sound("./src/resources/sfx/gameplay_opening_transition.mp3");
    //m_endingTransitionSound = raylib::Sound("./src/resources/sfx/gameplay_ending_transition.mp3");
    m_soundManager->loadSounds(std::vector<std::string> {
        "./src/resources/sfx/gameplay_opening_transition.mp3",
        "./src/resources/sfx/gameplay_ending_transition.mp3",
        "./src/resources/sfx/button_click.mp3"
    });

    m_score = std::make_shared<int>();
}

void Game::RunLoop()
{
	while (!m_exitGame)
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

    //m_openingTransitionSound.Unload();
    //m_endingTransitionSound.Unload();
	m_window.Close();
}

void Game::UpdateGame(float deltaTime)
{
    if (WindowShouldClose())
    {
        m_exitGame = true;
        return;
    }

    if (m_currentScreen != LOGO)
        //m_backgroundMusic.Play();
        m_soundManager->playMusic("music");

    // Update music
    //m_backgroundMusic.Update();
    m_soundManager->updateMusic("music");

	// Update game variables
    if (m_onTransition)
    {
        UpdateTransition(); // Update transition (fade-in, fade-out)
        return;
    }

    m_screen->UpdateScreen(deltaTime);
    int nextScreen {m_screen->getNextScreen()};
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
                //m_openingTransitionSound.Play();
                m_soundManager->playSound("gameplay_opening_transition");
                TransitionToScreen(OPTIONS);
            }
            else if (nextScreen == 2)
            {
                //m_openingTransitionSound.Play();
                m_soundManager->playSound("gameplay_opening_transition");
                TransitionToScreen(GAMEPLAY);
            }
            else if (nextScreen == 5)
            {
                //m_openingTransitionSound.Play();
                m_soundManager->playSound("gameplay_opening_transition");
                TransitionToScreen(CREDITS);
            }
            else if (nextScreen == 6)
            {
                m_exitGame = true;
                return;
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
                //m_endingTransitionSound.Play();
                m_soundManager->playSound("gameplay_ending_transition");
                TransitionToScreen(ENDING);
            }
            //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

        } break;
        case CREDITS:
        {
            if (nextScreen == 1)                    // Go back to TITLE screen if it was previous
            {
                //m_endingTransitionSound.Play();
                m_soundManager->playSound("gameplay_ending_transition");
                TransitionToScreen(TITLE);
            }
            else if (nextScreen == 4)               // Go back to ENDING screen if it was previous
            {
                //m_endingTransitionSound.Play();
                m_soundManager->playSound("gameplay_ending_transition");
                TransitionToScreen(ENDING);
            }
        } break;
        case ENDING:
        {
            if (nextScreen == 3)
            {   
                //m_openingTransitionSound.Play();
                m_soundManager->playSound("gameplay_opening_transition");
                TransitionToScreen(GAMEPLAY);
            }
            else if (nextScreen == 5)
            {
                //m_openingTransitionSound.Play();
                m_soundManager->playSound("gameplay_opening_transition");
                TransitionToScreen(CREDITS);
            }
            else if (nextScreen == 6)
            {
                m_exitGame = true;
                return;
            }
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
    // Save previous screen
    m_prevScreen = m_currentScreen;

    // Init next screen
    switch (screen)
    {
        case LOGO: 
        {
            m_screen = std::make_unique<LogoScreen>();
        } break;
        case TITLE:
        {
            m_screen = std::make_unique<TitleScreen>(m_textures, m_soundManager);
        } break;
        case GAMEPLAY: 
        {
            *m_score = 0;
            m_screen = std::make_unique<GameplayScreen>(m_textures, m_soundManager, m_font, m_score);
        } break;
        case CREDITS:
        {
            m_screen = std::make_unique<CreditsScreen>(m_soundManager, m_font, m_textures["back_button"], m_prevScreen);
        } break;
        case ENDING: 
        {
            m_screen = std::make_unique<EndingScreen>(m_textures, m_soundManager, m_font, m_score);
        } break;
        default: break;
    }
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
void Game::UpdateTransition()
{
    if (!m_transFadeOut)
    {
        m_transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (m_transAlpha > 1.01f)
        {
            m_transAlpha = 1.0f;

            // Save previous screen
            m_prevScreen = m_currentScreen;

            // Load next screen
            switch (m_transToScreen)
            {
                case LOGO:
                {
                    m_screen = std::make_unique<LogoScreen>();
                } break;
                case TITLE:
                {
                    m_screen = std::make_unique<TitleScreen>(m_textures, m_soundManager);
                } break;
                case GAMEPLAY:
                {
                    *m_score = 0;
                    m_screen = std::make_unique<GameplayScreen>(m_textures, m_soundManager, m_font, m_score);
                } break;
                case CREDITS:
                {
                    m_screen = std::make_unique<CreditsScreen>(m_soundManager, m_font, m_textures["back_button"], m_prevScreen);
                } break;
                case ENDING:
                {
                    m_screen = std::make_unique<EndingScreen>(m_textures, m_soundManager, m_font, m_score);
                } break;
                default: break;
            }

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