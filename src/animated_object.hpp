#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"

class AnimatedObject
{
protected:
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_texture {};
	int m_frame {};
	int m_maxFrames {};
	float m_updateTime {};
	float m_runningTime {};
	float m_scale {1.0f};
	raylib::Rectangle m_sourceRec {};
	raylib::Rectangle m_destRec {};
	int m_width {};
	int m_height {};
public:
	AnimatedObject();
	~AnimatedObject();
	AnimatedObject(
		raylib::Vector2 pos,
		raylib::Texture2DUnmanaged texture,
		int maxFrames,
		float updateTime
	);
	void update(float deltaTime);
	void draw(float deltaTime);
};