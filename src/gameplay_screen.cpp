#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include "gameplay_screen.hpp"
#include "cloud.hpp"

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

GameplayScreen::GameplayScreen(
	std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
	const raylib::Font& font,
	std::shared_ptr<int> score)	
	: Screen(textures), m_font(font), m_score(score)
{

}

GameplayScreen::~GameplayScreen() {}

// Gameplay Screen Initialization logic
void GameplayScreen::InitScreen()
{
	// Load sounds
	initializeSounds({
		"./src/resources/sfx/arrow_whoosh.mp3",
		"./src/resources/sfx/heart_hit.wav"
	}, m_sounds);

    // Initialize player
    Vector2 startPos {0.0f, static_cast<float>(GetScreenHeight() / 2)};
    m_player = std::make_unique<Player>(
        m_textures["cupid"],				// Player alive texture
		m_textures["cupid_end"],			// PLayer dead texture
        m_textures["arrow"],				// Arrow texture
		m_textures["bow_loaded"],			// Loaded bow texture
		m_textures["bow_unloaded"],			// Unloaded bow texture
        2,									// Max frames
        1.0f / 1.5f							// Update time
    );

    // Initialize arrows vector
    m_arrows = std::make_unique<std::vector<std::shared_ptr<Arrow>>>();
	
	// Initialize target spawner
    float targetSpawnRate {1.5f};								// Base spawn rate
	float minTargetSpawnRate {0.65f};							// Minimum spawn rate
    std::vector<raylib::Texture2DUnmanaged> heartTextures {
		m_textures["hearts_01"],
		m_textures["hearts_02"],
		m_textures["hearts_03"],
		m_textures["heart_end"]
	};
    m_spawner = std::make_unique<TargetSpawner>(
        targetSpawnRate,									// Base spawn rate
		minTargetSpawnRate,									// Minimum spawn rate
        m_player->getHeight() / 2,							// Min y player is able to shoot
        GetScreenHeight() - (m_player->getHeight() / 2),	// Max y player is able to shoot
        heartTextures										// Target textures
    );
    // Initialize targets vector
    m_targets = std::make_unique<std::vector<std::unique_ptr<Target>>>();
	
	raylib::Vector2 cloudPosition1 {
		0.0f,
		static_cast<float>(GetScreenHeight() - m_textures["clouds"].height / 2)
	};
	
	raylib::Vector2 cloudPosition2 {
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(GetScreenHeight() - m_textures["clouds"].height / 2)
	};
	m_clouds.push_back(Cloud(cloudPosition1, m_textures["clouds"]));
	m_clouds.push_back(Cloud(cloudPosition2, m_textures["clouds"]));

}

// Gameplay Screen Update logic
void GameplayScreen::UpdateScreen(float deltaTime)
{
	if (m_gameOver)
	{
		if (m_player->isReadyForEnd())
			m_finishScreen = 1;						// Move to ending screen
	}
	else
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			std::shared_ptr<Arrow> arrowShot = m_player->shoot();
			if (arrowShot)
			{
				m_arrows->push_back(arrowShot);
				m_sounds[0].Play();
			}
		}

		//////////////////////////
		/* Check for collisions */
		//////////////////////////

		// Check target collision with player
		for (auto itTarget = m_targets->begin(); itTarget != m_targets->end();)
		{
			if (CheckCollisionRecs(m_player->getCollisionRec(), (*itTarget)->getCollisionRec()))
			{
				itTarget = m_targets->erase(itTarget);
				m_sounds[1].Play();						// Play hit sound
				m_gameOver = true;						// Set game over
				m_player->toggleAliveStatus();			// Set player dead
			}
			else
				++itTarget;
		}

		// Check for collisions of arrows and targets
		for (auto itArrow = m_arrows->begin(); itArrow != m_arrows->end();)
		{
			for (auto itTarget = m_targets->begin(); itTarget != m_targets->end();)
			{

				// Target collided with arrow
				if ((*itTarget)->getCollisionsOn() && CheckCollisionRecs((*itArrow)->getCollisionRec(), (*itTarget)->getCollisionRec()))
				{
					m_sounds[1].Play();
					itArrow = m_arrows->erase(itArrow);
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
			if (itArrow != m_arrows->end())
				++itArrow;
		}

		// Check arrow out of bounds collision
		for (auto itArrow = m_arrows->begin(); itArrow != m_arrows->end();)
		{
			if ((*itArrow)->getPos().x > GetScreenWidth())
			{
				itArrow = m_arrows->erase(itArrow);
			}
			else
				++itArrow;
		}

		// Check target out of bounds
		for (auto itTarget = m_targets->begin(); itTarget != m_targets->end();)
		{
			if ((*itTarget)->readyToDelete())
				itTarget = m_targets->erase(itTarget);
			else if ((*itTarget)->getPos().x + static_cast<float>((*itTarget)->getWidth()) < 0.0f)
				itTarget = m_targets->erase(itTarget);
			else
				++itTarget;
		}

		/////////////////////////
		/* Update game objects */
		/////////////////////////

		// Update clouds
		for (auto& cloud : m_clouds)
			cloud.update(deltaTime);

		// Update arrows
		for (auto& arrow : *m_arrows)
		{
			arrow->update(deltaTime);
		}

		// Update target spawner
		m_spawner->update(deltaTime, m_targets);

		// Update targets
		for (auto& target : *m_targets)
		{
			target->update(deltaTime);
		}
	}

	// Update player
	m_player->update(deltaTime);
	
}

// Gameplay Screen Draw logic
void GameplayScreen::DrawScreen()
{
	for (auto& cloud : m_clouds)
		cloud.draw();

	// Draw player
	m_player->draw();

	// Draw arrows
	for (auto& arrow : *m_arrows)
	{
		arrow->draw();
	}

	// Draw targets
	for (auto& target : *m_targets)
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

	/*raylib::Text scoreText(
		std::to_string(*m_score),
		75.0f,
		BLACK,
		GetFontDefault(),
		3.0f
	);*/
	scoreText.Draw(raylib::Vector2 {static_cast<float>((GetScreenWidth() / 2) - (scoreText.Measure() / 2)), 25});

	// FPS counter
	/*raylib::Text fpsText(
		std::to_string(GetFPS()),
		20.0f,
		RED,
		GetFontDefault(),
		3.0f
	);
	fpsText.Draw(raylib::Vector2 {10.0f, 10.0f});*/
}

// Gameplay Screen Unload logic
void GameplayScreen::UnloadScreen()
{
	// Unload sounds
	for (auto& sound : m_sounds)
		sound.Unload();

}