#include "target_spawner.hpp"
#include "target.hpp"
#include <memory>
#include <vector>

TargetSpawner::TargetSpawner(
	float spawnRate, float minSpawnRate, int minY, int maxY,
	std::vector<raylib::Texture2DUnmanaged>& textures
) :	m_spawnRate(spawnRate), m_minSpawnRate(minSpawnRate),
	m_minY(minY), m_maxY(maxY), m_textures(textures),
	m_mt((std::random_device())()) 
{
}

TargetSpawner::~TargetSpawner() {};

raylib::Vector2 TargetSpawner::calculateSpawnPosition(const raylib::Texture2DUnmanaged& texture, float scale)
{
	int maxY = GetScreenHeight() - (texture.GetHeight() * scale) - 64; // Screen height - scaled texture height - height of clouds
	std::uniform_int_distribution<int> distPos(m_minY, maxY);
	raylib::Vector2 spawnPos {static_cast<float>(GetScreenWidth()), static_cast<float>(distPos(m_mt))};
	return spawnPos;
}

void TargetSpawner::spawnTarget(std::unique_ptr<std::vector<std::unique_ptr<Target>>>& targets)
{
	// Get random target type to spawn
	// 60% small, 30% medium, 10% large
	std::uniform_int_distribution<int> distSpawn(0, 100);
	int num = distSpawn(m_mt);
	std::unique_ptr<Target> target {};
	if (num <= 59)
	{	
		target = std::make_unique<TargetSmall>(
			calculateSpawnPosition(m_textures[0], 0.3f),
			m_textures[0],
			m_textures[3]
		);
	}
	else if (num >= 60 && num <= 89)
		target = std::make_unique<TargetMedium>(
			calculateSpawnPosition(m_textures[1], 0.6f),
			m_textures[1],
			m_textures[3]
		);
	else if (num >= 90)
		target = std::make_unique<TargetLarge>(
			calculateSpawnPosition(m_textures[2], 1.0f),
			m_textures[2],
			m_textures[3]
		);
	targets->push_back(std::move(target));
}

void TargetSpawner::update(float deltaTime, std::unique_ptr<std::vector<std::unique_ptr<Target>>>& targets)
{
	if (m_spawnRate > m_minSpawnRate)
	{
		m_timer += deltaTime;

		// Increase spawn rate every 15 seconds
		if (m_timer > 10.0f)
		{
			m_spawnRate *= 0.9;
			m_timer = 0.0f;
		}
	}
		
	if (m_spawnTimer > m_spawnRate)
	{
		// Choose number of targets to spawn (1-3)
		std::uniform_int_distribution<int> distAmountChance(0, 100);
		int chance {distAmountChance(m_mt)};
		int spawnAmount {};
		if (chance <= 59)
			spawnAmount = 1;
		else if (chance >= 60 && chance <= 89)
			spawnAmount = 2;
		else
			spawnAmount = 3;
		
		for (int i {0}; i < spawnAmount; ++i)
			spawnTarget(targets);
		
		m_spawnTimer = 0.0f;
	}
	else
		m_spawnTimer += deltaTime;
}