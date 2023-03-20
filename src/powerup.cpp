#include "powerup.hpp"

// Base power up function definitions
PowerUp::PowerUp()
{

}

PowerUp::PowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos
) : m_texture(texture), m_pos(pos)
{
	m_scale = 0.5f;
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
}

raylib::Rectangle PowerUp::getCollisionRec()
{
	raylib::Rectangle rec {
		m_pos.GetX(),
		m_pos.GetY(),
		static_cast<float>(m_width),
		static_cast<float>(m_height)
	};
	return rec;
}


// Speed power up function definitions
FireRatePowerUp::FireRatePowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos
) : PowerUp(texture, pos)
{

}

FireRatePowerUp::~FireRatePowerUp()
{

}

void FireRatePowerUp::onCollision(
	std::unique_ptr<Player>& player,
	std::unordered_map<std::string, Sound>& sounds)
{
	PlaySound(sounds["speed_up"]);
	// Increase player fire rate by 0.1 if fire rate is >= 0.1
	if (player->getFireRate() > 0.1f)
		player->setFireRate(player->getFireRate() - 0.1f);
}


// Freeze power up function deinitions
FreezePowerUp::FreezePowerUp(
	raylib::Texture2DUnmanaged texture,
	raylib::Vector2 pos
) : PowerUp(texture, pos)
{

}

FreezePowerUp::~FreezePowerUp()
{

}

void FreezePowerUp::onCollision(
	std::unique_ptr<std::vector<Target>>& targets,
	std::unordered_map<std::string, Sound>& sounds)
{
	PlaySound(sounds["freeze"]); // time freeze sound
	// zero all target velocities on screen
	for (auto& target : *targets)
	{
		target.setVelocity(0.0f);
	}
}


// Powerup spawner function declarations
PowerUpSpawner::PowerUpSpawner(
	std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
	std::mt19937& mt
) : m_textures(textures), m_mt(mt)
{
	m_spawnRate = 5.0f;		// Spawn powerup every 5 seconds
}

PowerUpSpawner::~PowerUpSpawner()
{

}

void PowerUpSpawner::update(float deltaTime, std::unique_ptr<PowerUp>& powerup)
{
	m_spawnTimer += deltaTime;
	if (m_spawnTimer >= m_spawnRate)
	{
		powerup = std::move(spawnPowerUp());
		m_spawnTimer = 0.0f;
	}
}

std::unique_ptr<PowerUp> PowerUpSpawner::spawnPowerUp()
{
	// Select power up to spawn
	std::uniform_int_distribution<int> powerUpDist(0, 100);
	int powerUpToSpawn {powerUpDist(m_mt)};

	// Get random spawn position
	std::uniform_int_distribution<int> spawnPosXDist(GetScreenWidth() * 0.2f, GetScreenWidth() * 0.8f);
	int spawnXPos {spawnPosXDist(m_mt)};
	std::uniform_int_distribution<int> spawnPosYDist(GetScreenHeight() * 0.2f, GetScreenHeight() * 0.8f);
	int spawnYPos {spawnPosYDist(m_mt)};
	raylib::Vector2 spawnPos {
		static_cast<float>(spawnXPos),
		static_cast<float>(spawnYPos)
	};

	std::unique_ptr<PowerUp> powerup;
	if (powerUpToSpawn < 49)
	{
		powerup = std::make_unique<FireRatePowerUp>(m_textures["fire_rate_up"], spawnPos);
	}
	else if (powerUpToSpawn >= 50)
	{
		powerup = std::make_unique<FreezePowerUp>(m_textures["freeze"], spawnPos);
	}

	return powerup;
}