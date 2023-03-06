#include "animated_object.hpp"

AnimatedObject::AnimatedObject() {}

AnimatedObject::~AnimatedObject() {}

AnimatedObject::AnimatedObject(
	raylib::Vector2 pos,
	raylib::Texture2DUnmanaged texture,
	int maxFrames,
	float updateTime)
	:	m_pos(pos), m_texture(texture),
		m_maxFrames(maxFrames), m_updateTime(updateTime)
{
	m_width = texture.width / m_maxFrames;
	m_height = texture.height;

	m_sourceRec = raylib::Rectangle(m_width * m_frame, 0.0f, m_width, m_height);
	m_destRec = raylib::Rectangle(
		m_pos.GetX(),
		m_pos.GetY(),
		static_cast<float>(m_width * m_scale),
		static_cast<float>(m_height * m_scale)
	);
}

void AnimatedObject::update(float deltaTime)
{
	m_runningTime += deltaTime;
	if (m_runningTime >= m_updateTime)
	{
		m_runningTime = 0;
		++m_frame;
		if (m_frame > m_maxFrames)
			m_frame = 0;
	}
}

void AnimatedObject::draw(float deltaTime)
{
	m_sourceRec = raylib::Rectangle(m_width * m_frame, 0.0f, -m_width, m_height);
	m_destRec = raylib::Rectangle(
		m_pos.GetX(),
		m_pos.GetY() + sin(GetTime() * 2.0f) * 5.0f,
		static_cast<float>(m_width * m_scale),
		static_cast<float>(m_height * m_scale)
	);
	m_texture.Draw(m_sourceRec, m_destRec, raylib::Vector2 {}, -1.0f, WHITE);
}