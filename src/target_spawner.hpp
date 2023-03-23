#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "texture_manager.hpp"
#include "target.hpp"
#include <memory>
#include <vector>
#include <random>

class TargetSpawner
{
private:
	float m_spawnRate {};
	float m_minSpawnRate {};
	float m_spawnTimer {};
	int m_minY {};
	int m_maxY {};
	float m_timer {};
	std::shared_ptr<TextureManager> m_textureManager;
	std::mt19937& m_mt;
public:
	TargetSpawner(
		float spawnRate,
		float minSpawnRate,
		int minY,
		int maxY,
		std::shared_ptr<TextureManager> textureManager,
		std::mt19937& mt
	);
	~TargetSpawner();
	raylib::Vector2 calculateSpawnPosition(const raylib::Texture2DUnmanaged& texture, float scale);
	void spawnTarget(std::vector<std::unique_ptr<Target>>& targets);
	void update(float deltaTime, std::vector<std::unique_ptr<Target>>& targets);
};