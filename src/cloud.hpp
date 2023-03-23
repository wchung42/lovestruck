#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"

class Cloud
{
private:
	raylib::Vector2 m_pos {};
	raylib::Texture2DUnmanaged m_texture {};
	float m_scale {1.0f};
	float m_width {m_texture.GetWidth() * m_scale};
public:
	Cloud();
	Cloud(raylib::Vector2 pos, raylib::Texture2DUnmanaged texture);
	~Cloud();
	raylib::Vector2 getPos() const { return m_pos; }
	float getWidth() const { return m_width; }
	void update(float deltaTime);
	void draw();
};