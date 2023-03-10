#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
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
	std::vector<raylib::Texture2DUnmanaged> m_textures;

	std::mt19937 m_mt;
public:
	TargetSpawner(
		float spawnRate,
		float minSpawnRate,
		int minY,
		int maxY,
		std::vector<raylib::Texture2DUnmanaged>& textures
	);
	~TargetSpawner();
	raylib::Vector2 calculateSpawnPosition(const raylib::Texture2DUnmanaged& texture, float scale);
	void spawnTarget(std::unique_ptr<std::vector<std::unique_ptr<Target>>>& targets);
	void update(float deltaTime, std::unique_ptr<std::vector<std::unique_ptr<Target>>>& targets);
};