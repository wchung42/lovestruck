#include "target_spawner.hpp"
#include "target.hpp"
#include "target_small.hpp"
#include "target_medium.hpp"
#include "target_large.hpp"
#include <memory>
#include <iostream>
#include <vector>

TargetSpawner::TargetSpawner(
	int spawnRate, int windowWidth, 
	int minY, int maxY, std::vector<raylib::Texture2DUnmanaged>& textures
)
	: m_spawnRate(spawnRate), m_windowWidth(windowWidth), m_minY(minY), m_maxY(maxY), 
		m_textures(textures), m_mt((std::random_device())()) 
{
}

TargetSpawner::~TargetSpawner() {};

std::shared_ptr<Target> TargetSpawner::spawnTarget()
{
	
	// Get random y position
	std::uniform_int_distribution<int> distPos(m_minY, m_maxY);
	Vector2 spawnPos {static_cast<float>(m_windowWidth), static_cast<float>(distPos(m_mt))};

	// Get random target type to spawn
	// 70% small, 20% medium, 10% large
	std::uniform_int_distribution<int> distSpawn(0, 100);
	int num = distSpawn(m_mt);
	std::shared_ptr<Target> target {};
	if (num <= 69)
	{
		target = std::make_shared<TargetSmall>(spawnPos, m_textures[0], m_textures[3]);
	}
	else if (num >= 70 && num <= 89)
		target = std::make_shared<TargetMedium>(spawnPos, m_textures[1], m_textures[3]);
	else if (num >= 90)
		target = std::make_shared<TargetLarge>(spawnPos, m_textures[2], m_textures[3]);
	// Create target at generated position
	//std::shared_ptr<Target> target = std::make_shared<Target>(spawnPos, m_targetTexture);
	return target;
}

void TargetSpawner::update(float deltaTime, std::unique_ptr<std::vector<std::shared_ptr<Target>>>& targets)
{
	if (m_spawnTimer > m_spawnRate)
	{
		// Choose number of targets to spawn [1-3]
		std::uniform_int_distribution<int> distAmt(1, 2);
		int spawnAmt {distAmt(m_mt)};
		for (int i {0}; i < spawnAmt; ++i)
			targets->push_back(spawnTarget());
		m_spawnTimer = 0.0f;
	}
	else
		m_spawnTimer += deltaTime;
}