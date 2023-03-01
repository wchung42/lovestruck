#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "target.hpp"
#include <memory>
#include <vector>
#include <random>

class TargetSpawner
{
private:
	int m_spawnRate {3};
	int m_windowWidth {};
	int m_minY {};
	int m_maxY {};
	float m_spawnTimer {0.0f};
	std::vector<raylib::Texture2DUnmanaged> m_textures;

	std::mt19937 m_mt;
public:
	TargetSpawner(
		int spawnRate,
		int windowWidth,
		int minY,
		int maxY,
		std::vector<raylib::Texture2DUnmanaged>& textures
	);
	~TargetSpawner();
	std::shared_ptr<Target> spawnTarget();
	void update(float deltaTime, std::unique_ptr<std::vector<std::shared_ptr<Target>>>& targets);
};