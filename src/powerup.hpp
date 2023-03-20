#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "player.hpp"
#include "arrow.hpp"
#include "target.hpp"
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
public:
	PowerUp();
	PowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2	pos
	);
	virtual ~PowerUp();
	void update(float deltaTime);
	void draw();
	raylib::Rectangle getCollisionRec();
};


// Speed powerup class declaration
class FireRatePowerUp : public PowerUp
{
private:
public:
	FireRatePowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2 pos
	);
	~FireRatePowerUp();
	void onCollision(
		std::unique_ptr<Player>& player,
		std::unordered_map<std::string, Sound>& sounds);
};


// Freeze powerup class declaration
class FreezePowerUp : public PowerUp
{
private:
	float m_freezeDuration {};
public:
	FreezePowerUp(
		raylib::Texture2DUnmanaged texture,
		raylib::Vector2 pos
	);
	~FreezePowerUp();
	void onCollision(
		std::unique_ptr<std::vector<Target>>& targets,
		std::unordered_map<std::string, Sound>& sounds);
};


// Powerup spawner class declaration
class PowerUpSpawner
{
private:
	std::mt19937& m_mt;
	std::unordered_map<std::string, raylib::Texture2DUnmanaged>& m_textures;
	float m_spawnRate {};
	float m_spawnTimer {};
public:
	PowerUpSpawner(
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
		std::mt19937& mt
	);
	~PowerUpSpawner();
	void update(float deltaTime, std::unique_ptr<PowerUp>& powerup);
	std::unique_ptr<PowerUp> spawnPowerUp();
};