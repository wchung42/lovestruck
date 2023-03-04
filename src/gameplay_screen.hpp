#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"
#include "player.hpp"
#include "arrow.hpp"
#include "target.hpp"
#include "target_spawner.hpp"
#include "cloud.hpp"
#include <memory>

class GameplayScreen : public Screen
{
private:
	std::unique_ptr<Player> m_player;
	std::unique_ptr<std::vector<std::shared_ptr<Arrow>>> m_arrows;
	std::unique_ptr<std::vector<std::unique_ptr<Target>>> m_targets;
	std::unique_ptr<TargetSpawner> m_spawner;
	//std::vector<raylib::Texture2DUnmanaged> m_textures;
	std::vector<Cloud> m_clouds;
	std::vector<raylib::Sound> m_sounds;
	int m_score {};
	bool m_gameOver {};
public:
	GameplayScreen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures);
	~GameplayScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};