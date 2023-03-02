#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "gameplay_screen.hpp"
#include "cloud.hpp"
#include <iostream>

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void GameplayScreen::InitScreen()
{
    // Load resources
    initializeTextures({
        "./src/resources/textures/cupid_spritesheet.png",
        "./src/resources/textures/cupid_bow_loaded.png",
        "./src/resources/textures/cupid_bow_unloaded.png",
        "./src/resources/textures/cupid_arrow.png",
		"./src/resources/textures/hearts_spritesheet_01.png",
		"./src/resources/textures/hearts_spritesheet_02.png",
		"./src/resources/textures/hearts_spritesheet_03.png",
		"./src/resources/textures/heart_ending.png",
		"./src/resources/textures/cloud_full.png"
    }, m_textures);

	// TODO: Load music
	// TODO: Load font

    // Initialize player
    Vector2 startPos {0.0f, static_cast<float>(GetScreenHeight() / 2)};
    m_player = std::make_unique<Player>(
        m_textures[0],	// Player texture
        m_textures[3],	// Arrow texture
		m_textures[1],	// Loaded bow texture
		m_textures[2],	// Unloaded bow texture
        2,				// Max frames
        1.0f / 2.0f		// Update time
    );

    // Initialize arrows vector
    m_arrows = std::make_unique<std::vector<std::shared_ptr<Arrow>>>();

    // TODO: Increase spawnRate as game progresses
    float targetSpawnRate {2.0f};
    std::vector<raylib::Texture2DUnmanaged> heartTextures {
		m_textures[4],
		m_textures[5],
		m_textures[6],
		m_textures[7]
	};
    m_spawner = std::make_unique<TargetSpawner>(
        targetSpawnRate,									// Spawn rate
        m_player->getHeight() / 2,							// Min y player is able to shoot
        GetScreenHeight() - (m_player->getHeight() / 2),	// Max y player is able to shoot
        heartTextures										// Target textures
    );
    // Initialize targets vector
    m_targets = std::make_unique<std::vector<std::shared_ptr<Target>>>();

	// Initialize clouds vector
	//m_clouds = std::make_unique<std::vector<std::unique_ptr<Cloud>>>();
	// Initialize clouds
	/*std::vector<raylib::Vector2> cloudPositions;
	for (int xPos {0}; xPos < GetScreenWidth(); xPos += 256)
	{
		cloudPositions.push_back(raylib::Vector2 {static_cast<float>(xPos), static_cast<float>(GetScreenHeight() - 100)});
	}*/
	
	
	/*for (auto& position : cloudPositions)
	{
		std::unique_ptr<Cloud> cloud = std::make_unique<Cloud>(position, m_textures[8]);
		m_clouds->push_back(std::move(cloud));
	}*/
	
	raylib::Vector2 cloudPosition1 {
		0.0f,
		static_cast<float>(GetScreenHeight() - m_textures[8].height / 2)
	};
	
	raylib::Vector2 cloudPosition2 {
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(GetScreenHeight() - m_textures[8].height / 2)
	};
	/*m_clouds->push_back(std::move(std::make_unique<Cloud>(cloudPosition1, m_textures[8])));
	m_clouds->push_back(std::move(std::make_unique<Cloud>(cloudPosition2, m_textures[8])));*/
	m_clouds.push_back(Cloud(cloudPosition1, m_textures[8]));
	m_clouds.push_back(Cloud(cloudPosition2, m_textures[8]));
}

// Gameplay Screen Update logic
void GameplayScreen::UpdateScreen(float deltaTime)
{
	/*for (auto itCloud = m_clouds->begin(); itCloud != m_clouds->end();)
	{
		if ((*itCloud)->getPos().x + (*itCloud)->getWidth() < 0)
			(*itCloud)->set
		else
			++itCloud;
	}*/

	if (IsKeyPressed(KEY_SPACE))
	{
		std::shared_ptr<Arrow> arrowShot = m_player->shoot();
		if (arrowShot)
			m_arrows->push_back(arrowShot);
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
			m_finishScreen = 1;						// Move to ending screen
			std::cout << "Game over" << std::endl;
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
				itArrow = m_arrows->erase(itArrow);
				(*itTarget)->onHit();

				// Score calculation
				if ((*itTarget)->getHealth() == 0)
					m_score += (*itTarget)->getScore();

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

	// Update player
	m_player->update(deltaTime);

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
		std::to_string(m_score),
		75.0f,
		BLACK,
		GetFontDefault(),
		3.0f
	);
	scoreText.Draw(raylib::Vector2 {static_cast<float>((GetScreenWidth() / 2) - (scoreText.Measure() / 2)), 25});
}

// Gameplay Screen Unload logic
void GameplayScreen::UnloadScreen()
{
    // Unload textures
	for (auto& texture : m_textures)
	{
		texture.Unload();
	}
}