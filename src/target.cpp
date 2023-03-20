#include "target.hpp"

// ----------------------------------------------
// Base target class definitions
// ----------------------------------------------
Target::Target(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture,
	raylib::Texture2DUnmanaged& endingTexture
) : m_pos(pos), m_texture(aliveTexture),
	m_aliveTexture(aliveTexture), m_endingTexture(endingTexture)
{
}

Target::~Target() {}

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

// ----------------------------------------------
// Small target class definitions
// ----------------------------------------------
TargetSmall::TargetSmall(
	Vector2 pos,
	raylib::Texture2DUnmanaged& activeTexture,
	raylib::Texture2DUnmanaged& endingTexture
) : Target(pos, activeTexture, endingTexture)
{
	m_maxFrames = 2;
	m_width = m_texture.width / m_maxFrames;
	m_height = m_texture.height;
	m_velocity = 300.0f;
	m_scale = 0.3f; // 0.3f
	m_health = 1; // 1 hit to destroy
	m_score = 1;
}

TargetSmall::~TargetSmall() {};

void TargetSmall::onHit()
{
	Target::onHit();
}

// ----------------------------------------------
// Medium target class definitions
// ----------------------------------------------
TargetMedium::TargetMedium(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture,
	raylib::Texture2DUnmanaged& endingTexture
) : Target(pos, aliveTexture, endingTexture)
{
	m_maxFrames = 3;
	m_width = m_texture.width / m_maxFrames;
	m_height = m_texture.height;
	m_velocity = 250.0f;
	m_scale = 0.6f;
	m_health = 2; // 2 hits to destroy
	m_score = 2;
}

TargetMedium::~TargetMedium() {};

void TargetMedium::onHit()
{
	Target::onHit();
	this->m_frame++;
}

// ----------------------------------------------
// Large target class definitions
// ----------------------------------------------
TargetLarge::TargetLarge(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture,
	raylib::Texture2DUnmanaged& endingTexture
) : Target(pos, aliveTexture, endingTexture)
{
	m_maxFrames = 4;
	m_width = m_texture.width / m_maxFrames;
	m_height = m_texture.height;
	m_velocity = 200.0f;
	m_scale = 1.0f;
	m_health = 3; // 3 hits to destroy
	m_score = 3;
}

TargetLarge::~TargetLarge() {};

void TargetLarge::onHit()
{
	Target::onHit();
	this->m_frame++;
}