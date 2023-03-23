#include "Arrow.hpp"

Arrow::Arrow(raylib::Vector2 pos, raylib::Texture2DUnmanaged& arrowTexture)
	: m_pos(pos), m_arrowTexture(arrowTexture)
{
	m_width = arrowTexture.width;
	m_height = arrowTexture.height;
}

Arrow::~Arrow() {}

void Arrow::update(float deltaTime)
{
	// Move arrow to the right by m_velocity * deltaTime
	if (isFired)
		m_pos.x += m_velocity * deltaTime;
}

void Arrow::draw()
{
	// Draw arrow in motion
	m_arrowTexture.Draw(m_pos, 0.0f, m_scale, WHITE);
	//DrawTextureEx(m_texture, m_pos, 0.0f, m_scale, WHITE);
	//DrawRectangleLinesEx(getCollisionRec(), 1.0f, RED);
}

void Arrow::move()
{
	isFired = true;
}

Rectangle Arrow::getCollisionRec()
{
	float scaledWidth {m_width * m_scale};
	float scaledHeight {m_height * m_scale};
	float xOffsetMultiplier {0.05f};
	float yOffsetMultiplier {0.2f};
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