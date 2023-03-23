#include "screen.hpp"

//----------------------------------------------------------------------------------
// Base Screen Function Definitions
//----------------------------------------------------------------------------------
Screen::Screen() {}

Screen::Screen(std::shared_ptr<SoundManager> soundManager)
	: m_soundManager(soundManager)
{
	
}

Screen::Screen(
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<SoundManager> soundManager
) 	: m_textureManager(textureManager), m_soundManager(soundManager)
{

}


Screen::~Screen() {}


void Screen::UpdateScreen(float deltaTime)
{
	// Update screen
}


void Screen::DrawScreen()
{
	// Draw screen
}


//----------------------------------------------------------------------------------
// Logo Screen Function Definitions
//----------------------------------------------------------------------------------
LogoScreen::LogoScreen()
{
	m_nextScreen = 0;
	m_framesCounter = 0;
	m_lettersCount = 0;

	m_logoPositionX = GetScreenWidth() / 2 - 128;
	m_logoPositionY = GetScreenHeight() / 2 - 128;

	m_topSideRecWidth = 16;
	m_leftSideRecHeight = 16;
	m_bottomSideRecWidth = 16;
	m_rightSideRecHeight = 16;

	m_state = 0;
	m_alpha = 1.0f;
}


LogoScreen::~LogoScreen()
{

}


void LogoScreen::UpdateScreen(float deltaTime)
{
    if (m_state == 0)                 // State 0: Top-left square corner blink logic
    {
        m_framesCounter++;

        if (m_framesCounter == 80)
        {
            m_state = 1;
            m_framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (m_state == 1)            // State 1: Bars animation logic: top and left
    {
        m_topSideRecWidth += 8;
        m_leftSideRecHeight += 8;

        if (m_topSideRecWidth == 256) m_state = 2;
    }
    else if (m_state == 2)            // State 2: Bars animation logic: bottom and right
    {
        m_bottomSideRecWidth += 8;
        m_rightSideRecHeight += 8;

        if (m_bottomSideRecWidth == 256) m_state = 3;
    }
    else if (m_state == 3)            // State 3: "raylib" text-write animation logic
    {
        m_framesCounter++;

        if (m_lettersCount < 10)
        {
            if (m_framesCounter / 12)   // Every 12 frames, one more letter!
            {
                m_lettersCount++;
                m_framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (m_framesCounter > 200)
            {
                m_alpha -= 0.02f;

                if (m_alpha <= 0.0f)
                {
                    m_alpha = 0.0f;
                    m_nextScreen = 1;   // Jump to next screen
                }
            }
        }
    }
}


void LogoScreen::DrawScreen()
{
    if (m_state == 0)         // Draw blinking top-left square corner
    {
        if ((m_framesCounter / 10) % 2)
        {
            DrawRectangle(m_logoPositionX, m_logoPositionY, 16, 16, BLACK);
        }
    }
    else if (m_state == 1)    // Draw bars animation: top and left
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);
    }
    else if (m_state == 2)    // Draw bars animation: bottom and right
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);

        DrawRectangle(m_logoPositionX + 240, m_logoPositionY, 16, m_rightSideRecHeight, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY + 240, m_bottomSideRecWidth, 16, BLACK);
    }
    else if (m_state == 3)    // Draw "raylib" text-write animation + "powered by"
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, Fade(BLACK, m_alpha));
        DrawRectangle(m_logoPositionX, m_logoPositionY + 16, 16, m_leftSideRecHeight - 32, Fade(BLACK, m_alpha));

        DrawRectangle(m_logoPositionX + 240, m_logoPositionY + 16, 16, m_rightSideRecHeight - 32, Fade(BLACK, m_alpha));
        DrawRectangle(m_logoPositionX, m_logoPositionY + 240, m_bottomSideRecWidth, 16, Fade(BLACK, m_alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, m_alpha));

        DrawText(TextSubtext("raylib", 0, m_lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, m_alpha));

        if (m_framesCounter > 20) DrawText("powered by", m_logoPositionX, m_logoPositionY - 27, 20, Fade(DARKGRAY, m_alpha));
    }
}

//----------------------------------------------------------------------------------
// Options Screen Function Definitions
//----------------------------------------------------------------------------------
OptionsScreen::OptionsScreen()
{
    m_framesCounter = 0;
    m_nextScreen = 0;
}


OptionsScreen::~OptionsScreen()
{

}


void OptionsScreen::UpdateScreen()
{
    // TODO: Update OPTIONS screen variables here!
}


void OptionsScreen::DrawScreen()
{
    // TODO: Draw OPTIONS screen here!
}


//----------------------------------------------------------------------------------
// Title Screen Function Definitions
//----------------------------------------------------------------------------------
TitleScreen::TitleScreen(
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<SoundManager> soundManager
) : Screen(textureManager, soundManager)
{
	// Title 
	m_titleTexture = m_textureManager->getTexture("title");
	m_titlePos = raylib::Vector2 {
		static_cast<float>((GetScreenWidth() / 2) - (m_titleTexture.width / 2)),
		static_cast<float>((GetScreenHeight() * 0.4) - (m_titleTexture.height / 1.5))
	};

	// Player
	float playerScale {1.0f};
	m_player = AnimatedObject(m_textureManager->getTexture("cupid"), 2, 1.0f / 1.5f, -1, 1, playerScale);

	// Buttons
	float buttonOffset {1.0f};
	float buttonScale {0.8f};

	m_playButtonTexture = m_textureManager->getTexture("play_button");
	raylib::Vector2 playButtonPos = raylib::Vector2 {
		static_cast<float>(GetScreenWidth() / 2 - (m_playButtonTexture.width * buttonScale / 2)),
		static_cast<float>(GetScreenHeight() * 0.5f),
	};
	m_playButton = Button(playButtonPos, m_playButtonTexture, buttonScale);

	m_creditsButtonTexture = m_textureManager->getTexture("credits_button");
	raylib::Vector2 creditsButtonPos {
		playButtonPos.x,
		playButtonPos.y + m_playButton.getHeight() * buttonScale + buttonOffset - 15.0f,
	};
	m_creditsButton = Button(creditsButtonPos, m_creditsButtonTexture, buttonScale);

	m_quitButtonTexture = m_textureManager->getTexture("quit_button");
	raylib::Vector2 quitButtonPos {
		creditsButtonPos.x,
		creditsButtonPos.y + m_creditsButton.getHeight() * buttonScale + buttonOffset - 15.0f,
	};
	m_quitButton = Button(quitButtonPos, m_quitButtonTexture, buttonScale);
}


TitleScreen::~TitleScreen() 
{

}


void TitleScreen::UpdateScreen(float deltaTime)
{
    // Button logic
    if (m_playButton.isClicked())
    {
		m_soundManager->playSound("button_click");
        //finishScreen = 1;     // OPTIONS
        m_nextScreen = 2;     // GAMEPLAY
        return;
    }

    if (m_creditsButton.isClicked())
    {
		m_soundManager->playSound("button_click");
        m_nextScreen = 5;     // CREDITS
        return;
    }

    // Exit out of game
    if (m_quitButton.isClicked() || WindowShouldClose())
    {
		m_soundManager->playSound("button_click");
        m_nextScreen = 6;     // Exit game
        return;
    }

    m_player.update(deltaTime);
    m_playButton.update();
    m_creditsButton.update();
    m_quitButton.update();

}


void TitleScreen::DrawScreen()
{
    float deltaTime = GetFrameTime();
    raylib::Vector2 playerPos {
        static_cast<float>(GetScreenWidth() * 0.7f),
        static_cast<float>((GetScreenHeight() * 0.5f) - m_textureManager->getTexture("cupid").GetHeight())
    };
    raylib::Rectangle playerDestRec(
        playerPos.x,
        playerPos.y + sin(GetTime() * 2.0f) * 5.0f,
        static_cast<float>(m_player.getWidth() * m_player.getScale()),
        static_cast<float>(m_player.getHeight() * m_player.getScale())
    );
    m_player.draw(deltaTime, playerDestRec);
    m_titleTexture.Draw(m_titlePos, 0.0f, 1.0f, WHITE);
    // Draw buttons
    m_playButton.draw();
    m_creditsButton.draw();
    m_quitButton.draw();
}


//----------------------------------------------------------------------------------
// Gameplay Screen Function Definitions
//----------------------------------------------------------------------------------
GameplayScreen::GameplayScreen(
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<SoundManager> soundManager,
	const raylib::Font& font,
	std::shared_ptr<int> score
)	:	Screen(textureManager, soundManager), m_font(font), m_score(score),
		m_mt(static_cast<unsigned int>(time(nullptr)))
{
	// Load sounds
	m_soundManager->loadSounds(std::vector<std::string> {
		"./src/resources/sfx/arrow_whoosh.mp3",
		"./src/resources/sfx/heart_hit.wav",
		"./src/resources/sfx/firerateup_sfx.mp3",
		"./src/resources/sfx/freeze_sfx.mp3"
	});

	// Initialize player
	Vector2 startPos {0.0f, static_cast<float>(GetScreenHeight() / 2)};
	m_player = std::make_unique<Player>(
		m_textureManager->getTexture("cupid"),				// Player alive texture
		m_textureManager->getTexture("cupid_end"),			// PLayer dead texture
		m_textureManager->getTexture("arrow"),				// Arrow texture
		m_textureManager->getTexture("bow_loaded"),			// Loaded bow texture
		m_textureManager->getTexture("bow_unloaded"),			// Unloaded bow texture
		2,									// Max frames
		1.0f / 1.5f						// Update time
	);

	// Initialize powerup spawner
	m_powerupSpawner = std::make_unique<PowerUpSpawner>(m_textureManager, m_soundManager, m_player, m_targets, m_mt);

	// Initialize target spawner
	float targetSpawnRate {1.5f};								// Base spawn rate
	float minTargetSpawnRate {0.65f};							// Minimum spawn rate
	m_targetSpawner = std::make_unique<TargetSpawner>(
		targetSpawnRate,										// Base spawn rate
		minTargetSpawnRate,										// Minimum spawn rate
		m_player->getHeight() / 2,								// Min y player is able to shoot
		GetScreenHeight() - (m_player->getHeight() / 2),		// Max y player is able to shoot
		m_textureManager,										// Target textures
		m_mt													// Random num generator
	);

	// Initialize clouds
	raylib::Vector2 cloudPosition1 {
		0.0f,
		static_cast<float>(GetScreenHeight() - m_textureManager->getTexture("clouds").height / 2)
	};

	raylib::Vector2 cloudPosition2 {
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(GetScreenHeight() - m_textureManager->getTexture("clouds").height / 2)
	};
	m_clouds.push_back(Cloud(cloudPosition1, m_textureManager->getTexture("clouds")));
	m_clouds.push_back(Cloud(cloudPosition2, m_textureManager->getTexture("clouds")));
}


GameplayScreen::~GameplayScreen() 
{
	// Unload sounds
	/*for (auto& sound : m_sounds)
		sound.Unload();*/
}


void GameplayScreen::UpdateScreen(float deltaTime)
{
	if (m_gameOver)
	{
		if (m_player->isReadyForEnd())
			m_nextScreen = 1;						// Move to ending screen
	}
	else
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			std::unique_ptr<Arrow> arrowShot = m_player->shoot();
			if (arrowShot)
			{
				m_arrows.push_back(std::move(arrowShot));
				m_soundManager->playSound("arrow_whoosh");
			}
		}

		//---------------------------
		// Check collisions 
		//---------------------------

		if (m_powerup)
		{
			// Check powerup collision with player
			if (m_player->getCollisionRec().CheckCollision(m_powerup->getCollisionRec()))
			{
				m_powerup->onCollision();
				m_powerup.reset();
			}
			// Check powerup collision with left side of the screen
			else if (m_powerup->getPos().GetX() < 0)
			{
				m_powerup.reset();
			}
		}

		// Check target collision with player
		for (auto itTarget = m_targets.begin(); itTarget != m_targets.end();)
		{
			if (CheckCollisionRecs(m_player->getCollisionRec(), (*itTarget)->getCollisionRec()))
			{
				itTarget = m_targets.erase(itTarget);
				m_soundManager->playSound("heart_hit");		// Play hit sound
				m_gameOver = true;							// Set game over
				m_player->toggleAliveStatus();				// Set player dead
			}
			else
				++itTarget;
		}

		// Check for collisions of arrows and targets
		for (auto itArrow = m_arrows.begin(); itArrow != m_arrows.end();)
		{
			for (auto itTarget = m_targets.begin(); itTarget != m_targets.end();)
			{

				// Target collided with arrow
				if ((*itTarget)->areCollisionsOn() && 
					CheckCollisionRecs((*itArrow)->getCollisionRec(), (*itTarget)->getCollisionRec()))
				{
					m_soundManager->playSound("heart_hit");
					itArrow = m_arrows.erase(itArrow);
					(*itTarget)->onHit();

					// Score calculation
					if ((*itTarget)->getHealth() == 0)
					{
						(*m_score) += (*itTarget)->getScore();
						//m_sounds[1].Play();
					}

					break;
				}
				else
					++itTarget;
			}
			if (itArrow != m_arrows.end())
				++itArrow;
		}

		// Check arrow out of bounds collision
		for (auto itArrow = m_arrows.begin(); itArrow != m_arrows.end();)
		{
			if ((*itArrow)->getPos().x > GetScreenWidth())
			{
				itArrow = m_arrows.erase(itArrow);
			}
			else
				++itArrow;
		}

		// Check target out of bounds
		for (auto itTarget = m_targets.begin(); itTarget != m_targets.end();)
		{
			if ((*itTarget)->readyToDelete())
				itTarget = m_targets.erase(itTarget);
			else if ((*itTarget)->getPos().x + static_cast<float>((*itTarget)->getWidth()) < 0.0f)
				itTarget = m_targets.erase(itTarget);
			else
				++itTarget;
		}

		//------------------------
		// Update game objects 
		//------------------------

		// Update clouds
		for (auto& cloud : m_clouds)
			cloud.update(deltaTime);

		// Update arrows
		for (auto& arrow : m_arrows)
		{
			arrow->update(deltaTime);
		}

		// Update target spawner
		m_targetSpawner->update(deltaTime, m_targets);

		// Update targets
		for (auto& target : m_targets)
		{
			target->update(deltaTime);
		}

		// Update powerup spawner
		m_powerupSpawner->update(deltaTime, m_powerup);

		// Update powerup
		if (m_powerup)
			m_powerup->update(deltaTime);
	}

	// Update player here bc player might be in ending animation
	m_player->update(deltaTime);

}


void GameplayScreen::DrawScreen()
{
	for (auto& cloud : m_clouds)
		cloud.draw();

	// Draw player
	m_player->draw();

	// Draw powerup
	if (m_powerup)
		m_powerup->draw();

	// Draw arrows
	for (auto& arrow : m_arrows)
	{
		arrow->draw();
	}

	// Draw targets
	for (auto& target : m_targets)
	{
		target->draw();
	}

	// Draw score
	raylib::Text scoreText(
		m_font,
		std::to_string(*m_score),
		75.0f,
		3.0f,
		BLACK
	);

	scoreText.Draw(raylib::Vector2 {static_cast<float>((GetScreenWidth() / 2) - (scoreText.Measure() / 2)), 25});

	//---------------
	// Draw FPS counter
	//---------------
	/*raylib::Text fpsText(
		std::to_string(GetFPS()),
		20.0f,
		RED,
		GetFontDefault(),
		3.0f
	);
	fpsText.Draw(raylib::Vector2 {10.0f, 10.0f});*/
}


//----------------------------------------------------------------------------------
// Credit Screen Function Definitions
//----------------------------------------------------------------------------------
CreditsScreen::CreditsScreen(
	std::shared_ptr<SoundManager> soundManager,
	raylib::Font& font,
	raylib::Texture2DUnmanaged backButtonTexture,
	GameScreen prevScreen
) : Screen(soundManager), m_font(font), m_backButtonTexture(backButtonTexture), m_prevScreen(prevScreen)
{
	// Initialize headings and text
	float headingTextYOffset {15.0f};
	float sectionYOffset {25.0f};

	// Designer, Developer, Texture heading and text
	m_designerHeading = raylib::Text(
		m_font,
		std::string("Designer, Developer, Textures"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 designerHeadingMeasurements = m_designerHeading.MeasureEx();
	m_designerHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - designerHeadingMeasurements.x / 2),
		static_cast<float>(GetScreenHeight() * 0.1f)
	);

	m_designerText = raylib::Text(
		m_font,
		std::string("FictionalGiggle"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 designerTextMeasurements = m_designerText.MeasureEx();
	m_designerTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - designerTextMeasurements.x / 2),
		static_cast<float>(m_designerHeadingPos.y + designerHeadingMeasurements.y + headingTextYOffset)
	);

	// Fonts heading and text
	m_fontsHeading = raylib::Text(
		m_font,
		std::string("Fonts"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 fontsHeadingMeasurements = m_fontsHeading.MeasureEx();
	m_fontsHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - fontsHeadingMeasurements.x / 2),
		static_cast<float>(m_designerTextPos.y + designerTextMeasurements.y + sectionYOffset)
	);

	m_fontsText = raylib::Text(
		m_font,
		std::string("Mahima Khullar & Letter Art Studio"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 fontsTextMeasurements = m_fontsText.MeasureEx();
	m_fontsTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - fontsTextMeasurements.x / 2),
		static_cast<float>(m_fontsHeadingPos.y + fontsHeadingMeasurements.y + headingTextYOffset)
	);

	// SFX heading and text
	m_sfxHeading = raylib::Text(
		m_font,
		std::string("SFX"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 sfxHeadingMeasurements = m_sfxHeading.MeasureEx();
	m_sfxHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - sfxHeadingMeasurements.x / 2),
		static_cast<float>(m_fontsTextPos.y + fontsTextMeasurements.y + sectionYOffset)
	);

	m_sfxText = raylib::Text(
		m_font,
		std::string("DanJFilms & JuliusH"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 sfxTextMeasurements = m_sfxText.MeasureEx();
	m_sfxTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - sfxTextMeasurements.x / 2),
		static_cast<float>(m_sfxHeadingPos.y + sfxHeadingMeasurements.y + headingTextYOffset)
	);

	float buttonScale {0.8f};
	raylib::Vector2 backButtonPos {
		static_cast<float>(GetScreenWidth() / 2 - m_backButtonTexture.width * buttonScale / 2),
		static_cast<float>(GetScreenHeight() * 0.7f)
	};
	m_backButton = Button(backButtonPos, m_backButtonTexture, buttonScale);
}


CreditsScreen::~CreditsScreen() 
{

};


void CreditsScreen::UpdateScreen(float deltaTime)
{
	if (m_backButton.isClicked())
	{
		m_soundManager->playSound("button_click");
		m_nextScreen = m_prevScreen;					// Return to previous screen
	}

	m_backButton.update();
}

// Helper function to draw an "underline"
void underlineText(raylib::Text& text, raylib::Vector2& textPos)
{
	raylib::Vector2 measurements = text.MeasureEx();
	DrawLineEx(
		raylib::Vector2 {textPos.x, textPos.y + measurements.y},
		raylib::Vector2 {textPos.x + measurements.x, textPos.y + measurements.y},
		2.0f,
		BLACK
	);
}


void CreditsScreen::DrawScreen()
{
	// Draw headings and text

	m_designerHeading.Draw(m_designerHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_designerHeading, m_designerHeadingPos);
	m_designerText.Draw(m_designerTextPos, 0.0f, raylib::Vector2 {});

	m_fontsHeading.Draw(m_fontsHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_fontsHeading, m_fontsHeadingPos);
	m_fontsText.Draw(m_fontsTextPos, 0.0f, raylib::Vector2 {});

	m_sfxHeading.Draw(m_sfxHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_sfxHeading, m_sfxHeadingPos);
	m_sfxText.Draw(m_sfxTextPos, 0.0f, raylib::Vector2 {});

	m_backButton.draw();
}


//----------------------------------------------------------------------------------
// Ending Screen Function Definitions
//----------------------------------------------------------------------------------
EndingScreen::EndingScreen(
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<SoundManager> soundManager,
	const raylib::Font& font,
	std::shared_ptr<int> score
)	: Screen(textureManager, soundManager), m_font(font), m_score(score)
{
	// Initialize Player
	float playerScale {1.0f};
	m_player = AnimatedObject(m_textureManager->getTexture("cupid_end"), 2, 1.0f / 1.0f, 1, 1, playerScale);

	// Initialize buttons
	float buttonScale {0.8f};
	float buttonOffset {15.0f};

	raylib::Vector2 playAgainButtonPos {
		static_cast<float>(GetScreenWidth() / 2 - (m_textureManager->getTexture("play_again_button").width * buttonScale / 2)),
		static_cast<float>(GetScreenHeight() * 0.5f),
	};
	m_playAgainButton = Button(playAgainButtonPos, m_textureManager->getTexture("play_again_button"), buttonScale);

	raylib::Vector2 creditsButtonPos {
	   playAgainButtonPos.x,
	   playAgainButtonPos.y + m_playAgainButton.getHeight() * buttonScale - buttonOffset,
	};
	m_creditsButton = Button(creditsButtonPos, m_textureManager->getTexture("credits_button"), buttonScale);

	raylib::Vector2 quitButtonPos {
		creditsButtonPos.x,
		creditsButtonPos.y + m_creditsButton.getHeight() * buttonScale - buttonOffset,
	};
	m_quitButton = Button(quitButtonPos, m_textureManager->getTexture("quit_button"), buttonScale);
}


EndingScreen::~EndingScreen() 
{

}


void EndingScreen::UpdateScreen(float deltaTime)
{
	// Press enter or tap to change to GAMEPLAY screen
	if (m_playAgainButton.isClicked())
	{
		m_soundManager->playSound("button_click");
		//finishScreen = 1;     // OPTIONS
		m_nextScreen = 3;     // GAMEPLAY
		return;
	}

	// Show credits
	if (m_creditsButton.isClicked())
	{
		m_soundManager->playSound("button_click");
		m_nextScreen = 5;     // CREDITS
		return;
	}

	// Exit out of game
	if (m_quitButton.isClicked() || WindowShouldClose())
	{
		m_soundManager->playSound("button_click");
		m_nextScreen = 6;     // Exit game
		return;
	}

	m_player.update(deltaTime);
	m_playAgainButton.update();
	m_creditsButton.update();
	m_quitButton.update();
}


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