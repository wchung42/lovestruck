#include "cloud.hpp"
#include <iostream>

Cloud::Cloud() {};

Cloud::Cloud(raylib::Vector2 pos, raylib::Texture2DUnmanaged& texture)
	: m_pos(pos), m_texture(texture)
{
}

Cloud::~Cloud() {};

void Cloud::update(float deltaTime)
{
	// Move cloud back to right side of screen if it goes out of left side screen
	if (m_pos.x + m_texture.GetWidth() < 0)
	{
		float offset = std::abs((m_pos.x + m_texture.GetWidth()) - 0.0f);
		m_pos.x = GetScreenWidth() - offset;
	}

	m_pos.x -= 100.0f * deltaTime;
}

void Cloud::draw()
{
	m_texture.Draw(m_pos, 0.0f, m_scale, WHITE);
}