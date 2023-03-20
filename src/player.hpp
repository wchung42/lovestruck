#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "Arrow.hpp"
#include <memory>

class Player
{
private:
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_playerTexture {};
	raylib::Texture2DUnmanaged m_playerAliveTexture {};
	raylib::Texture2DUnmanaged m_playerDeadTexture {};
	raylib::Texture2DUnmanaged m_arrowTexture {};
	raylib::Texture2DUnmanaged m_bowLoadedTexture {};
	raylib::Texture2DUnmanaged m_bowNotLoadedTexture {};
	int m_width {};
	int m_height {};
	float m_velocity {6.0f};
	std::shared_ptr<Arrow> m_arrow;
	bool m_hasArrow {true};
	float m_fireRate {0.3f};
	float m_fireTimer {0.0f};
	bool m_controlsOn {true}; // Turn off controls in title screen
	bool m_alive {true};
	bool m_readyForEndScreen {};
	
	// Animation variables
	int m_frame {};
	int m_maxFrames {};
	float m_updateTime {};
	float m_runningTime {};
	float m_scale {0.85f};
	float m_bowScale {0.5f};	

public:
	Player( 
		raylib::Texture2DUnmanaged& playerAliveTexture,
		raylib::Texture2DUnmanaged& playerDeadTexture, 
		raylib::Texture2DUnmanaged& arrowTexture,
		raylib::Texture2DUnmanaged& m_bowLoadedTexture,
		raylib::Texture2DUnmanaged& m_bowNotLoadedTexture,
		int maxFrames, 
		float updateTime
	);
	~Player();
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	Vector2 getPos() const { return m_pos; }
	bool getHasArrow() const { return m_hasArrow; }
	float getFireRate() const { return m_fireRate; }
	void setFireRate(float newFireRate) { m_fireRate = newFireRate; }
	void toggleAliveStatus() { m_alive = false; }
	bool isReadyForEnd() const { return m_readyForEndScreen; }
	void update(float deltaTime);
	void draw();
	void reload();
	std::shared_ptr<Arrow> shoot();
	Rectangle getCollisionRec();
};