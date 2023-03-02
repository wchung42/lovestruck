#include "target.hpp"
#include <iostream>

Target::Target(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture,
	raylib::Texture2DUnmanaged& endingTexture
) : m_pos(pos), m_texture(aliveTexture),
	m_aliveTexture(aliveTexture), m_endingTexture(endingTexture)
{
};

Target::~Target() { };

void Target::onHit()
{
	m_health--;
	if (m_health == 0)
	{
		m_texture = m_endingTexture;
		m_maxFrames = 4;
		m_frame = -1; // Starts at -1 so the first sprite would get rendered during update
		m_collisionsOn = false; // Turn off collisions for dead target
	}
}

void Target::update(float deltaTime)
{
	if (m_health == 0)
	{
		m_runningTime += deltaTime;
		if (m_runningTime >= m_updateTime)
		{
			++m_frame;
			m_runningTime = 0.0f;
			if (m_frame == m_maxFrames)
				m_readyToDelete = true;
		}
	}
	else
		m_pos.x -= m_velocity * deltaTime;
}

void Target::draw()
{
	raylib::Rectangle source {
		static_cast<float>(m_frame * m_width),
		0.0f,
		static_cast<float>(m_width),
		static_cast<float>(m_height)
	};
	raylib::Rectangle dest {
		m_pos.x,
		m_pos.y,
		static_cast<float>(m_width) * m_scale,
		static_cast<float>(m_height) * m_scale
	};
	m_texture.Draw(source, dest, raylib::Vector2 {}, 0.0f, WHITE);

	/*if (m_collisionsOn)
		DrawRectangleLinesEx(getCollisionRec(), 1.0f, RED);*/
}

Rectangle Target::getCollisionRec()
{
	float scaledWidth {m_width * m_scale};
	float scaledHeight {m_height * m_scale};
	float xOffsetMultiplier {0.2f};
	float yOffsetMultiplier {0.1f};
	float xOffset {scaledWidth * xOffsetMultiplier};
	float yOffset {scaledWidth * yOffsetMultiplier};
	raylib::Rectangle rec {
		m_pos.x + xOffset,
		m_pos.y + yOffset,
		scaledWidth - (2.0f * xOffset),
		scaledHeight - (2.0f * yOffset)
	};
	return rec;
}