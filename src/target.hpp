#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"

class Target
{
protected:
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_texture {}; // Current texture
	raylib::Texture2DUnmanaged m_aliveTexture {};
	raylib::Texture2DUnmanaged m_endingTexture {};
	int m_width {};
	int m_height {};
	float m_velocity {}; // 300.0f
	float m_scale {}; // 1.0f
	int m_health {};
	int m_score {};
	bool m_readyToDelete {};
	bool m_collisionsOn {true};

	int m_frame {0};
	int m_maxFrames {};
	float m_runningTime {};
	float m_updateTime {1.0f / 12.0f};
	
public:
	Target(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged& liveTexture,
		raylib::Texture2DUnmanaged& endTexture
	);
	~Target();
	int getWidth() const { return m_width; }
	Vector2 getPos() const { return m_pos; }
	int getHealth() const { return m_health; }
	int getScore() const { return m_score; }
	bool areCollisionsOn() const { return m_collisionsOn; }
	void setVelocity(float newVelocity) { m_velocity = newVelocity; }
	virtual void onHit();
	bool readyToDelete() { return m_readyToDelete; }
	void update(float deltaTime);
	void draw();
	Rectangle getCollisionRec();
};


// Small target
class TargetSmall : public Target
{
public:
	TargetSmall(
		Vector2 pos,
		raylib::Texture2DUnmanaged& activeTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetSmall();
	void onHit();
};


// Medium target
class TargetMedium : public Target
{
public:
	TargetMedium(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged& aliveTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetMedium();
	void onHit();
};


// Large target
class TargetLarge : public Target
{
public:
	TargetLarge(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged& activeTexture,
		raylib::Texture2DUnmanaged& endingTexture
	);
	~TargetLarge();
	void onHit();
};