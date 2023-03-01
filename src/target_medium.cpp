#include "target_medium.hpp"
#include <iostream>

TargetMedium::TargetMedium(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged& aliveTexture,
	raylib::Texture2DUnmanaged& endingTexture
)	: Target(pos, aliveTexture, endingTexture)
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

//void TargetMd::update(float deltaTime)
//{
//	if (m_health == 0)
//		//m_readyToDelete = true;
//	{
//		m_runningTime += deltaTime;
//		if (m_runningTime >= m_updateTime)
//		{
//			m_readyToDelete = true;
//		}
//	}
//	else
//		Target::update(deltaTime);
//}
