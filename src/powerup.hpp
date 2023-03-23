#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "player.hpp"
#include "arrow.hpp"
#include "target.hpp"
#include "texture_manager.hpp"
#include "sound_manager.hpp"
#include <unordered_map>
#include <memory>
#include <random>

// Base powerup class declaration
class PowerUp
{
protected:
	raylib::Texture2DUnmanaged m_texture {};
	raylib::Vector2 m_pos {};
	float m_scale {};
	int m_width {};
	int m_height {};
	float m_velocity {600.0f};
	std::shared_ptr<SoundManager> m_soundManager;
public:
	PowerUp();
	PowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2	pos,
		std::shared_ptr<SoundManager> soundManager
	);
	virtual ~PowerUp();
	void update(float deltaTime);
	void draw();
	virtual void onCollision();
	raylib::Vector2 getPos() { return m_pos; }
	raylib::Rectangle getCollisionRec();
};


// Speed powerup class declaration
class FireRatePowerUp : public PowerUp
{
private:
	std::unique_ptr<Player>& m_player;
public:
	FireRatePowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2 pos,
		std::unique_ptr<Player>& player,
		std::shared_ptr<SoundManager> m_soundManager
	);
	~FireRatePowerUp();
	void onCollision() override;
};


// Freeze powerup class declaration
class FreezePowerUp : public PowerUp
{
private:
	float m_freezeDuration {};
	std::vector<std::unique_ptr<Target>>& m_targets;
public:
	FreezePowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2 pos,
		std::vector<std::unique_ptr<Target>>& targets,
		std::shared_ptr<SoundManager> m_soundManager
	);
	~FreezePowerUp();
	void onCollision() override;
};


// Powerup spawner class declaration
class PowerUpSpawner
{
private:
	std::mt19937& m_mt;
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<SoundManager> m_soundManager;
	float m_spawnRate {};
	float m_spawnTimer {};

	// For powerup
	std::unique_ptr<Player>& m_player;
	std::vector<std::unique_ptr<Target>>& m_targets;
public:
	PowerUpSpawner(
		std::shared_ptr<TextureManager> textureManager,
		std::shared_ptr<SoundManager> m_soundManager,
		std::unique_ptr<Player>& player,
		std::vector<std::unique_ptr<Target>>& targets,
		std::mt19937& mt
	);
	~PowerUpSpawner();
	void update(float deltaTime, std::unique_ptr<PowerUp>& powerup);
	std::unique_ptr<PowerUp> spawnPowerUp();
};