#include "target_large.hpp"

TargetLarge::TargetLarge(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture, 
	raylib::Texture2DUnmanaged& endingTexture
)	: Target(pos, aliveTexture, endingTexture) 
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