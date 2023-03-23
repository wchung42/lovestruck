#include "powerup.hpp"

// Base power up function definitions
PowerUp::PowerUp()
{

}

PowerUp::PowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos,
	std::shared_ptr<SoundManager> soundManager
) : m_texture(texture), m_pos(pos), m_soundManager(soundManager)
{
	m_scale = 0.25f;
	m_width = m_texture.GetWidth() * m_scale;
	m_height = m_texture.GetHeight() * m_scale;
}

PowerUp::~PowerUp()
{

}

void PowerUp::update(float deltaTime)
{
	m_pos.x -= m_velocity * deltaTime;
}

void PowerUp::draw()
{
	m_texture.Draw(m_pos, 0.0f, m_scale, WHITE);
	//getCollisionRec().DrawLines(RED);
}

void PowerUp::onCollision()
{

}

raylib::Rectangle PowerUp::getCollisionRec()
{
	raylib::Rectangle rec {
		m_pos.GetX() + 10,
		m_pos.GetY() + 10,
		static_cast<float>(m_width) - 20,
		static_cast<float>(m_height) - 20
	};
	return rec;
}


// Speed power up function definitions
FireRatePowerUp::FireRatePowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos,
	std::unique_ptr<Player>& player,
	std::shared_ptr<SoundManager> soundManager
) : PowerUp(texture, pos, soundManager), m_player(player)
{

}

FireRatePowerUp::~FireRatePowerUp()
{

}

void FireRatePowerUp::onCollision()
{
	// Play fire rate powerup sound
	m_soundManager->playSound("firerateup_sfx");

	// Increase player fire rate by 0.01 if fire rate is >= 0.1
	if (m_player->getFireRate() > 0.1f)
		m_player->setFireRate(m_player->getFireRate() - 0.015f);
}


// Freeze power up function deinitions
FreezePowerUp::FreezePowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos,
	std::vector<std::unique_ptr<Target>>& targets,
	std::shared_ptr<SoundManager> soundManager
) : PowerUp(texture, pos, soundManager), m_targets(targets)
{

}

FreezePowerUp::~FreezePowerUp()
{

}

void FreezePowerUp::onCollision()
{
	// Play freeze powerup sound
	m_soundManager->playSound("freeze_sfx");

	// zero all target velocities on screen
	for (auto& target : m_targets)
	{
		target->setVelocity(0.0f);
	}
}


// Powerup spawner function declarations
PowerUpSpawner::PowerUpSpawner(
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<SoundManager> soundManager,
	std::unique_ptr<Player>& player,
	std::vector<std::unique_ptr<Target>>& targets,
	std::shared_ptr<std::mt19937> mt
) : m_textureManager(textureManager), m_soundManager(soundManager),
	m_player(player), m_targets(targets), m_mt(mt)
{
	m_spawnRate = 8.0f;		// Spawn powerup every 8 seconds
}

PowerUpSpawner::~PowerUpSpawner()
{

}

void PowerUpSpawner::update(float deltaTime, std::unique_ptr<PowerUp>& powerup)
{
	m_spawnTimer += deltaTime;
	if (m_spawnTimer >= m_spawnRate)
	{
		if (!powerup)	
		{
			powerup = std::move(spawnPowerUp());
		}
		m_spawnTimer = 0.0f;
	}
}

std::unique_ptr<PowerUp> PowerUpSpawner::spawnPowerUp()
{

	// Select power up to spawn
	std::uniform_int_distribution<int> powerUpDist(0, 100);
	int powerUpToSpawn {powerUpDist(*m_mt)};

	// Get random spawn position
	std::uniform_int_distribution<int> spawnPosYDist(GetScreenHeight() * 0.2f, GetScreenHeight() * 0.8f);
	int spawnYPos {spawnPosYDist(*m_mt)};
	raylib::Vector2 spawnPos {
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(spawnYPos)
	};

	std::unique_ptr<PowerUp> powerup;
	if (powerUpToSpawn < 69)
	{
		powerup = std::make_unique<FireRatePowerUp>(m_textureManager->getTexture("firerate_powerup"), spawnPos, m_player, m_soundManager);
	}
	else if (powerUpToSpawn >= 70)
	{
		powerup = std::make_unique<FreezePowerUp>(m_textureManager->getTexture("freeze_powerup"), spawnPos, m_targets, m_soundManager);
	}

	return powerup;
}