#include "target_small.hpp"

TargetSmall::TargetSmall(
	Vector2 pos,
	raylib::Texture2DUnmanaged& activeTexture,
	raylib::Texture2DUnmanaged& endingTexture
)	: Target(pos, activeTexture, endingTexture)
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