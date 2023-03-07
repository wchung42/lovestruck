#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"

class AnimatedObject
{
protected:
	raylib::Texture2DUnmanaged m_texture {};
	int m_frame {};
	int m_maxFrames {};
	float m_updateTime {};
	float m_runningTime {};
	float m_scale {1.0f};
	//raylib::Rectangle m_sourceRec {};
	//raylib::Rectangle m_destRec {};
	int m_width {};
	int m_height {};
	int m_directionX {1};	// 1: right, -1: left
	int m_directionY {1};	// 1: upright, -1: upside down
public:
	AnimatedObject();
	~AnimatedObject();
	AnimatedObject(
		raylib::Texture2DUnmanaged texture,
		int maxFrames,
		float updateTime,
		int directionX = 1,
		int directionY = 1,
		float scale = 1.0f
	);
	void update(float deltaTime);
	void draw(raylib::Vector2 pos);
	void draw(float deltaTime, raylib::Rectangle dest);
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	float getScale() { return m_scale; }

};